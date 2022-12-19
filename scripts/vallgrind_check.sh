#!/bin/sh
print_lint_header() {
    echo "\n***** ${1} *****"
}
print_lint_header "VALLGRIND"
VALGRIND_LOG="valgrind.log"

valgrind --tool=memcheck --leak-check=summary --leak-check=full --track-origins=yes --log-file=${VALGRIND_LOG} "$@" || exit 1

cat ${VALGRIND_LOG}
print_lint_header "SUCCESS"
#Для запука использовать из директории проекта: sh scripts/vallgrind_check.sh "здесь_имя_бинарника_проекта"
#Внимание! Не скомпилипованные утилитой (g++) файлы .cpp не будут обрабатываться скриптом.