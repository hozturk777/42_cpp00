#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <string>

class Column {
	private:
		std::string _str;
	public:
		Column(std::string _s);
		~Column();
		std::string getColumn() const;
};

std::ostream& operator<<(std::ostream& os, const Column& col);

#endif