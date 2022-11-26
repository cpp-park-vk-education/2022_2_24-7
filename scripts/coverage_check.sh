#!/bin/sh
print_lint_header() {
    echo "\n***** ${1} *****"
}
print_lint_header "COVERAGE"
cmake -B build
cmake --build build
gcovr -s ./build --xml coverage.xml --filter ../server_side/ --filter ../client_side/
print_lint_header "SUCCESS"