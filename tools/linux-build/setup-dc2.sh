#!/bin/bash
# Per-checkout bootstrap for building DC2 (gnirsdc-2-vme, the top-level tree)
# on Linux. The top Makefile runs this by itself when it is needed, so nobody
# has to run it by hand.
#
# DC2 (ngnirsdc2) is an MVME162 running vxWorks 5.2 and EPICS R3.12.2GEM5 --
# the generation gnirscc uses, built with the same packages (gem-vxworks52-linux
# for the Linux 68k gcc, gem-epics3122gem5, gem5-deplibs) plus the DHS headers
# from hrwfs-dhs-vxlibs (DHS 0.16, which nirsSetup named as DHS_DIR).
#
# This is nirsSetup's applSetup call, made reproducible. It exists because the
# EPICS 3.12 applSetup stamps the checkout's ABSOLUTE path into the generated
# config and symlinks, so none of it can be committed or baked into an image.
set -e

TOP="$(cd "$(dirname "$0")/../.." && pwd -P)"
cd "$TOP"

if [ -f /etc/profile.d/gem5.sh ]; then . /etc/profile.d/gem5.sh
else
    export EPICS=/usr/software/dev/packages/epics/epics3.12.2GEM5
    export EPICS_BASE=$EPICS/base EPICS_EXTENSIONS=$EPICS/extensions
    export HOST_ARCH=Linux TARGET_ARCH=68k
    export VX_DIR=/usr/software/dev/packages/vxworks/v5.2b
    unset GCC_EXEC_PREFIX
    export PATH=$VX_DIR/gnu/$HOST_ARCH.$TARGET_ARCH/bin:$PATH
fi
. "$TOP/tools/linux-build/build.conf"

APPLSETUP=$EPICS/extensions/bin/solaris/applSetup
[ -f "$APPLSETUP" ] || { echo "ERROR: $APPLSETUP not found -- install gem-epics3122gem5" >&2; exit 1; }
command -v csh >/dev/null || { echo "ERROR: csh (tcsh) is required for applSetup" >&2; exit 1; }

# --- snc ---------------------------------------------------------------------
# epicsCntrlSrc/dcSetup.st (the DC setup sequencer, part of cadTasks.o) needs
# the state-notation compiler, and the GEM5 package has no Linux host tools.
# Build SNC 1.9.2 -- the version of the seq runtime the crate loads ("SEQ
# Version 1.9.2") -- from the polaris source in snc-1.9.2/, using the parser
# and lexer polaris generated (snc.c, snc.h, snc_lex.c), so no yacc or lex is
# involved. 32-bit: the 1998 code casts pointers to int and relies on implicit
# int returns, which truncate pointers in a 64-bit build.
SNCDIR=$TOP/tools/linux-build/snc-1.9.2
mkdir -p "$SNCDIR/O.$HOST_ARCH"
( cd "$SNCDIR" && gcc -m32 -O -w -I. -I"$EPICS_BASE/include" \
      -o "O.$HOST_ARCH/snc" snc_main.c parse.c phase2.c gen_ss_code.c \
      gen_tables.c sncVersion.c snc.c ) \
  || { echo "ERROR: building snc failed (needs gcc and glibc-devel.i686)" >&2; exit 1; }

# --- scrub -------------------------------------------------------------------
# applSetup PRESERVES values from an existing config/CONFIG.Defs (install path,
# iocpath, depends), so a checkout set up elsewhere would keep stale ones.
# data/ and include/ are NOT scrubbed: in this tree they are committed source
# that the build also installs into (APPLIC_INSTALL is the checkout).
rm -rf bin epics config/CONFIG.Defs config.par Distfile
find . -name .git -prune -o -path ./ppc -prune -o -path ./tools -prune -o \
       -type d -name 'O.*' -prune -exec rm -rf {} + 2>/dev/null || true
find . -name .git -prune -o -path ./ppc -prune -o \
       \( -name .applTop -o -name .epics -o -name .version \) -type l -exec rm -f {} +
rm -f startup/Distfile.*

# applSetup OVERWRITES the application's own startup files with the UAE
# templates on every run. A template local.vws mounts the wrong file server
# and still boots. Stash what the repository versions and put it back.
VERSIONED="startup/local.vws startup/resource.def startup/UAE.dist capfast/cad.rc Makefile"
STASH=$(mktemp -d)
trap 'rm -rf "$STASH"' EXIT
for f in $VERSIONED; do
    [ -f "$f" ] && cp -p "$f" "$STASH/${f//\//_}"
done

# nirsSetup's arguments (target mv162, its -I list, slalib/timelib/astlib and
# DHS depends), with -b/-c/-e explicit because applSetup otherwise finds them
# through Solaris host binaries. `dl` is left out: its .adl -> .dl conversion
# needs a tool that only ever existed on Solaris, and the .dl files are
# committed in data/ (identical to production's).
csh -f "$APPLSETUP" \
    -b "$EPICS/base" -c "$EPICS/config" -e "$EPICS/extensions" \
    -install "$TOP" -targets mv162 -P "$IOCPATH_HOST:$DC2_DEPLOY" \
    -subdir_file Makefile.subdirs \
    -I omega -I pv -I annex -I src -I ascii -I capfast -I dqSocket \
    -I epicsCntrlSrc -I globals -I gnRpcSrc -I startup -I tempCard -I utilSource \
    -depends /gemini/slalib -depends /gemini/timelib -depends /gemini/astlib \
    -depends /gemini/dhs/dhs

for f in $VERSIONED; do
    k="$STASH/${f//\//_}"
    if [ -f "$k" ] && ! cmp -s "$k" "$f"; then
        echo "  restoring $f (applSetup replaced it with its template)"
        cp -p "$k" "$f"
    fi
done
for f in $VERSIONED; do
    k="$STASH/${f//\//_}"
    if [ -f "$k" ] && ! cmp -s "$k" "$f"; then
        echo "ERROR: $f was not restored after applSetup" >&2; exit 1
    fi
done

for f in config/CONFIG.Defs .applTop epics/base epics/config epics/extensions; do
    [ -e "$f" ] || { echo "ERROR: applSetup did not produce $f" >&2; exit 1; }
done

# `override`: CONFIG_APPLIC and CONFIG_SITE.Unix.Linux assign both AFTER
# CONFIG.Defs is read. bsdinstall (CONFIG_SITE.Unix.Linux's choice) does not
# exist on a modern Linux; it only installs host-side extras (bin/Linux), which
# do not ship, but a failure there would hide real ones in the log.
cat >> config/CONFIG.Defs <<EOF

override SNC = $SNCDIR/O.\$(HOST_ARCH)/snc
override INSTALL_PRODUCT = install
EOF

# Two generators cannot run on Linux, and their outputs are committed in data/
# (byte-identical to production's). Seed them into the host build directories,
# NEWER than their inputs, so make treats the chains as satisfied:
#   capfast/: .sch -> sch2edif (FlexLM, licence server gone) -> .db
#   ascii/:   cat_ascii/*.ascii -> SPARC bld* tools -> default.{dctsdr,sdrSum}
mkdir -p capfast/O.$HOST_ARCH ascii/O.$HOST_ARCH
cp -p data/nirsTop.db data/nirsSadTop.db capfast/O.$HOST_ARCH/
cp -p data/default.dctsdr data/default.sdrSum ascii/O.$HOST_ARCH/
touch capfast/O.$HOST_ARCH/*.db ascii/O.$HOST_ARCH/default.*

echo "DC2 setup complete:"
grep '^APPLIC_IOCPATH\|^APPLIC_TARGETS' config/CONFIG.Defs | sed 's/^/  /'
