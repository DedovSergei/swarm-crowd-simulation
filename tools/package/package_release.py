"""Builds the release archives from a clean checkout of the release commit. Run from the repository root, in an x64 Native Tools command prompt:

  python tools/package/package_release.py [--version v1.0] [--out dist]

Writes into --out:
  SWARM-<version>-windows-x64.zip    SWARM.exe, the shaders, the venue files, README.md, LICENSE, THIRD_PARTY_NOTICES.txt, navcache/ of venues S and M
  SWARM-<version>-navcache-L.zip     navcache/ of venue L, optional, extracted into the program folder
  SWARM-<version>-SHA256.txt         the archives' checksums

The program is built in out/build/package without the source tree's path (SWARM_EMBED_SOURCE_DIR off). The navigation tables are built fresh there by
nav_probe, whatever the build folder held before. The zip's README.md is the repository's with every relative link as a full URL at the release's tag.
The script stops if the tree is not clean, if the program needs a Visual C++ runtime DLL other than vcomp140.dll (MSVC has no static OpenMP runtime; the
README sends users to Microsoft's Redistributable for it), if it holds a path of this machine, or if the README links to a missing file or has a placeholder.
"""
import ctypes
import glob
import hashlib
import os
import re
import shutil
import subprocess
import sys
import time
import zipfile

VERSION = sys.argv[sys.argv.index("--version") + 1] if "--version" in sys.argv else "v1.0"
OUT = sys.argv[sys.argv.index("--out") + 1] if "--out" in sys.argv else "dist"
BUILD = os.path.join("out", "build", "package")
PROGRAM_TABLES = ("S", "M")
OPTIONAL_TABLES = {"L": ("L",)}
REPO ="https://github.com/DedovSergei/swarm-crowd-simulation"
DOCS = ("LICENSE", "THIRD_PARTY_NOTICES.txt")
ASSETS = ("stadium.obj", "stadium.sdf", "venue_s.obj")
RUNTIME_DLL = re.compile(r"^(msvcp|vcruntime|concrt|vccorlib|ucrtbase|api-ms-win-crt)", re.I)
MD_LINK = re.compile(r"(!?)\[([^\]]*)\]\(([^)\s]+)\)")
PLACEHOLDER = re.compile(r"\[(THESIS LINK|SCREENSHOT)")
NO_WINDOW = 0x08000000


def stop(message):
    sys.exit("package_release: " + message)


def run(cmd, env=None, quiet=False):
    """No console window and no error box: a failure shows as the exit code."""
    print("  $ " + " ".join(cmd), flush=True)
    t0 = time.time()
    p = subprocess.run(cmd, env=env, stdin=subprocess.DEVNULL, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, creationflags=NO_WINDOW)
    out = p.stdout.decode("utf-8", "replace")
    print(f"    exit {p.returncode}, {time.time() - t0:.1f} s", flush=True)
    if p.returncode != 0:
        print(out[-4000:])
        stop("failed: " + " ".join(cmd))
    return out


def machine_paths():
    """The byte strings of this machine's paths, in the forms a program can hold them."""
    home = os.path.expanduser("~")
    root = os.getcwd()
    texts = {"C:/Users", "C:\\Users"}
    for p in (home, root):
        texts |= {p, p.replace("\\", "/"), p.replace("\\", "\\\\")}
    return [t.encode("utf-8") for t in texts] + [t.encode("utf-16-le") for t in texts]


def check_program(exe):
    imports = run(["dumpbin", "/nologo", "/dependents", exe], quiet=True)
    dlls = re.findall(r"^\s+(\S+\.dll)\s*$", imports, re.M | re.I)
    print("    imports:", ", ".join(dlls))
    bad = [d for d in dlls if RUNTIME_DLL.match(d)]
    if bad:
        stop(f"{exe} needs runtime DLLs: {bad}")
    data = open(exe, "rb").read()
    hits = [t for t in machine_paths() if t in data]
    if hits:
        stop(f"{exe} holds a path of this machine: {hits[:4]}")
    print("    no path of this machine in the program")


def write_release_readme(path):
    """Relative links lead nowhere in a zip, so each becomes a full URL. An image gets ?raw=true: a blob URL alone serves a web page, not the picture."""
    text = open("README.md", encoding="utf-8", newline="").read()

    def full_url(m):
        bang, label, target = m.groups()
        if re.match(r"https?://", target):
            return m.group(0)
        if not os.path.isfile(target):
            stop(f"README.md links to a missing file: {target}")
        return f"{bang}[{label}]({REPO}/blob/{VERSION}/{target}{'?raw=true' if bang else ''})"

    text, n = MD_LINK.subn(full_url, text)
    if PLACEHOLDER.search(text):
        stop("README.md still has a placeholder")
    with open(path, "w", encoding="utf-8", newline="") as f:
        f.write(text)
    print(f"  the zip's README.md: {n} links, every relative one now under {REPO}/blob/{VERSION}/", flush=True)


