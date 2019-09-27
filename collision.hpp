#if !defined(COLLISION_HPP)
#define COLLISION_HPP

class
Collision
{
public:
	static bool AABB(const SDL_Rect &a, const SDL_Rect &b)
	{
		return (((a.x + a.w) >= b.x) &&
				((a.y + a.h) >= b.y) &&
				((b.x + b.w) >= a.x) &&
				((b.y + b.h) >= a.y));
	}

};

#endif // !defined(COLLISION_HPP)

// vim:set sw=4 ts=4 noet:
