#!/bin/sh
print_lint_header() {
    echo "\n***** ${1} *****"
}
print_lint_header "COVERAGE"
cmake -B build
cmake --build build
print_lint_header "REPORT"
gcovr -s ./build --filter ../server_side/ --filter ../client_side/ #--xml coverage.xml
print_lint_header "SUCCESS"