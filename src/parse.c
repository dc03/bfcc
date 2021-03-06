#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"
#include "parse.h"

static enum TokenType scan(FILE *source) {
    char ch = fgetc(source);
    switch (ch) {
        case '[': return LEFT_IND;
        case ']': return RIGHT_IND;
        case '<': return LEFT_ANGLE;
        case '>': return RIGHT_ANGLE;
        case '+': return INCREMENT;
        case '-': return DECREMENT;
        case ',': return READ;
        case '.': return WRITE;
        case EOF: return END_OF_FILE;
        default: return NONE;
    }
}

static void halt(struct TokenStream *stream, const char *message) {
    free(stream->toks);
    // Attempt to release memory but forget about file handles
    error(message);
    exit(EXIT_FAILURE);
}

static size_t find_loop_end(struct TokenStream *stream, size_t where) {
    size_t i = where + 1;
    for (; i < stream->length; i++) {
        if (stream->toks[i] == RIGHT_IND) {
            return i;
        } else if (stream->toks[i] == LEFT_IND) {
            i = find_loop_end(stream, i);
        }
    }
    if (stream->toks[i] != END_OF_FILE) {
        halt(stream, "expected end of loop but found eof");
    }
    return i; 
}

static void check(struct TokenStream *stream) {
    for (size_t i = 0; i < stream->length; i++) {
        if (stream->toks[i] == LEFT_IND) {
            i += find_loop_end(stream, i);
        } else if (stream->toks[i] == RIGHT_IND) {
            halt(stream, "extra loop end (']') in input");
        }
    }
}

struct TokenStream parse(FILE *source) {
    struct TokenStream stream;
    stream.length = 0;
    stream.capacity = 8;
    stream.toks = (enum TokenType*)malloc(stream.capacity *
                                          sizeof(enum TokenType));
    while (true) {
        enum TokenType tok = scan(source);
        if (tok == NONE) {
            continue;
        }
        if (stream.length >= stream.capacity) {
            stream.capacity *= 2;
            stream.toks = realloc(stream.toks, stream.capacity * sizeof(enum TokenType));
        }
        stream.toks[stream.length++] = tok;
        if (feof(source)) {
            break;
        }
    }
    stream.toks = realloc(stream.toks, (stream.length + 1) * sizeof(enum TokenType));

    check(&stream);
    return stream;
}
