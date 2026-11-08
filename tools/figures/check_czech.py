"""check_czech.py: scan the Czech figure set's SVG text for English words, internal names and Unicode subscript digits.

  python tools/figures/check_czech.py <folder with the Czech SVGs> [--draft]

Prints every offending text element and exits 1 if any. Without --draft the '(ověřit)' marker counts as an offence (the thesis set has
none); with --draft it must appear in the figures that cite references.
"""
import glob
import os
import re
import sys

FORBIDDEN = ["EMPIRICAL", "CONSERVATIVE", "Task", "úloha", "LoS", "verify", "seed", "semínk", "stairs", "level", "venue", "peak", "crush",
             "gangway", "evacuat", "density", "flow", "time", "load", "exit", "the ", " of ", "t_lb"]
SUBSCRIPTS = "₀₁₂₃₄₅₆₇₈₉"


def texts(svg):
    s = open(svg, encoding="utf-8").read()
    # matplotlib writes text as <text ...>...</text> (svg.fonttype none), possibly with nested tspans
    out = []
    for m in re.finditer(r"<text\b[^>]*>(.*?)</text>", s, re.S):
        t = re.sub(r"<[^>]+>", "", m.group(1))
        t = t.replace("&#x2009;", " ").replace("&#160;", " ").strip()
        if t:
            out.append(t)
    return out


def main(argv):
    folder, draft = argv[0], "--draft" in argv
    bad = 0
    seen_verify = set()
    for svg in sorted(glob.glob(os.path.join(folder, "*.svg"))):
        for t in texts(svg):
            hits = [w for w in FORBIDDEN if w in t]
            if any(c in t for c in SUBSCRIPTS):
                hits.append("unicode subscript")
            if "ověřit" in t:
                seen_verify.add(os.path.basename(svg))
                if not draft:
                    hits.append("(ověřit) in the thesis set")
            if hits:
                bad += 1
                print(f"{os.path.basename(svg)}: {hits}: {t[:120]}")
    print(f"{bad} offending text elements; '(ověřit)' in: {', '.join(sorted(seen_verify)) or 'none'}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
