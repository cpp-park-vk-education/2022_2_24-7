#!/bin/sh
append_newline () {
    if [ -z "$(tail -c 1 "$1")" ]; then
        :
    else
        echo >> "$1"
    fi
}
THIS_PATH="$(realpath "$0")"
THIS_DIR="$(dirname "$THIS_PATH")"
FILE_LIST1="$(find "$THIS_DIR/client_side" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"
FILE_LIST2="$(find "$THIS_DIR/server_side" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"
FILE_LIST3="$(find "$THIS_DIR/tests" | grep -E ".*(\.cpp|\.h|\.hpp|\.hh)$")"
echo -e "Files found to format = \n\"\"\"\n${FILE_LIST1}\n\"\"\"\n${FILE_LIST2}\n\"\"\"\n${FILE_LIST3}\n\"\"\""
# Run clang-format
clang-format --verbose -i --style=file ${FILE_LIST1}
clang-format --verbose -i --style=file ${FILE_LIST2}
clang-format --verbose -i --style=file ${FILE_LIST3}
for f in ${FILE_LIST1}
do append_newline $f 
done
for f in ${FILE_LIST2}
do append_newline $f 
done
for f in ${FILE_LIST3}
do append_newline $f 
done