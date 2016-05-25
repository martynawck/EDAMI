#include "config.h"
#include "error.h"


Config::Config(std::string const& config_file)
{
	ini.LoadFile(config_file.c_str());
	ini.SetUnicode();
}

const char * Config::read(std::string const& section, std::string const& field)
{
	auto value = ini.GetValue(section.c_str(), field.c_str(), nullptr);
	if (value == nullptr) throw Error("No config field does provide value: " + section + "/" + field);
	return value;
}
