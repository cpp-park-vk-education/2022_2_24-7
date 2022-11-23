#!/bin/bash

append_newline () {
    if [ -z "$(tail -c 1 "$1")" ]; then
        :
    else
        echo >> "$1"
    fi
}

THIS_PATH="$(realpath "$0")"
THIS_DIR="$(dirname "$THIS_PATH")"

FILE_LIST="$(find "$THIS_DIR/" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"

echo -e "Files found to format = \n\"\"\"\n$FILE_LIST\n\"\"\""

# Run clang-format
clang-format --verbose -i --style=file ${FILE_LIST}

# Check newlines
for f in ${FILE_LIST}; do
    append_newline $f
done
