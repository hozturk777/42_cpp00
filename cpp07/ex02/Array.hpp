#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class Array
{
	private:
		T			*_data;
		size_t		_size;

	public:
		Array() : _data(new T[0]), _size(0)
		{
		}

		Array(unsigned int n) : _data(new T[n]), _size(n)
		{
		}

		Array(Array const &src) : _data(new T[src._size]), _size(src._size)
		{
			for (size_t i = 0; i < _size; ++i)
				_data[i] = src._data[i];
		}

		Array &operator=(Array const &src)
		{
			if (this != &src)
			{
				T *tmp = new T[src._size];
				for (size_t i = 0; i < src._size; ++i)
					tmp[i] = src._data[i];
				delete[] _data;
				_data = tmp;
				_size = src._size;
			}
			return (*this);
		}

		~Array()
		{
			delete[] _data;
		}

		T &operator[](size_t index)
		{
			if (index >= _size)
				throw std::out_of_range("Array: index out of bounds");
			return (_data[index]);
		}

		T const &operator[](size_t index) const
		{
			if (index >= _size)
				throw std::out_of_range("Array: index out of bounds");
			return (_data[index]);
		}

		size_t size() const
		{
			return (_size);
		}
};

#endif
