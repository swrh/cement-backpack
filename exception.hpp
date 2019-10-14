#if !defined(EXCEPTION_HPP)
#define EXCEPTION_HPP

#include <stdexcept>
#include <string>

class
Exception
: public std::exception
{
private:
	const std::string reason_;
public:
	Exception(const char *reason)
		: Exception(std::string(reason))
	{
	}

	Exception(const std::string &reason)
		: Exception(std::string(reason))
	{
	}

	Exception(std::string &&reason)
		: reason_(reason)
	{
	}

	virtual const char *what() const noexcept
	{
		return reason_.c_str();
	}
};

#endif // !defined(EXCEPTION_HPP)

// vim:set sw=4 ts=4 noet:
