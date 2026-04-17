#pragma once

#include <iostream>
#include <stdexcept>
#include <cmath>

#include "command.h"
#include "tokenizer.h"

Token Computator::getCurrentToken() {
	return token_vec_[iterator_];
}

void Computator::consumeToken() {
	iterator_++;
}

bool Computator::rangeCheck(int operand1, int operand2) {
	int operand1_by_modulus = std::abs(operand1);
	int operand2_by_modulus = std::abs(operand2);

	if (operand1_by_modulus > INT_MAX / operand2_by_modulus) return false;
	else return true;
}

int Computator::expression() {
	int value = term();
	Token t = getCurrentToken();
	while (t.type == TokenType::MINUS || t.type == TokenType::PLUS) {
		consumeToken();
		int rhs = term();
		if (t.type == TokenType::MINUS) {
			if (value - rhs >= INT_MIN) value -= rhs;
			else throw std::runtime_error("Error: during substraction value went out of negative integer range");
		}
		else {
			if (value <= INT_MAX - rhs) value += rhs;
			else throw std::runtime_error("Error: during addition value went out of positive integer range");
		}
		t = getCurrentToken();
	}
	return value;
}

int Computator::term() {
	int value = factor();
	Token t = getCurrentToken();
	while (t.type == TokenType::DIVIDE || t.type == TokenType::MULTIPLY) {
		consumeToken();
		int rhs = factor();
		if (t.type == TokenType::DIVIDE) {
			if (rhs == 0) throw std::runtime_error("Error: division by 0!");
			else 
				if (value == INT_MIN && rhs == -1) throw std::runtime_error("Error: during division value went out of integer range");
				else value /= rhs;
		}
		else {
			if (rangeCheck(value, rhs)) value *= rhs;
			else throw std::runtime_error("Error: during multiplication value went out of integer range");
		}
		t = getCurrentToken();
	}
	return value;
}

int Computator::factor() {
	Token t = getCurrentToken();
	if (t.type == TokenType::LPAREN) {
		consumeToken();
		int value = expression();
		t = getCurrentToken();
		if (t.type == TokenType::RPAREN) {
			consumeToken();
			return value;
		}
		else {
			throw std::runtime_error("Missing ) token");
		}
	}
	else
		if (t.type == TokenType::NUMBER) {
			consumeToken();
			return t.value;
		}
		else {
			if (t.type == TokenType::MINUS) {
				consumeToken();
				return factor() * -1;
			}
			else throw std::runtime_error("Wrong input, please recheck it.");
 		}
}

void Computator::execute() {
	stringToTokens(string_to_compute_, token_vec_);
	int result = expression();
	Token t = getCurrentToken();
	if (t.type != TokenType::END) throw std::runtime_error("Input error");
	else std::cout << result << std::endl;
}


