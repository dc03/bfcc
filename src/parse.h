#include <stdint.h>
#include <stdio.h>

enum TokenType {
	LEFT_IND, RIGHT_IND, LEFT_ANGLE, RIGHT_ANGLE, PLUS, MINUS, READ, WRITE
};

struct Token {
	enum TokenType type;
	size_t byte;
};

struct Token *parse(FILE *source);