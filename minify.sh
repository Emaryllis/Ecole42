#!/bin/bash
# This script puts all non git-ignored files recursively into a single minified text file.
# It is highly recommended to either copy or symlink this script into one of the path folders.

set -euo pipefail

# Get Unix timestamp
unix_time=$(date +%s)
output_file="minified-${unix_time}.txt"

# Get current script path
current_script_path="$(readlink -f "$0")"

# Try to find parent batch/script path
parent_script_path=""
ppid=$PPID

if [ -d "/proc/$ppid" ]; then
  pcmd=$(cat "/proc/$ppid/cmdline" 2>/dev/null | tr '\0' ' ' || true)
  if [[ "$pcmd" =~ ([^[:space:]]+\.(bat|cmd|sh)) ]]; then
    parent_script_path="${BASH_REMATCH[1]}"
  fi
fi

# Exclusion arrays
exact_exclusions=("$output_file" "LICENSE" "package-lock.json" ".env.example" "next-env.d.ts" ".gitignore")
ext_exclusions=(".ttf" ".db" ".svg" ".ico" ".png" ".jpg" ".jpeg")

# Function to check if value is in array
in_array() {
  local needle="$1"
  shift
  local item
  for item in "$@"; do
    if [[ "$item" == "$needle" ]]; then
      return 0
    fi
  done
  return 1
}

# Create temporary Python scripts
js_minify_script=$(mktemp)
css_minify_script=$(mktemp)
json_minify_script=$(mktemp)
html_minify_script=$(mktemp)
html_minify_script=$(mktemp)
sql_minify_script=$(mktemp)

trap 'rm -f "$js_minify_script" "$css_minify_script" "$json_minify_script" "$html_minify_script" "$sql_minify_script"' EXIT

cat > "$js_minify_script" << 'PYEOF'
import re
import sys

code = sys.stdin.buffer.read().decode('utf-8', 'replace')
store = []

string_pattern = r""""(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|`(?:\\.|[^`\\])*`"""

def protect_literal(m):
  lit = m.group(0)
  lit = re.sub(r'\s+', ' ', lit)
  store.append(lit)
  return f'__LIT_{len(store)-1}__'

code = re.sub(string_pattern, protect_literal, code)

blocks = []

def protect_block(m):
  blk = re.sub(r'\s+', ' ', m.group(0))
  blocks.append(blk)
  return f'__BLK_{len(blocks)-1}__'

code = re.sub(r'/\*[\s\S]*?\*/', protect_block, code)

code = code.replace('\t', '')
code = re.sub(r'(?<![:\w])//[^\r\n]*', '', code)
code = re.sub(r'\s+', ' ', code)
code = re.sub(r'(?<=[^\w\s])\s(?=[^\w\s])', '', code)

for i, blk in enumerate(blocks):
  code = code.replace(f'__BLK_{i}__', blk)

for i, lit in enumerate(store):
  code = code.replace(f'__LIT_{i}__', lit)

print(code.strip())
PYEOF

cat > "$css_minify_script" << 'PYEOF'
import re
import sys

code = sys.stdin.buffer.read().decode('utf-8', 'replace')
store = []

string_pattern = r""""(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'"""

def protect_literal(m):
  lit = m.group(0)
  store.append(lit)
  return f'__LIT_{len(store)-1}__'

code = re.sub(string_pattern, protect_literal, code)

code = code.replace('\t', '')
code = re.sub(r'/\*[\s\S]*?\*/', '', code)
code = re.sub(r'\s+', ' ', code)
code = re.sub(r'(?<=[^\w\s])\s(?=[^\w\s])', '', code)

for i, lit in enumerate(store):
  code = code.replace(f'__LIT_{i}__', lit)

print(code.strip())
PYEOF

cat > "$json_minify_script" << 'PYEOF'
import json
import sys

s = sys.stdin.buffer.read().decode('utf-8', 'replace')

try:
  data = json.loads(s)
  print(json.dumps(data, separators=(',', ':')))
except Exception:
  sys.exit(1)
PYEOF

cat > "$html_minify_script" << 'PYEOF'
import re
import sys

c = sys.stdin.buffer.read().decode('utf-8', 'replace')

c = re.sub(r'<!--.*?-->', '', c, flags=re.DOTALL)
c = re.sub(r'\s+', ' ', c)
c = re.sub(r'>\s+<', '><', c)

print(c.strip())
PYEOF

cat > "$sql_minify_script" << 'PYEOF'
import re
import sys

