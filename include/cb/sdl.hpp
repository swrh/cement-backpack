#if !defined(CB_SDL_HPP)
#define CB_SDL_HPP

#include <stdexcept>
#include <string>

namespace cb {

class
SdlError
: public std::exception
{
private:
	const std::string what_;

public:
	SdlError(const char *function)
		: what_(std::string(function) + ": " + SDL_GetError())
	{
	}

	virtual const char *
	what() const noexcept override
	{
		return what_.c_str();
	}
};

class
SdlInit
{
public:
	SdlInit()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw SdlError("SDL_Init");
	}

	~SdlInit()
	{
		SDL_Quit();
	}
};

}

#endif // !defined(CB_SDL_HPP)
