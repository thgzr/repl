#include <string>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "tokenizer.h"

Token constructToken(TokenType t_type, long long val) {
	Token t;
	t.type = t_type;
	t.value = val;
	return t;
}

bool isAllowed(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ' ') return true;
	return false;
}

void stringToTokens(std::string str, std::vector<Token>& t) {
	std::string tmp;
	for (const auto c : str) {
		if (isdigit(c)) {
			tmp += c;
			continue;
		}
		if (tmp.size() > 0) {
			try {
				t.push_back(constructToken(TokenType::NUMBER, std::stoll(tmp)));
			}
			catch (const std::out_of_range&) {
				throw std::runtime_error("Provided number is out of range");
			}
			catch (const std::invalid_argument&) {
				throw std::runtime_error("Unable to convert string into integer");
			}
			tmp = "";
		}

		if (!isAllowed(c)) throw std::runtime_error("Invalid character detected");
		
		if (c == '+') t.push_back(constructToken(TokenType::PLUS, 0));
		if (c == '-') t.push_back(constructToken(TokenType::MINUS, 0));
		if (c == '*') t.push_back(constructToken(TokenType::MULTIPLY, 0));
		if (c == '/') t.push_back(constructToken(TokenType::DIVIDE, 0));
		if (c == '(') t.push_back(constructToken(TokenType::LPAREN, 0));
		if (c == ')') t.push_back(constructToken(TokenType::RPAREN, 0));
	}
	if (tmp.size() > 0) {
		t.push_back(constructToken(TokenType::NUMBER, stoll(tmp)));
		tmp = "";
	}
	t.push_back(constructToken(TokenType::END, 0));
}