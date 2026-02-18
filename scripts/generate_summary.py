#!/usr/bin/env python3
"""
Scan a module directory for .cpp files and extract metadata headers to generate a SUMMARY.md.

Usage:
  python3 scripts/generate_summary.py --dir 05-Algorithms-L2 --output 05-Algorithms-L2/SUMMARY.md --write

The script looks for top-line comments like:
// Title: ...
// Source: ...
// Tags: ...
// Difficulty: ...
// Status: ...
// Date: ...

Only the Title is required for the listing; other fields are optional.
"""
import os
import re
import sys
import argparse

META_KEYS = ["Title", "Source", "Tags", "Difficulty", "Status", "Date"]

parser = argparse.ArgumentParser(description="Generate SUMMARY.md from C++ file headers")
parser.add_argument("--dir", default="05-Algorithms-L2", help="Module directory to scan")
parser.add_argument("--output", default=None, help="Output path for summary (default: stdout)")
parser.add_argument("--write", action="store_true", help="Write output to --output (required to modify files)")
args = parser.parse_args()

module_dir = args.dir

if not os.path.isdir(module_dir):
    print(f"Error: directory not found: {module_dir}", file=sys.stderr)
    sys.exit(2)

cpp_files = sorted([f for f in os.listdir(module_dir) if f.endswith('.cpp')])

entries = []
header_re = re.compile(r"^//\s*([^:]+)\s*:\s*(.*)$")

for fname in cpp_files:
    path = os.path.join(module_dir, fname)
    meta = {k: '' for k in META_KEYS}
    try:
        with open(path, 'r', encoding='utf-8') as fh:
            for _ in range(40):
                line = fh.readline()
                if not line:
                    break
                m = header_re.match(line.strip())
                if m:
                    key = m.group(1).strip()
                    val = m.group(2).strip()
                    if key in META_KEYS:
                        meta[key] = val
                # stop at first non-comment block
                if not line.strip().startswith('//') and line.strip() != '':
                    break
    except Exception as ex:
        print(f"Warning: failed to read {path}: {ex}", file=sys.stderr)
        continue

    # derive index from filename prefix
    idx = fname.split('-', 1)[0] if '-' in fname else fname
    title = meta.get('Title') or fname
    entries.append({
        'index': idx,
        'file': fname,
        'title': title,
        'tags': meta.get('Tags',''),
        'difficulty': meta.get('Difficulty',''),
        'status': meta.get('Status',''),
        'source': meta.get('Source',''),
        'date': meta.get('Date','')
    })

# build markdown
lines = []
lines.append(f"# Module {os.path.basename(module_dir)} — Summary\n")
lines.append("This summary is generated from the metadata headers in each problem file.\n")
lines.append("| # | Title | Tags | Difficulty | Status | File |")
lines.append("|---:|---|---|---|---|---|")
for e in entries:
    file_link = f"[{e['file']}]({os.path.join(module_dir, e['file'])})"
    title = e['title']
    tags = e['tags'] or '-'
    diff = e['difficulty'] or '-'
    status = e['status'] or '-'
    lines.append(f"| {e['index']} | {title} | {tags} | {diff} | {status} | {file_link} |")

out = '\n'.join(lines) + '\n'

if args.output and args.write:
    try:
        with open(args.output, 'w', encoding='utf-8') as fh:
            fh.write(out)
        print(f"Wrote summary to {args.output}")
    except Exception as ex:
        print(f"Error writing output: {ex}", file=sys.stderr)
        sys.exit(3)
else:
    sys.stdout.write(out)

