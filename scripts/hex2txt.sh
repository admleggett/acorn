#!/bin/bash
# hexargs2bin.sh - Convert hex arguments to binary

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 <hex1> <hex2> ... (e.g., cafe babe 00 34)"
    exit 1
fi

# Join all args into a single hex string (remove spaces)
hexstr=$(printf "%s" "$@" | tr -d ' ')

# Convert hex string to binary using xxd
echo "$hexstr" | xxd -r -p

# echo newline
echo