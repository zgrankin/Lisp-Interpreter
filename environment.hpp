#include <string>
#include <map>
#include "interpreter.hpp"


class Environment {
public:
	Environment();

	bool setVariable(std::string aString, Atom envAtom);
	Atom findVar(std::string aString);

	std::map<std::string, Atom> varMap;

private:
	
};