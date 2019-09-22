#if !defined(POINT_HPP)
#define POINT_HPP

#include <ostream>

class
Point
{
public:
	typedef std::size_t value_type;

private:
	value_type x, y;

public:
	Point()
		: Point(0, 0)
	{
	}

	Point(value_type x, value_type y)
		: x(x), y(y)
	{
	}

	value_type getX() const
	{
		return x;
	}

	value_type getY() const
	{
		return y;
	}

	void setX(value_type x_)
	{
		x = x_;
	}

	void setY(value_type y_)
	{
		y = y_;
	}

	bool operator==(const Point &other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Point &other) const
	{
		return !this->operator==(other);
	}

	Point &operator++()
	{
		++x;
		++y;
		return *this;
	}

	Point operator++(int)
	{
		Point p(*this);
		++(*this);
		return p;
	}

	Point &operator--()
	{
		--x;
		--y;
		return *this;
	}

	Point operator--(int)
	{
		Point p(*this);
		--(*this);
		return p;
	}

	Point &operator+=(const Point &other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Point &operator-=(const Point &other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Point &operator*=(const Point &other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Point &operator/=(const Point &other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	Point operator+(const Point &other) const
	{
		Point p(*this);
		p += other;
		return p;
	}

	Point operator-(const Point &other) const
	{
		Point p(*this);
		p -= other;
		return p;
	}

	Point operator*(const Point &other) const
	{
		Point p(*this);
		p *= other;
		return p;
	}

	Point operator/(const Point &other) const
	{
		Point p(*this);
		p /= other;
		return p;
	}

public:
	friend std::ostream &operator<<(std::ostream &stream, const Point &p)
	{
		return stream << p.x << ',' << p.y;
	}

};

#endif // !defined(POINT_HPP)

// vim:set sw=4 ts=4 noet:
