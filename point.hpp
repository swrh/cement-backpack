#if !defined(POINT_HPP)
#define POINT_HPP

#include <ostream>

template <typename T>
struct
Point
{
	typedef T value_type;

	value_type x, y;

	bool
	operator==(const Point<T> &other) const
	{
		return x == other.x && y == other.y;
	}

	bool
	operator!=(const Point<T> &other) const
	{
		return !this->operator==(other);
	}

	Point<T> &
	operator++()
	{
		++x;
		++y;
		return *this;
	}

	Point<T>
	operator++(int)
	{
		Point<T> p(*this);
		++(*this);
		return p;
	}

	Point<T> &
	operator--()
	{
		--x;
		--y;
		return *this;
	}

	Point<T>
	operator--(int)
	{
		Point<T> p(*this);
		--(*this);
		return p;
	}

	Point<T> &
	operator+=(const Point<T> &other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Point<T> &
	operator-=(const Point<T> &other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Point<T> &
	operator*=(const Point<T> &other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Point<T> &
	operator/=(const Point<T> &other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	Point<T>
	operator+(const Point<T> &other) const
	{
		Point<T> p(*this);
		p += other;
		return p;
	}

	Point<T>
	operator-(const Point<T> &other) const
	{
		Point<T> p(*this);
		p -= other;
		return p;
	}

	Point<T>
	operator*(const Point<T> &other) const
	{
		Point<T> p(*this);
		p *= other;
		return p;
	}

	Point<T>
	operator/(const Point<T> &other) const
	{
		Point<T> p(*this);
		p /= other;
		return p;
	}

	Point<T> &
	operator+=(value_type value)
	{
		(*this) += Point<T>(value, value);
		return *this;
	}

	Point<T> &
	operator-=(value_type value)
	{
		(*this) -= Point<T>(value, value);
		return *this;
	}

	Point<T> &
	operator*=(value_type value)
	{
		(*this) *= Point<T>(value, value);
		return *this;
	}

	Point<T> &
	operator/=(value_type value)
	{
		(*this) /= Point<T>(value, value);
		return *this;
	}

	Point<T>
	operator+(value_type value) const
	{
		Point<T> p(*this);
		p += Point<T>(value, value);
		return p;
	}

	Point<T>
	operator-(value_type value) const
	{
		Point<T> p(*this);
		p -= Point<T>(value, value);
		return p;
	}

	Point<T>
	operator*(value_type value) const
	{
		Point<T> p(*this);
		p *= Point<T>(value, value);
		return p;
	}

	Point<T>
	operator/(value_type value) const
	{
		Point<T> p(*this);
		p /= Point<T>(value, value);
		return p;
	}

	friend std::ostream &
	operator<<(std::ostream &stream, const Point<T> &p)
	{
		return stream << p.x << ',' << p.y;
	}
};

#endif // !defined(POINT_HPP)

// vim:set sw=4 ts=4 noet:
