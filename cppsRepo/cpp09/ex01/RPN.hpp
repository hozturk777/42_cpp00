#ifndef RPN_HPP
#define RPN_HPP

#include <list>
#include <stack>
#include <string>

class RPN
{
private:
	// stack varsayilan olarak deque kullanir; deque ex02'de lazim, o yuzden list
	std::stack<long, std::list<long> >	_stack;

	void	applyOperator(char op);

public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	long	evaluate(const std::string& expr);
};

#endif
