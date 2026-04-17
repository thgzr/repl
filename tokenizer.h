#pragma once

enum class TokenType {
	NUMBER = 0,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	LPAREN,
	RPAREN,
	END
};

struct Token {
	TokenType type;
	long long value;
};

Token constructToken(TokenType t_type, long long val);
bool isAllowed(char c);
void stringToTokens(std::string str, std::vector<Token>& t);