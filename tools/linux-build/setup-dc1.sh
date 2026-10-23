#!/bin/bash
# Per-checkout bootstrap for building DC1 (gnirsdc-1-vme, the ppc/ tree) on
# Linux. `make -C ppc` runs this by itself when it is needed (see the rule at
# the top of ppc/Makefile), so nobody has to run it by hand.
#
# Everything here exists because applSetup.pl stamps the tree's ABSOLUTE path
# into the generated config, so it cannot be committed or baked into an image.
#
# DC1 is the coadder/DHS crate: an MVME2700 that loads no iocCore. It builds
# against EPICS 3.13.4GEM7 headers and Tornado 2.0 (gem-epics3134gem7,
# gem-tornado20-linux) and the DHS headers (hrwfs-dhs-vxlibs) -- the same
# toolchain and DHS package as hrwfs.
set -e

# pwd -P: the PHYSICAL path. ppc/Makefile compares .applTop against make's
# $(CURDIR), which is always physical.
TOP="$(cd "$(dirname "$0")/../.." && pwd -P)"
cd "$TOP/ppc"

if [ -f /etc/profile.d/gem7.sh ]; then . /etc/profile.d/gem7.sh
else
    export EPICS=/usr/software/dev/packages/epics/epics3.13.4GEM7
    export EPICS_BASE=$EPICS/base HOST_ARCH=Linux
    export WIND_BASE=/usr/software/dev/packages/vxworks/tornado2.0/ppc
    export WIND_HOST_TYPE=x86-linux
    export PATH=$EPICS_BASE/bin/$HOST_ARCH:$WIND_BASE/host/$WIND_HOST_TYPE/bin:$PATH
fi

. "$TOP/tools/linux-build/build.conf"
SITE="${APPLIC_SITE:-$SITE}"

# Scrub generated state. applSetup PRESERVES APPLIC_INSTALL from an existing
# config/CONFIG.Defs, so a tree bootstrapped elsewhere would keep a stale path.
rm -rf config bin lib include dbd data Distfile .applTop
find . -type d -name 'O.*' -prune -exec rm -rf {} + 2>/dev/null || true

echo "APPLIC_TOP = $TOP/ppc" > .applTop

APPLSETUP="$EPICS_BASE/bin/$HOST_ARCH/applSetup.pl"
[ -f "$APPLSETUP" ] || { echo "ERROR: $APPLSETUP not found -- install gem-epics3134gem7" >&2; exit 1; }

# applSetup OVERWRITES the application's own startup files from the site
# templates (local.vws, resource.def, UAE.dist) and the top Makefile. A
# template local.vws mounts the WRONG file server and still boots, which is
# how hrwfs once shipped pisces-control. Stash what the repository versions
# and put it back afterwards.
STASH=$(mktemp -d)
VERSIONED="startup/local.vws startup/resource.def startup/UAE.dist Makefile"
for f in $VERSIONED; do
    [ -f "$f" ] && cp -p "$f" "$STASH/${f//\//_}"
done

# nirsPPCInstall's applSetup arguments, with the DHS paths of the packaged
# hrwfs-dhs-vxlibs (production built against /gemini/dhs/dhs-0.19b; the
# libraries DC1 loads are byte-identical to the packaged ones).
perl "$APPLSETUP" -T ppc604 -S "$SITE" \
     -d /gemini/dhs/dhs/external -d /gemini/dhs/dhs \
     -I dc-data -I startup -s Makefile.Dirs

for f in $VERSIONED; do
    k="$STASH/${f//\//_}"
    if [ -f "$k" ] && ! cmp -s "$k" "$f"; then
        echo "  restoring ppc/$f (applSetup replaced it with its template)"
        cp -p "$k" "$f"
    fi
done
for f in $VERSIONED; do
    k="$STASH/${f//\//_}"
    if [ -f "$k" ] && ! cmp -s "$k" "$f"; then
        echo "ERROR: ppc/$f was not restored after applSetup" >&2
        rm -rf "$STASH"; exit 1
    fi
done
rm -rf "$STASH"

# Production's objects carry stabs (cygnus 2.7.2); gcc 2.96 defaults to DWARF,
# which the Tornado 2.0 debugger cannot read.
#
# APPLIC_IOCPATH must be host:path -- CONFIG_APPLIC takes the path after the
# colon for the generated startup scripts' cd. DCDATA_TARGET is what
# dc-data/Makefile builds for; nirsPPCInstall exported it from the shell, and
# without it dc-data quietly builds nothing.
cat >> config/CONFIG.Defs <<EOF

DEBUG_CFLAGS = -gstabs
include $TOP/tools/linux-build/build.conf
APPLIC_IOCPATH = \$(IOCPATH_HOST):\$(DC1_DEPLOY)
DCDATA_TARGET = ppc604
EOF

# Without config/, ppc/Makefile's -include silently skips CONFIG and make runs
# its first target, `release`, which tars the source instead of building.
for f in config/CONFIG config/CONFIG.Defs config/RULES.Dirs; do
    [ -f "$f" ] || { echo "ERROR: applSetup.pl did not produce ppc/$f" >&2; exit 1; }
done

echo "DC1 setup complete:"
grep '^APPLIC_IOCPATH\|^APPLIC_TARGETS' config/CONFIG.Defs | sed 's/^/  /'
