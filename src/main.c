#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cg.h"
#include "error.h"
#include "parse.h"

void print_usage(const char *prog) {
    printf("Usage: %s [in] [out]\n", prog);
}

bool check_ext(const char *file_name, const char *ext) {
    size_t len = strlen(file_name);
    size_t expected = strlen(ext);
    if (len < expected + 1) {
        // Expect at least one character file name before extension
        return false;
    }

    int i = len - 1;
    for (; i >= 0; i--) {
        // Find the last '.' in the string
        if (file_name[i] == '.') {
            break;
        }
    }

    if (strcmp(&file_name[i], ext) == 0) {
        return true;
    }
    return false;
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

    if (!check_ext(in_name, ".bf")) {
        error("unknown extension for infile '%s', need '.bf'", in_name);
        exit(EXIT_FAILURE);
    }
    if (!check_ext(out_name, ".s")) {
        error("unknown extension for outfile '%s', need '.s'", out_name);
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen(in_name, "rt");
    FILE *out = fopen(out_name, "wb");

    if (in == NULL) {
        error("unable to open file '%s'", in_name);
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }
    if (out == NULL) {
        error("unable to open file '%s'", out_name);
        fclose(in);
        fclose(out);
        exit(EXIT_FAILURE);
    }

    struct TokenStream parsed = parse(in);
    generate(out, out_name, parsed);
    free(parsed.toks);

    fclose(in);
    fclose(out);

    return 0;
}
