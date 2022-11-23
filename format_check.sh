#!/bin/sh
THIS_PATH="$(realpath "$0")"
THIS_DIR="$(dirname "$THIS_PATH")"
FILE_LIST1="$(find "$THIS_DIR/client_side" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"
FILE_LIST2="$(find "$THIS_DIR/server_side" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"
FILE_LIST3="$(find "$THIS_DIR/tests" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"
echo -e "Files found to format = \n\"\"\"\n$FILE_LIST\n\"\"\""
# Run clang-format
clang-format --verbose -i --style=file ${FILE_LIST1}
clang-format --verbose -i --style=file ${FILE_LIST2}
clang-format --verbose -i --style=file ${FILE_LIST3}