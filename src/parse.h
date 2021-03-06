#ifndef PARSE_H
#define PARSE_H

#include <stdint.h>
#include <stdio.h>

enum TokenType {
	LEFT_IND, RIGHT_IND, LEFT_ANGLE, RIGHT_ANGLE,
	INCREMENT, DECREMENT, READ, WRITE, END_OF_FILE, NONE
};

struct TokenStream {
	enum TokenType *toks;
	size_t length;
	size_t capacity;
};

struct TokenStream parse(FILE *source);

#endif // parse.h
