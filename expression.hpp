#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "tokenize.hpp"

class Expression
{
public:

	// Default construct an Expression of type None
	Expression();

	// Construct an Expression with a single Boolean atom with value
	Expression(bool value);

	// Construct an Expression with a single Number atom with value
	Expression(double value);

	// Construct an Expression with a single Symbol atom with value
	Expression(const std::string & value);

	// Equality operator for two Expressions, two expressions are equal if the have the same 
	// type, atom value, and number of arguments
	bool operator==(const Expression & exp) const noexcept;

	void defineMethod();
	
	void evaluateTree();

private:
	
	
};


#endif