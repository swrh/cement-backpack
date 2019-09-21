#if !defined(EXCEPTION_HPP)
#define EXCEPTION_HPP

#include <stdexcept>

class
Exception
: public std::exception
{
private:
	const char *reason;
public:
	Exception(const char *reason_)
		: reason(reason_)
	{
	}

	virtual const char *what() const noexcept
	{
		return reason;
	}

};

#endif // !defined(EXCEPTION_HPP)

// vim:set sw=4 ts=4 noet:
