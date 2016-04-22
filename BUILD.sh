#! /usr/bin/env bash

clang -D_XOPEN_SOURCE=700 -O3 -std=c99 -g3 -Wall -Wextra -Wpedantic -DKJ_DEBUG -lpthread -lrt test.c && ./a.out

exit 1
