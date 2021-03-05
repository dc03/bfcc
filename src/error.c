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