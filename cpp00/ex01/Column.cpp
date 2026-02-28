#include "Column.hpp"
#include <iostream>
#include <iomanip>


Column::Column(std::string _s) : _str(_s) {

}
Column::~Column(){

}

std::string Column::getColumn() const
{
	return (this->_str);
}

std::ostream& operator<<(std::ostream& os, const Column& col)
{
	std::string temp = col.getColumn();

	if(temp.length() > 10)
	{
		temp = temp.substr(0, 9);
		temp += ".";
	}

	os << std::setw(10) << temp;
	return os;
}
