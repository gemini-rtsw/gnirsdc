#!/bin/bash
# Check a finished build of both crates before it ships. The spec runs this
# after `make`; a developer can run it after a local build -- same checks, so a
# build that passes here passes in the pipeline.
#
#   make -C ppc && make && ./tools/linux-build/check-build.sh
#
# The EPICS 3.12 recursive make (DC2) exits 0 even when a sub-directory fails,
# so the object lists below are the only thing that catches a missing object.
# They are exactly what each crate's startup loads from its own tree.
set -u
TOP="$(cd "$(dirname "$0")/../.." && pwd -P)"
cd "$TOP"
. tools/linux-build/build.conf
rc=0
fail() { echo "ERROR: $*" >&2; rc=1; }

# --- DC1: gnirsdc-1-vme, ppc/ ------------------------------------------------
B=ppc/bin/ppc604
for o in globals coadGlobals sockutil bc350time getTime gnSocketIntrfc \
         gnDataCoAdder dqrpc; do
    [ -f "$B/$o.o" ] || fail "$B/$o.o was not built"
done
[ -f ppc/data/IMP_Startup.ngnirsdc1 ] || fail "ppc/data/IMP_Startup.ngnirsdc1 missing"

# --- DC2: gnirsdc-2-vme, top level -------------------------------------------
B2=bin/mv162
for o in sockutil globals epicsGlobals cicsLib cicsLib2 getTime bc350time \
         HKVars omega b014Driver vxddldnet devAoWFireMessage WFMsgUtilities \
         download eprpc gemLogMsg cadTasks gnDQSocket healthChk; do
    [ -f "$B2/$o.o" ] || fail "$B2/$o.o was not built"
done
for f in data/default.dctsdr data/nirsTop.db data/nirsSadTop.db \
         tpSource/tp/nifs/NAACtp.nif kernel/mv162/vxWorks kernel/mv162/vxWorks.sym; do
    [ -f "$f" ] || fail "$f missing"
done

# --- the generated startup scripts -------------------------------------------
# Each must cd into its deploy path (the path the boot parameters name, through
# production's DC link) and mount from the new boot server.
for pair in "$B:$DC1_DEPLOY" "$B2:$DC2_DEPLOY"; do
    d=${pair%%:*}; dep=${pair#*:}
    for f in startup local; do
        grep -q "cd \"$dep\"" "$d/$f" 2>/dev/null \
            || fail "$d/$f does not cd to $dep: $(grep '^cd ' "$d/$f" 2>/dev/null | head -1)"
    done
    grep -q "nfsMount \"$IOCPATH_HOST\", \"/gemini\"" "$d/local" \
        || fail "$d/local does not mount /gemini from $IOCPATH_HOST"
    grep -n 'pisces' "$d/startup" "$d/local" | grep -v '^[^:]*:[0-9]*:#' \
        | sed 's/^/  /' | grep . >&2 && fail "$d still names pisces (above)"
done

# Nothing that ships may name the build directory or a versioned release dir.
# (DC2's other startup.* variants are not shipped; see the spec.)
grep -lI -e '/root/rpmbuild' -e "$TOP" -e 'DC/V1-1[0-9]' \
     "$B"/startup "$B"/local "$B2"/startup "$B2"/local ppc/data/* 2>/dev/null \
    | sed 's/^/  /' | grep . >&2 && fail "build directory or V1-xx path in files that ship (above)"

# DC2's objects must be a.out, which is what its vxWorks 5.2 loader reads.
file "$B2/cadTasks.o" | grep -q 'a.out' || fail "$B2/cadTasks.o is not a.out: $(file -b "$B2/cadTasks.o")"

[ $rc -eq 0 ] && echo "check-build: OK"
exit $rc
