#!/bin/sh
#
# gnirsdc-gather.sh -- collect what both GNIRS DC crates boot, from a host that
# can see the production /gemini tree (hbfcon03, where it is mounted under
# /net/pisces). REL-5058.
#
#   sh gnirsdc-gather.sh
#   # then scp the tarball it names at the end
#
# The GNIRS DC is two crates on two platforms (from their boot logs):
#
#   DC2 ngnirsdc2 10.2.2.84  MVME162, vxWorks 5.2, EPICS R3.12.2GEM5
#       kernel  /gemini/gnirs/vw/mv162/vxWorks
#       startup /gemini/GEM5/gnirs/DC/DC/bin/mv162/startup  -> cd .../DC/V1-13
#   DC1 ngnirsdc1 10.2.2.83  MVME2700, vxWorks 5.4.2, no iocCore (coadder/DHS)
#       kernel  /gemini/external/vxWorks/tornado2.0/mv2700-niri/vxWorks
#       startup /gemini/epics3.13.4/gnirs/DC/DC/ppc/bin/ppc604/startup
#                                                    -> cd .../DC/V1-10/ppc
#
# READ-ONLY against production. It writes only under $OUTDIR (default
# /tmp/gnirsdc-gather) and the final tarball in /tmp.
#
# Overrides:
#   GEMINI_ROOT=/path   skip autodetect and use this as the /gemini root
#   OUTDIR=/path        where to build the collection
#   LIMIT_MB=800        refuse to tar any single tree bigger than this
#
# Plain POSIX /bin/sh: no `find -maxdepth`, no `test -e`, no `tar -z`.

set -u

OUTDIR=${OUTDIR:-/tmp/gnirsdc-gather}
LIMIT_MB=${LIMIT_MB:-800}
REPORT=$OUTDIR/REPORT.txt

if md5sum /dev/null >/dev/null 2>&1; then MD5CMD="md5sum"
elif digest -a md5 /dev/null >/dev/null 2>&1; then MD5CMD="digest -a md5 -v"
elif openssl md5 /dev/null >/dev/null 2>&1; then MD5CMD="openssl md5"
else MD5CMD=""
fi

say() { echo "$@" >> "$REPORT"; }
note() { echo "$@" | tee -a "$REPORT"; }
sec() {
    echo ""                                                            >> "$REPORT"
    echo "=============================================================" >> "$REPORT"
    echo "== $*"                                                       >> "$REPORT"
    echo "=============================================================" >> "$REPORT"
    echo "==> $*"
}
run() {
    echo ""                    >> "$REPORT"
    echo "\$ $*"               >> "$REPORT"
    "$@" 2>&1 | sed 's/^/   /' >> "$REPORT"
}

rm -rf "$OUTDIR"
mkdir -p "$OUTDIR/tars" "$OUTDIR/manifests" "$OUTDIR/text" || exit 1
: > "$REPORT"

sec "host"
run uname -a
run date
say "  md5 tool : ${MD5CMD:-NONE}"

# --- 1. locate the /gemini root --------------------------------------------
sec "locating the /gemini root"
G=""
if [ -n "${GEMINI_ROOT:-}" ]; then
    G=$GEMINI_ROOT
else
    for c in /net/pisces/gemini /net/pisces/export/gemini /gemini; do
        if [ -d "$c/GEM5/gnirs" ]; then G=$c; break; fi
    done
fi
if [ -z "$G" ] || [ ! -d "$G/GEM5/gnirs" ]; then
    note "ERROR: no /gemini root with GEM5/gnirs found. Find it and re-run:"
    note "  GEMINI_ROOT=/net/pisces/<whatever> sh $0"
    exit 1
fi
note "  GEMINI ROOT = $G"

DC2=$G/GEM5/gnirs/DC
DC1=$G/epics3.13.4/gnirs/DC

# --- 2. topology: which version each DC link selects ------------------------
sec "topology"
run ls -l "$G/GEM5/gnirs"
run ls -l "$DC2"
run ls -l "$G/epics3.13.4/gnirs"
run ls -l "$DC1"
[ -d "$DC1/DC" ] && run ls -l "$DC1/DC"
run ls -l "$G/gnirs" "$G/gnirs/vw" "$G/gnirs/vw/mv162"
run ls -l "$G/external/vxWorks" "$G/external/vxWorks/tornado2.0/mv2700-niri"
run ls -l "$G/slalib" "$G/timelib" "$G/astlib"
run ls -l "$G/external/GEM5/base/bin/mv167" "$G/external/GEM5/extensions/bin/mv167"
run ls -l "$G/dhs/dhs/lib/mv2700T2" "$G/dhs/dhs/external/lib/mv2700T2"

