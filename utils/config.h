#pragma once
#include <string>
#include <map>
#include <set>
#include <boost\property_tree\ptree.hpp>
#include "simpleini.h"

class Config {
private:
	std::map<std::string, std::string> values;
public:
	Config(std::string const& options);

	template<class T> T value(std::string const& name);
	template<> int value<int>(std::string const& name) { return atoi(read(name)); }
	template<> double value<double>(std::string const& name) { return atof(read(name)); }
	template<> std::string value<std::string>(std::string const& name) { return std::string(read(name)); }
private:
	const char* read(std::string const& name);
};