def add_tree(zf, src, arc):
    zf.write(src, arc)
    return os.path.getsize(src)


def write_zip(path, entries):
    t0 = time.time()
    total = 0
    with zipfile.ZipFile(path, "w", zipfile.ZIP_DEFLATED, compresslevel=6, allowZip64=True) as zf:
        for src, arc in entries:
            total += add_tree(zf, src, arc)
    print(f"  {os.path.basename(path)}: {len(entries)} files, {total / 1e6:.1f} MB -> {os.path.getsize(path) / 1e6:.1f} MB, {time.time() - t0:.1f} s", flush=True)


def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def table_entries(cache, venues):
    files = []
    for v in venues:
        found = sorted(glob.glob(os.path.join(cache, f"nav_{v}_*.bin")))
        if len(found) != 2:
            stop(f"expected venue {v}'s field and exit choice table in {cache}, found {found}")
        files += [(f, "navcache/" + os.path.basename(f)) for f in found]
    return files


def write_archives(exe, cache):
    """Extracted anywhere, the program zip is a working program with S's and M's tables in navcache/ beside it. The optional zips hold navcache/ too, so extracting one into the program folder adds its tables there."""
    os.makedirs(OUT, exist_ok=True)
    for old in glob.glob(os.path.join(OUT, f"SWARM-{VERSION}-*")):
        os.remove(old)   # an archive of an earlier layout must not stay beside these
    readme = os.path.join(BUILD, "README_release.md")
    write_release_readme(readme)
    entries = [(exe, "SWARM.exe"), (readme, "README.md")]
    entries += [(os.path.join(BUILD, a), a) for a in ASSETS]
    shaders = sorted(glob.glob(os.path.join(BUILD, "shaders", "*")))
    if not shaders:
        stop("no shaders in the build folder")
    entries += [(s, "shaders/" + os.path.basename(s)) for s in shaders]
    entries += [(d, d) for d in DOCS]
    entries += table_entries(cache, PROGRAM_TABLES)
    archives = [os.path.join(OUT, f"SWARM-{VERSION}-windows-x64.zip")]
    write_zip(archives[0], entries)
    for label, venues in OPTIONAL_TABLES.items():
        archives.append(os.path.join(OUT, f"SWARM-{VERSION}-navcache-{label}.zip"))
        write_zip(archives[-1], table_entries(cache, venues))

    sums = os.path.join(OUT, f"SWARM-{VERSION}-SHA256.txt")
    with open(sums, "w", encoding="utf-8", newline="\n") as f:
        for a in archives:
            f.write(f"{sha256(a)}  {os.path.basename(a)}\n")
    print(open(sums, encoding="utf-8").read())


def main():
    ctypes.windll.kernel32.SetErrorMode(0x8003)
    if not shutil.which("dumpbin"):
        stop("run this in an x64 Native Tools command prompt (dumpbin is not on PATH)")
    dirty = subprocess.check_output(["git", "status", "--porcelain"], text=True)
    if dirty.strip():
        stop("the tree is not clean:\n" + dirty)
    commit = subprocess.check_output(["git", "rev-parse", "--short", "HEAD"], text=True).strip()
    print(f"release {VERSION} at commit {commit}", flush=True)

    print("building", flush=True)
    run(["cmake", "-S", ".", "-B", BUILD, "-G", "Ninja", "-DCMAKE_BUILD_TYPE=Release", "-DSWARM_EMBED_SOURCE_DIR=OFF"])
    run(["cmake", "--build", BUILD, "--target", "SWARM", "nav_probe"])
    exe = os.path.join(BUILD, "SWARM.exe")
    print("checking the program", flush=True)
    check_program(exe)

    print("building the navigation tables fresh", flush=True)
    cache = os.path.join(BUILD, "navcache")
    if os.path.exists(cache):
        shutil.rmtree(cache)
    env = {k: v for k, v in os.environ.items() if k != "SWARM_NAV_CACHE"}
    report = os.path.join(BUILD, "nav_build_report")
    run([os.path.join(BUILD, "nav_probe.exe"), "build", "--venues", "S,M,L", "--out", report], env=env)
    text = open(os.path.join(report, "nav_build.md"), encoding="utf-8").read()
    if "reload differs" in text or "not saved" in text:
        stop("a table did not save or reload identically: " + os.path.join(report, "nav_build.md"))

    print("writing the archives", flush=True)
    write_archives(exe, cache)
    print("done", flush=True)


if __name__ == "__main__":
    main()
