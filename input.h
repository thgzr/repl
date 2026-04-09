#pragma once

#include <iostream>
#include <string>
#include <cctype>

#include "command.h"

std::string askForInput() {
	std::cout << "Waiting for command (type 'help' for command list)" << std::endl;
	std::cout << ">>";
	std::string input;
	std::getline(std::cin, input);
	return input;
}

void parseInput(std::string& input, std::string& command, std::string& argument) {
	size_t index = 0;
	bool seen_whitespace = false;
	input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));									// trim leading whitespaces.

	while (index < input.size()) {
		if (std::isspace(static_cast<unsigned char>(input[index]))) seen_whitespace = true;	// commands may be separated by tab, new line, etc from arguments.
		if (seen_whitespace) argument += input[index];
		else command += input[index];
		++index;
	}
	argument.erase(0, argument.find_first_not_of(" \t\n\r\f\v"));							// same here.
}

std::unique_ptr<Command> commandToPtr(std::string command, std::string argument) {
	if (command == "exit")		return std::make_unique<Exit>();
	if (command == "help")		return std::make_unique<Help>();
	if (command == "time")		return std::make_unique<Time>();
	if (command == "greet")		return std::make_unique<Greet>(argument);
	if (command == "yell")		return std::make_unique<YellSomething>(argument);
	if (command == "reverse")	return std::make_unique<ReverseString>(argument);
	return std::make_unique<UnknownCommand>(command);
}

