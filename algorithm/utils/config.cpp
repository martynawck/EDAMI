#include <boost\property_tree\ini_parser.hpp>
#include <iostream>
#include "config.h"
#include "error.h"

using std::string;

Config::Config(string const& config_path)
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(config_path, pt);
	for (auto const& section: pt) {
		for (auto const& element: section.second) {
			string key = section.first + "." + element.first;
			values[key] = element.second.data();
		}
	}
}

const char* Config::read(std::string const& name)
{
	return values.at(name).c_str();
}
