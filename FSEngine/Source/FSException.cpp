#include "../Header/FSException.h"

FSException::FSException(const string& message)
{
	this->message = message;
}

FSException::FSException(const string& message, int line, const string& function, const string& file)
{
	this->message = BuildMessageString(message, line, function, file);
}

string FSException::BuildMessageString(const string& message, int line, const string& function, const string& file) const
{
	return "FSException: \"" + message + "\"\nThrown on line " + std::to_string(line) + " in " + function + "() in file " + file + "\n";
}

const char* FSException::what() const noexcept
{
	return message.c_str();
}
