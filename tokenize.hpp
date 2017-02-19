#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::getline;

enum VariantType { NoneType, BoolType, NumberType, SymbolType };

template<typename T>
struct Atom {
	VariantType atomType = NoneType;
	T data;
};

template<typename T>
struct node {
	vector<node<T>*> children;
	node<T>* parent;
	Atom<T> atom;


};

template<typename T>
class Tokenize
{
public:

	vector<string> tokenize(string expression);

	bool buildAST(vector<string> token); // what should I store as boolean type when making the tree?

	void traversePostOrder(node<string> *currentNode);

	node<T>* head;
	node<T>* tail;
	node<T>* currentNode;

private:
	

};

#include "tokenize.cpp"

#endif


