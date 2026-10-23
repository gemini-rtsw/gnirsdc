#!/bin/bash
# Verify the gnirsdc-1-vme and gnirsdc-2-vme installs on the boot server.
# Reads the INSTALLED startup scripts and checks that every file each crate
# loads at boot exists, so it stays correct if the load lists change.
#
#   bash check-install.sh          (copy it to the boot server first)
DC1=/gemini/epics3.13.4/gnirs/DC/DC/ppc
DC2=/gemini/GEM5/gnirs/DC/DC
rc=0
note() { printf "  %-6s %s\n" "$1" "$2"; if [ "$1" = FAIL ]; then rc=1; fi; return 0; }

echo "== packages"
for p in gnirsdc-1-vme gnirsdc-2-vme; do
    rpm -q $p >/dev/null 2>&1 && note OK "$(rpm -q $p)" || note FAIL "$p not installed"
done
out=$(rpm -V gnirsdc-1-vme gnirsdc-2-vme 2>&1 | grep -v 'Permission denied')
[ -z "$out" ] && note OK "rpm -V: every file matches the package" \
    || { note FAIL "rpm -V differences:"; echo "$out" | sed 's/^/           /'; }

# Every path a startup script loads: ld, <, dbLoad, dbLoadRecords, pvload,
# iocInit and initHkArray, with or without a space after ld <. Relative paths
# are relative to the tree the script cd's into.
loads() {   # loads <script> <tree>
    grep -v '^[[:space:]]*#' "$1" \
    | grep -oE '(ld[[:space:]]*<|^<|dbLoad|dbLoadRecords|pvload|iocInit|initHkArray)[[:space:]]*"?[./A-Za-z0-9_-]+' \
    | sed -E 's/^(ld[[:space:]]*<|<|dbLoad|dbLoadRecords|pvload|iocInit|initHkArray)[[:space:]]*"?//' \
    | grep -E '^[./]' | sort -u \
    | while read -r p; do echo "${p/#./$2}"; done
}
for pair in "$DC1/bin/ppc604:$DC1" "$DC2/bin/mv162:$DC2"; do
    b=${pair%%:*}; t=${pair#*:}
    for s in startup local; do
        echo "== everything $b/$s loads"
        [ -f "$b/$s" ] || { note FAIL "$b/$s missing -- the crate boots this"; continue; }
        for f in $(loads "$b/$s" "$t"); do
            [ -e "$f" ] && note OK "$f" || note FAIL "$f"
        done
    done
done

echo "== DC2 transputer network (ldnet runs in tpSource/tp/nifs)"
for f in "$DC2/tpSource/tp/nifs/NAACtp.nif" "$DC2/tpSource/tp/tld/icon.tld" "$DC2/tpSource/tp/tld/seq.tld"; do
    [ -f "$f" ] && note OK "$f" || note FAIL "$f"
done

echo "== kernels"
for f in /gemini/external/vxWorks/tornado2.0/mv2700-niri/vxWorks \
         /gemini/external/vxWorks/tornado2.0/mv2700-niri/vxWorks.sym \
         /gemini/gnirs/vw/mv162/vxWorks /gemini/gnirs/vw/mv162/vxWorks.sym; do
    [ -e "$f" ] && note OK "$f" || note FAIL "$f"
done

echo "== the file server the crates mount"
for b in "$DC1/bin/ppc604" "$DC2/bin/mv162"; do
    grep -q 'nfsMount "mkotcsbootv2-lv1", "/gemini"' "$b/local" && note OK "$b/local mounts mkotcsbootv2-lv1" \
        || note FAIL "$b/local does not mount mkotcsbootv2-lv1 -- wrong build"
done

echo "== boot server: does it serve the DC crates?"
E=/etc/nfsv2-bootserver/tcs/exports; R=/etc/nfsv2-bootserver/tcs/rhosts
v=$(rpm -q nfsv2-bootserver-tcs 2>/dev/null) || v="nfsv2-bootserver-tcs not installed"
note INFO "$v"
systemctl is-active -q nfsv2-bootserver-tcs && note OK "nfsv2-bootserver-tcs service running" \
    || note FAIL "nfsv2-bootserver-tcs service not running"
for ip in 10.2.2.83 10.2.2.84; do
    for e in /gemini /gemdata; do
        grep -E "^$e " "$E" 2>/dev/null | grep -q "$ip(" \
            && note OK "$e exported to $ip" || note FAIL "$e NOT exported to $ip -- install the REL-5058 boot server"
    done
    grep -q "^$ip " "$R" 2>/dev/null && note OK "rhosts has $ip" \
        || note FAIL "rhosts lacks $ip -- the crate's kernel load over rsh will be refused"
done
echo
[ $rc -eq 0 ] && echo "ALL CHECKS PASSED" || echo "SOMETHING IS MISSING -- see FAIL lines above"
exit $rc
