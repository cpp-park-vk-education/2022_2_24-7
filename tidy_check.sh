#!/bin/sh
print_lint_header() {
    echo "\n***** ${1} *****"
}

CODE_FILES="server_side/server/src/*.cpp server_side/server/include/*.hpp \
server_side/text_editor/src/*.cpp server_side/text_editor/include/*.hpp \
server_side/DB/src/*.cpp server_side/DB/include/*.hpp \
client_side/src/*.cpp client_side/include/*.hpp "

INCLUDE_FILES="-Iserver_side/server/include -Iserver_side/text_editor/include -Iserver_side/DB/include -Iclient_side/include"

print_lint_header "CLANG-TIDY"

clang-tidy $CODE_FILES -warnings-as-errors=* -extra-arg=-std=c++17 -- $INCLUDE_FILES

print_lint_header "SUCCESS"