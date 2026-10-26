#!/usr/bin/env python3
"""Walk each GNIRS DC crate's boot the way vxWorks does, against an installed
tree, and report every host it talks to and every file it needs.

    python3 audit-boot.py PRESET.json [PRESET.json ...]

Run where the RPMs are installed (the boot server, or the pipeline's dev
image). Each argument is a bootsmith preset: its boot parameters are the
starting point -- the kernel and symbol table the boot ROM fetches over rsh
from host_name, then the startup script. The script is followed line by line,
tracking `cd` (DC2 cd's into tpSource for the transputer loader and back), and
every file a line loads must exist. `<` includes are followed recursively, so
`local` is checked too. Any host other than the boot server that the scripts
mount from or authenticate against is an error.
"""
import json, os, re, sys

BOOT_HOST, BOOT_IP = "mkotcsbootv2-lv1", "10.2.2.145"
bad = 0


def fail(msg):
    global bad
    bad += 1
    print("  FAIL  " + msg)


def ok(msg):
    print("  ok    " + msg)


def need(path, why):
    (ok if os.path.exists(path) else fail)("%s  (%s)" % (path, why))


LOADERS = re.compile(
    r'^\s*(ld\s*<|<|dbLoadRecords|dbLoadDatabase|dbLoad|pvload|iocInit|initHkArray)(?=[\s("/.])\s*\(?\s*"?([^",\s)]+)')


def walk(script, cwd, hosts, seen):
    if script in seen:
        return cwd
    seen.add(script)
    need(script, "script")
    if not os.path.exists(script):
        return cwd
    for raw in open(script, errors="replace"):
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        m = re.match(r'^cd\s+"([^"]+)"', line)
        if m:
            cwd = os.path.normpath(os.path.join(cwd, m.group(1)))
            need(cwd, "cd target")
            continue
        for kw in ("nfsMount", "nfsAuthUnixSet", "hostAdd"):
            if line.startswith(kw):
                h = re.findall(r'"([^"]+)"', line)
                if h:
                    hosts.append((kw, h[0], line))
                if kw == "nfsMount" and len(h) == 3:
                    print("  mount %s:%s -> %s" % (h[0], h[1], h[2]))
                    if h[1].startswith("/export"):
                        fail("mount uses pisces-style /export path: " + line)
        m = re.match(r'^ldnet\s+"([^"]+)"', line)
        if m:
            nif = os.path.join(cwd, m.group(1) + ".nif")
            need(nif, "transputer network")
            if os.path.exists(nif):
                for ref in re.findall(r'([./A-Za-z0-9_-]+\.tld)', open(nif).read()):
                    need(os.path.normpath(os.path.join(cwd, ref)), "transputer code in " + os.path.basename(nif))
            continue
        m = LOADERS.match(line)
        if m:
            kind, path = m.group(1), m.group(2)
            full = os.path.normpath(os.path.join(cwd, path))
            if kind == "<":
                cwd = walk(full, cwd, hosts, seen)
            else:
                need(full, kind.replace(" ", ""))
    return cwd


for preset in sys.argv[1:]:
    p = json.load(open(preset))
    bp = p["boot_params"]
    print("== %s" % p["name"])
    if bp["host_name"] != BOOT_HOST or bp["host_inet"] != BOOT_IP:
        fail("boot host is %s/%s, not %s/%s" % (bp["host_name"], bp["host_inet"], BOOT_HOST, BOOT_IP))
    else:
        ok("boot host %s %s" % (BOOT_HOST, BOOT_IP))
    need(bp["file_name"], "kernel, fetched over rsh as %s" % bp["user"])
    need(bp["file_name"] + ".sym", "symbol table, fetched over rsh")
    hosts = []
    deploy = os.path.dirname(os.path.dirname(os.path.dirname(bp["startup_script"])))
    walk(bp["startup_script"], deploy, hosts, set())
    for kw, h, line in hosts:
        if kw in ("nfsMount", "nfsAuthUnixSet") and h != BOOT_HOST:
            fail("%s names %s, not the boot server: %s" % (kw, h, line))
        elif kw == "hostAdd":
            print("  host  %s" % line)
    if not any(kw == "nfsMount" for kw, _, _ in hosts):
        fail("no nfsMount at all")
    # Files DC2 opens after boot, relative to the tree it cd's into: the
    # microcode the arSetup CAD names (TED logs: Path=<./tpSource/ucode/NAAC/>,
    # Name=<gnAIII_1024xSU01_4u>) and the WCS tables sdsuWcs reads.
    if deploy.endswith("/gnirs/DC/DC"):
        for ext in ("cmd", "tld"):
            need(os.path.join(deploy, "tpSource/ucode/NAAC/gnAIII_1024xSU01_4u." + ext), "microcode, at runtime")
        for port in (1, 3, 5):
            for cam in ("long", "short"):
                need(os.path.join(deploy, "data/gnirs_%d_%s.wcs" % (port, cam)), "WCS table, at runtime")

print()
print("AUDIT: %s" % ("ALL OK" if bad == 0 else "%d PROBLEM(S)" % bad))
sys.exit(1 if bad else 0)
