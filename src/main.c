#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "error.h"

void print_usage(const char *prog) {
	printf("Usage: %s [in] [out]\n", prog);
}

int main(const int argc, const char *argv[]) {
	if (argc == 1 || argc > 3) {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	const char *in_name = argv[1];
	const char *out_name = "out.s";
	if (argc == 3) {
		out_name = argv[2];
	}

	FILE *in = fopen(in_name, "rt");
	FILE *out = fopen(out_name, "wb");

	

	fclose(in);
	fclose(out);

	return 0;
}