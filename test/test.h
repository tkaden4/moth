/* test.h
 * Utilities for tests */

#pragma once

#include<stdio.h>
#include<unistd.h>

#define failwith(code, fmt, ...) \
    ({ fprintf(stderr, fmt "\n", ##__VA_ARGS__); _exit(code); })
