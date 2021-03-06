/* Copyright (C) 2021 Dhruv Chawla */
/* See LICENSE at project root for license details */
#include <stdarg.h>
#include <stdio.h>

#include "error.h"

void error(const char *message, ...) {
    va_list args;
    va_start(args, message);
    fprintf(stderr, "error: ");
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    va_end(args);
}
