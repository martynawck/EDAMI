#pragma once
#include <string>
#include "simpleini.h"

class Config {
private:
	CSimpleIniA ini;
public:
	Config(std::string const& config_file);
	template<class T> T value(std::string const& section, std::string const& field);
	template<> int value<int>(std::string const& section, std::string const& field) { return atoi(read(section, field)); }
	template<> double value<double>(std::string const& section, std::string const& field) { return atof(read(section, field)); }
	template<> std::string value<std::string>(std::string const& section, std::string const& field) { return std::string(read(section, field)); }
private:
	const char* read(std::string const& section, std::string const& field);
};