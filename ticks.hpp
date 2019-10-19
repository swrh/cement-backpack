#if !defined(TICKS_HPP)
#define TICKS_HPP

#include <SDL.h>

class
Ticks
{
private:
	Uint32 current_ = 0, last_ = 0;

public:
	Uint32
	now()
	{
		return SDL_GetTicks();
	}

	Uint32
	update()
	{
		last_ = current_;
		return current_ = now();
	}

	Uint32
	current() const
	{
		return current_;
	}

	Uint32
	last() const
	{
		return last_;
	}

	Uint32
	delta() const
	{
		return current_ - last_;
	}
};

#endif // !defined(TICKS_HPP)

// vim:set sw=4 ts=4 noet:
