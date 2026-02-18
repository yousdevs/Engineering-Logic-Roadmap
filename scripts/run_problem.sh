
#!/usr/bin/env bash
# Compile and run a single problem file from a module directory.
# Usage:
#   scripts/run_problem.sh 01                      # runs 05-Algorithms-L2/01-*.cpp
#   scripts/run_problem.sh 05-Algorithms-L2 01     # runs specified module and index
#   scripts/run_problem.sh path/to/file.cpp        # runs explicit file

set -euo pipefail

DEFAULT_MODULE="05-Algorithms-L2"

if [ "$#" -eq 0 ]; then
  echo "Usage: $0 [module] <index|file>" >&2
  echo "Or: $0 <index> (module defaults to ${DEFAULT_MODULE})" >&2
  exit 2
fi

if [ "$#" -eq 1 ]; then
  MODULE="$DEFAULT_MODULE"
  QUERY="$1"
else
  MODULE="$1"
  QUERY="$2"
fi

# if query is a path to file
if [ -f "$QUERY" ]; then
  FILE="$QUERY"
else
  # if query looks like NN-... or ends with .cpp
  if [[ "$QUERY" == *.cpp ]]; then
    FILE="$MODULE/$QUERY"
  else
    # try to find a file that starts with the query (e.g., "01" or "01-multiplication...")
    shopt -s nullglob
    matches=("$MODULE/${QUERY}"*.cpp)
    shopt -u nullglob
    if [ ${#matches[@]} -gt 0 ]; then
      FILE="${matches[0]}"
    else
      echo "No matching file found in $MODULE for query '$QUERY'" >&2
      echo "Existing files:" >&2
      ls -1 "$MODULE"/*.cpp 2>/dev/null || true
      exit 3
    fi
  fi
fi

if [ ! -f "$FILE" ]; then
  echo "File not found: $FILE" >&2
  exit 4
fi

# prepare build output
OUTDIR="./bin"
mkdir -p "$OUTDIR"
OUTBIN="$OUTDIR/run_problem"

# compile
if command -v g++ >/dev/null 2>&1; then
  echo "Compiling $FILE..."
  g++ -std=c++17 -O2 -Wall "$FILE" -o "$OUTBIN"
  echo "Running...\n"
  "$OUTBIN"
else
  echo "g++ not found in PATH. Please install a C++ compiler or compile manually: g++ -std=c++17 -O2 $FILE -o ./bin/run_problem" >&2
  exit 5
fi

