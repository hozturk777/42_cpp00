#include "Contact.hpp"

Contact::Contact(){
}
Contact::~Contact(){
}

std::string Contact::getFirstName() const
{
	return (this->_name);
}

std::string Contact::getSurName() const
{
	return (this->_surName);
}

std::string Contact::getNickName() const
{
	return (this->_nickName);
}

std::string Contact::getPhoneNumber() const
{
	return (this->_phoneNumber);
}

std::string Contact::getDarkestSecret() const
{
	return (this->_darkestSecret);
}

void Contact::setFirstName(std::string _name)
{
	this->_name = _name;
}

void Contact::setSurName(std::string _surName)
{
	this->_surName = _surName;
}

void Contact::setNickName(std::string _nickName)
{
	this->_nickName = _nickName;
}

void Contact:: setPhoneNumber(std::string _phoneNumber)
{
	this->_phoneNumber = _phoneNumber;
}

void Contact::setDarkestSecret(std::string _darkestSecret)
{
	this->_darkestSecret = _darkestSecret;
}