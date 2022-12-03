#!/bin/sh
print_lint_header() {
    echo "\n***** ${1} *****"
}
print_lint_header "CPPCHECK"
cppcheck --std=c++17 ./server_side/ ./client_side/ ./tests/
print_lint_header "SUCCESS"