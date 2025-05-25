#!/bin/sh
# Usage: ./hex2class.sh input.hex output.class

if [ $# -ne 2 ]; then
  echo "Usage: $0 input.hex output.class"
  exit 1
fi

# Remove everything after # (inline and full-line comments), then whitespace
sed 's/#.*//' "$1" | tr -d ' \n' > /tmp/hex2class_clean.hex
# Convert to binary
xxd -r -p /tmp/hex2class_clean.hex > "$2"

echo "Class file written to $2"
echo