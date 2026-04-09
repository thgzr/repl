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

CommandEnum commandToEnum(std::string command) {
	if (command == "exit")		return CommandEnum::Exit;
	if (command == "help")		return CommandEnum::Help;
	if (command == "time")		return CommandEnum::Time;
	if (command == "greet")		return CommandEnum::Greet;
	if (command == "yell")		return CommandEnum::YellSomething;
	if (command == "reverse")	return CommandEnum::ReverseString;
	return CommandEnum::Unknown;
}

std::unique_ptr<Command> commandToPtr(std::string command, std::string argument) {
	switch (commandToEnum(command)) {
	case CommandEnum::Exit:				return std::make_unique<Exit>();
	case CommandEnum::Help:				return std::make_unique<Help>();
	case CommandEnum::Time:				return std::make_unique<Time>();
	case CommandEnum::Greet:			return std::make_unique<Greet>(argument);
	case CommandEnum::YellSomething:	return std::make_unique<YellSomething>(argument);
	case CommandEnum::ReverseString:	return std::make_unique<ReverseString>(argument);
	default:							return std::make_unique<UnknownCommand>(command);
	}
}
