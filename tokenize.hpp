#ifndef _TOKENIZE_HPP_
#define _TOKENIZE_HPP_

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "expression.hpp"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::getline;

class Tokenize
{
public:
	Environment* environment;

	std::vector<string> tokenize(string expression);

	bool buildAST(std::vector<string> token); // what should I store as boolean type when making the tree?

	void traversePostOrder(Expression* currentNode);

	//void destroyAST(Expression* currentNode);

	Expression* head;
	Expression* tail;
	Expression* currentNode;

private:
	

};

#endif


