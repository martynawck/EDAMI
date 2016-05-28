#pragma once
#include <exception>
#include <string>

class Error: public std::exception {
	const std::string msg;
public:
	Error(std::string message);
	virtual const char* what() const override;
};