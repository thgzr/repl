#pragma once

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <utility>

#include "tokenizer.h"

class Command {
public:
	virtual void execute() = 0;
	virtual ~Command() = default;
};

class Invoker {
public: 
	Invoker(std::unique_ptr<Command> cmd) : cmd_(std::move(cmd)) {};
	~Invoker() = default;

	void invoke() {
		cmd_->execute();
	}
private:
	std::unique_ptr<Command> cmd_;
};


class Help : public Command {
public:
	void execute() {
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "List of available commands (case sensitive): " << std::endl;
		std::cout << "eval: math expression. currently accepts only numbers, (), and +, -, /, *: expression example (2 + 2) * 10 / 5" << std::endl;
		std::cout << "time: for getting current time" << std::endl;
		std::cout << "greet: for greeting" << std::endl;
		std::cout << "yell: for YELLING SOMETHING LOUD" << std::endl;
		std::cout << "reverse: for reversing your message" << std::endl;
		std::cout << "exit: to stop this application" << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
	}
};

class Time : public Command {
public:
	void execute() override {
		auto time_now = std::chrono::system_clock::now();
		std::cout << "Current UTC time is: " << time_now << std::endl;
	}
};

class Exit : public Command {
public:
	void execute() override {
		std::cout << "Bye. Thank you for using REPL!" << std::endl;
		std::exit(0);
	}
};

class Greet : public Command {
public:
	Greet(std::string person_name) : person_name_(person_name) {}
	void execute() override {
		if(person_name_.size() > 0) std::cout << "Salutations, dear " << person_name_ << std::endl;
		else std::cout << "Salutations, dear incognito" << std::endl;
	}
private:
	std::string person_name_;
};

class UnknownCommand : public Command {
public:
	UnknownCommand(std::string command) : command_(command) {};
	void execute() override {
		if (command_.size() > 0) std::cout << command_ << " is unknown command" << std::endl;
	}
private:
	std::string command_;
};

class YellSomething : public Command {
public :
	YellSomething(std::string string_to_yell) : string_to_yell_(string_to_yell) {}
	void execute() override {
		if (string_to_yell_.size() > 0) {
			for (char& c : string_to_yell_) c = std::toupper(c);
			std::cout << string_to_yell_ << std::endl;
		}
		else std::cout << "please provide argument to yell" << std::endl;
	}
private:
	std::string string_to_yell_;
};

class ReverseString : public Command {
public:
	ReverseString(std::string string_to_reverse) : string_to_reverse_(string_to_reverse) {}
	void execute() override {		
		if (string_to_reverse_.size() > 0) {
			std::reverse(string_to_reverse_.begin(), string_to_reverse_.end());
			std::cout << string_to_reverse_ << std::endl;
		}
		else std::cout << "please provide argument to reverse" << std::endl;
	}
private:
	std::string string_to_reverse_;
};

class Computator : public Command {
public:
	Computator(std::string string_to_compute) : string_to_compute_(string_to_compute) {
		iterator_ = 0;
	}
	void execute() override;

private:
	Token getCurrentToken();
	void consumeToken();

	long long expression();
	long long term();
	long long factor();

	bool rangeCheck(long long operand1, long long operand2);

	std::string string_to_compute_;
	std::vector<Token> token_vec_;
	size_t iterator_;
};
