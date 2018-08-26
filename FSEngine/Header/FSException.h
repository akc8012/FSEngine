#pragma once
#include <exception>
#include <string>
using std::string;

class FSException : public std::exception
{
private:
	string message;

	string BuildMessageString(const string& message, int line, const string& function, const string& file) const;

public:
	FSException(const string& message);
	FSException(const string& message, int line, const string& function, const string& file);
	const char* what() const noexcept override;
};

#define throwFS(message) throw FSException(message, __LINE__, __func__, __FILE__);
