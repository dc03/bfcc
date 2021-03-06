#ifndef PARSE_H
#define PARSE_H

/* Copyright (C) 2021 Dhruv Chawla */
/* See LICENSE at project root for license details */

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
