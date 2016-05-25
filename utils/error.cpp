#include "error.h"

Error::Error(std::string message): msg(message)
{
}

const char * Error::what() const
{
	return msg.c_str();
}
