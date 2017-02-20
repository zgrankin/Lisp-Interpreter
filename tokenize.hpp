#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include "expression.hpp"

class Environment;

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

	std::vector<string> tokenize(string expression);

	bool buildAST(std::vector<string> token); // what should I store as boolean type when making the tree?

	void traversePostOrder(Expression* currentNode);

	void destroyAST(Expression* currentNode);

	Expression* head;
	Expression* tail;
	Expression* currentNode;
	Environment* environment;

private:
	

};

//#include "tokenize.cpp"

#endif


