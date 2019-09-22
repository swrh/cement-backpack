#if !defined(MATRIX_HPP)
#define MATRIX_HPP

#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "exception.hpp"

template <typename T> class
Matrix
{
public:
	typedef std::size_t size_type;
	typedef std::vector<T> container_type;
	typedef typename container_type::const_iterator const_iterator;
	typedef typename container_type::iterator iterator;
	typedef typename container_type::const_reference const_reference;
	typedef typename container_type::reference reference;
	typedef typename container_type::value_type value_type;

private:
	container_type data;
	size_type width, height;

public:
	Matrix()
		: width(0), height(0)
	{
	}

	Matrix(size_type w, size_type h)
		: data(w * h), width(w), height(h)
	{
	}

	Matrix(size_type w, size_type h, const container_type &d)
		: data(d), width(w), height(h)
	{
		if (data.size() != (width * height))
			throw Exception("Matrix: invalid width/height");
	}

	Matrix(size_type w, size_type h, container_type &&d)
		: data(d), width(w), height(h)
	{
		if (data.size() != (width * height))
			throw Exception("Matrix: invalid width/height");
	}

	Matrix(const Matrix &other)
		: data(other.data), width(other.width), height(other.height)
	{
	}

	Matrix(Matrix &&other)
		: data(other.data), width(other.width), height(other.height)
	{
		other.width = 0;
		other.height = 0;
	}

public:
	Matrix &
	operator=(const Matrix &other)
	{
		if (this == &other)
			return *this;
		data = other.data;
		width = other.width;
		height = other.height;
		return *this;
	}

	Matrix &
	operator=(Matrix &&other)
	{
		if (this == &other)
			return *this;
		swap(other);
		return *this;
	}

	bool
	operator==(const Matrix &other) const
	{
		return (width == other.width) &&
			(height == other.height) &&
			(data == other.data);
	}

	const_reference
	operator[](size_type i) const
	{
		return data[i];
	}

	reference
	operator[](size_type i)
	{
		return data[i];
	}

	const_iterator
	begin() const
	{
		return data.begin();
	}

	iterator
	begin()
	{
		return data.begin();
	}

	const_iterator
	end() const
	{
		return data.end();
	}

	iterator
	end()
	{
		return data.end();
	}

	size_type
	size() const
	{
		return data.size();
	}

	size_type
	getWidth() const
	{
		return width;
	}

	size_type
	getHeight() const
	{
		return height;
	}

public:
	const_reference
	operator()(size_type x, size_type y) const
	{
		return data[width * y + x];
	}

	reference
	operator()(size_type x, size_type y)
	{
		return data[width * y + x];
	}

	const_reference
	at(size_type x, size_type y) const
	{
		return data.at(width * y + x);
	}

	reference
	at(size_type x, size_type y)
	{
		return data.at(width * y + x);
	}

public:
	void
	resize(size_type w, size_type h)
	{
		data.resize(w * h);
		width = w;
		height = h;
	}

public:
	void
	swap(Matrix &other)
	{
		using std::swap;
		data.swap(other.data);
		swap(width, other.width);
		swap(height, other.height);
	}

public:
	friend bool
	operator<(const Matrix &left, const Matrix &right)
	{
		const auto &ld = left.data;
		const auto &rd = right.data;

		if (ld.size() < rd.size())
			return true;

		for (auto l = ld.begin(), r = rd.begin(); l != ld.end() && r != rd.end(); ++l, ++r) {
			if (*l < *r)
				return true;
		}

		return false;
	}

	friend std::ostream &
	operator<<(std::ostream &out, const Matrix &m)
	{
		out << "(";
		for (size_type y = 0; y < m.getHeight(); ++y) {
			if (y != 0)
				out << ", ";
			out << "(";
			for (size_type x = 0; x < m.getWidth(); ++x) {
				if (x != 0)
					out << ", ";
				out << m.data[y * m.getWidth() + x];
			}
			out << ")";
		}
		out << ")";
		return out;
	}
};

template <typename T> Matrix<T>
makeMatrix(typename Matrix<T>::size_type w, typename Matrix<T>::size_type h)
{
	return Matrix<T>(w, h);
}

#endif // !defined(MATRIX_HPP)

// vim:set sw=4 ts=4 noet:
