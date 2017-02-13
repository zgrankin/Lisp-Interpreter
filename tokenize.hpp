#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

struct node {
	string data;
	vector<string> nChildren;
	node* next;
	node* prev;
};

//class Tokenize
//{
//public:


	vector<string> tokenize(string expression);

	bool buildAST(vector<string> token);

//private:


//}

//#include "tokenize.cpp"

#endif