# --- 3. the text artifacts, inline (read these first) -----------------------
sec "deployed startup scripts (READ THESE FIRST)"
show() {   # show <file> <copy-name>
    [ -f "$1" ] || { say "  MISSING: $1"; return; }
    say ""
    say "  ########## $1 ##########"
    sed 's/^/    /' "$1" >> "$REPORT" 2>&1
    cp "$1" "$OUTDIR/text/$2" 2>/dev/null
}
for f in startup local; do
    show "$DC2/DC/bin/mv162/$f"         "dc2-$f.txt"
    show "$DC1/DC/ppc/bin/ppc604/$f"    "dc1-$f.txt"
done
for f in "$DC2/DC"/IMP_Startup* "$DC1/DC/ppc"/IMP_Startup* \
         "$DC1/DC/ppc/data"/IMP_Startup*; do
    [ -f "$f" ] && show "$f" "imp-$(basename "$f").txt"
done
show "$G/external/vxWorks/vxUsers" "vxUsers.txt"

# --- 4. manifests ------------------------------------------------------------
sec "manifests"
manifest() {   # manifest <dir> <name>
    [ -d "$1" ] || { note "  SKIP manifest $1 -- not present"; return; }
    note "  manifest for $2 ..."
    ( cd "$1" && ls -lR . ) > "$OUTDIR/manifests/$2.ls-lR.txt" 2>&1
    [ -n "$MD5CMD" ] && ( cd "$1" && find . -type f -print | while read f; do
        $MD5CMD "$f"; done ) > "$OUTDIR/manifests/$2.md5.txt" 2>&1
}
manifest "$DC2"                       gem5-gnirs-DC
manifest "$DC1"                       epics3134-gnirs-DC
manifest "$G/gnirs/vw"                gnirs-vw
manifest "$G/external/vxWorks/tornado2.0/mv2700-niri" mv2700-niri
manifest "$G/external/GEM5"           GEM5
manifest "$G/dhs/dhs/lib/mv2700T2"    dhs-lib-mv2700T2
manifest "$G/dhs/dhs/external/lib/mv2700T2" dhs-ext-mv2700T2

# --- 5. tarballs -------------------------------------------------------------
# -h follows symlinks, so DC -> V1-13 is captured as content.
tar_tree() {   # tar_tree <parent> <name> <outfile-base>
    if [ ! -d "$1/$2" ]; then note "  SKIP $1/$2 -- not present"; return; fi
    _kb=`cd "$1" && du -skL "$2" 2>/dev/null | awk '{print $1}'`
    _mb=`expr ${_kb:-0} / 1024`
    note "  $1/$2 -- ${_mb} MB"
    if [ "$_mb" -gt "$LIMIT_MB" ]; then
        note "    SKIPPED: over LIMIT_MB=$LIMIT_MB. Re-run with LIMIT_MB=`expr $_mb + 100`."
        return
    fi
    ( cd "$1" && tar cfh - "$2" ) | gzip > "$OUTDIR/tars/$3.tar.gz" 2>/dev/null
    note "    -> tars/$3.tar.gz (`wc -c < "$OUTDIR/tars/$3.tar.gz"` bytes)"
}

sec "tarballs"
tar_tree "$DC2" DC  dc2-deployed             # what DC2 boots (via the DC link)
tar_tree "$DC1" DC  dc1-deployed             # what DC1 boots
tar_tree "$G/gnirs" vw gnirs-vw              # DC2's mv162 kernel and symbols
tar_tree "$G/external/vxWorks/tornado2.0" mv2700-niri kernel-mv2700-niri
for lib in slalib timelib astlib; do         # GEM5 libs DC2 loads by link
    tar_tree "$G" "$lib" "gem5-$lib"
done

# --- 6. wrap up --------------------------------------------------------------
sec "summary"
run du -sh "$OUTDIR"
run ls -l "$OUTDIR/tars"

FINAL=/tmp/gnirsdc-gather-`uname -n | sed 's/\..*//'`-`date +%Y%m%d`.tar.gz
( cd `dirname "$OUTDIR"` && tar cf - `basename "$OUTDIR"` ) | gzip > "$FINAL"

echo ""
echo "============================================================="
echo "DONE.  Report: $REPORT"
echo "       All:    $FINAL (`wc -c < "$FINAL"` bytes)"
echo ""
echo "  Copy it back with:"
echo "    scp `uname -n`:$FINAL ~/work/gnirsdc-migration/"
echo "============================================================="