code = sys.stdin.buffer.read().decode('utf-8', 'replace')
store = []

def protect_literal(m):
  lit = m.group(0)
  lit = re.sub(r'\s+', ' ', lit)
  store.append(lit)
  return f'__LIT_{len(store)-1}__'

# Protect quoted strings/identifiers
code = re.sub(r"'(?:''|\\.|[^'\\])*'", protect_literal, code)
code = re.sub(r'"(?:[^"]|"")*"', protect_literal, code)
code = re.sub(r'`[^`]*`', protect_literal, code)

# Remove comments
code = re.sub(r'/\*[\s\S]*?\*/', ' ', code)
code = re.sub(r'--[^\r\n]*', ' ', code)

# Collapse to one line
code = re.sub(r'\s+', ' ', code)
code = re.sub(r'(?<=[^\w\s])\s(?=[^\w\s])', '', code)

for i, lit in enumerate(store):
  code = code.replace(f'__LIT_{i}__', lit)

print(code.strip())
PYEOF

# Get all tracked and untracked files (excluding standard git ignores)
mapfile -t files < <(git ls-files -c -o --exclude-standard 2>/dev/null || find . -type f ! -path '*/.git/*' | sed 's|^./||')

# Temporary storage for blocks
declare -a blocks=()

for file_path in "${files[@]}"; do
  # Skip empty paths
  [[ -z "$file_path" ]] && continue

  # Skip if file doesn't exist
  [[ ! -f "$file_path" ]] && continue

  # Get file info
  file_name=$(basename "$file_path")
  file_ext=".${file_name##*.}"
  file_ext=$(printf '%s' "$file_ext" | tr '[:upper:]' '[:lower:]')
  full_path=$(readlink -f "$file_path")

  # Skip current script
  if [[ -n "$current_script_path" && "$full_path" == "$current_script_path" ]]; then
    continue
  fi

  # Skip parent script
  if [[ -n "$parent_script_path" && -f "$parent_script_path" ]]; then
    parent_full=$(readlink -f "$parent_script_path")
    if [[ "$full_path" == "$parent_full" ]]; then
      continue
    fi
  fi

  # Skip exact exclusions
  if in_array "$file_name" "${exact_exclusions[@]}"; then
    continue
  fi

  # Skip extension exclusions
  if in_array "$file_ext" "${ext_exclusions[@]}"; then
    continue
  fi

  # Skip specific directories
  if [[ "$file_path" == *.idea/* || "$file_path" == *.next/* ]]; then
    continue
  fi

  # Read file content, normalize Windows line endings
  raw=$(cat "$full_path" | tr -d '\r')

  # Process based on file type
  if [[ "$file_ext" == ".ts" || "$file_ext" == ".tsx" || "$file_ext" == ".js" || "$file_ext" == ".jsx" || "$file_ext" == ".mjs" ]]; then
    raw=$(python3 "$js_minify_script" <<< "$raw")

  elif [[ "$file_ext" == ".css" ]]; then
    raw=$(python3 "$css_minify_script" <<< "$raw")

  elif [[ "$file_ext" == ".html" || "$file_ext" == ".htm" ]]; then
    raw=$(python3 "$html_minify_script" <<< "$raw")

  elif [[ "$file_ext" == ".sql" || "$file_ext" == ".pgsql" || "$file_ext" == ".mysql" ]]; then
    raw=$(python3 "$sql_minify_script" <<< "$raw")

  elif [[ "$file_ext" == ".json" ]]; then
    raw=$(python3 "$json_minify_script" <<< "$raw" 2>/dev/null || printf '%s' "$raw")

  else
    # Keep internal newlines exactly as they are.
    # Remove only trailing blank lines / trailing newlines at end of file.
    raw=$(printf '%s\n' "$raw" | awk '
      { lines[NR] = $0 }
      END {
        last = NR
        while (last > 0 && lines[last] ~ /^[[:space:]]*$/) last--
        for (i = 1; i <= last; i++) print lines[i]
      }
    ')
  fi

  # Add to blocks if not empty
  if [[ -n "$raw" ]]; then
    blocks+=("# $file_path"$'\n'"$raw")
  fi
done

# Write output
if ((${#blocks[@]} > 0)); then
  printf '%s\n' "${blocks[@]}" > "$output_file"
else
  : > "$output_file"
fi

printf '\n'
echo "Done. Output: $output_file"
read -rp "Press Enter to continue..." _ || true