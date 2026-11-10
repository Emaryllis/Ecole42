#ifndef RPN_HPP
#define RPN_HPP

#include <list>
#include <stack>
#include <string>

class RPN {
public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	long evaluate(const std::string &expression);

private:
	// std::stack: an operator always takes the last two operands pushed (last in, first out).
	// std::stack uses std::deque by default, so std::list is given explicitly to keep std::deque free for ex02.
	std::stack<long, std::list<long> > _operands;

	void applyOperator(char op);
};

#endif