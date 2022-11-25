#!/bin/sh
print_lint_header() {
    echo "\n***** ${1} *****"
}

print_lint_header "CPPLINT"
cpplint --extensions=cpp --recursive ./server_side/* ./client_side/* ./tests/*

print_lint_header "SUCCESS"