#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>
#include <sstream>
//#include <fstream> // not used

#include "../dist/util-mod/util.hpp"

using std::vector;
using std::pair;
using std::string;
using std::ostream;
using std::map;
using std::istringstream;
using std::istream;
using std::stack;
using std::to_string;

class Exception
{
private:
	std::string msg;
	std::string msg_;
public:
	Exception(std::string msg) :
		msg{std::move(msg)}, msg_(std::move(msg)) {}
	std::string toString() const
	{
	return msg;
	}
};

void printProdRule(const pair<string, vector<string>>& prod)
	{
	std::cout << prod.first;
	for (const auto& s : prod.second)
		std::cout << " " << s;
	std::cout << std::endl;
	}

class LR1Machine
{
private:
	using prod_rules_t = vector<pair<string, vector<string>>>;

	
	prod_rules_t prodRules;
	map<pair<int, string>, int> nextStateMap;
	map<pair<int, string>, int> reduceRuleMap;
	vector<string> lines_;
	const vector<string>& rules_;

public:
	LR1Machine(const vector<string>& rules, vector<string> lines):
	lines_(std::move(lines)), rules_(rules)
		{
		for (const auto& rule : rules) 
			{
			vector<string> result;
			istringstream iss(rule);
			string LHS;
			iss >> LHS;
			for (string s; iss >> s; ) result.push_back(s);
			prodRules.push_back({ LHS, result });
			}

		for (auto& line : lines)
			{
			vector<string> result;
			istringstream iss(line);
			for (string s; iss >> s; )
				result.push_back(s);
			if (result.at(2) == "reduce")
				{
				reduceRuleMap.insert(
				{
				  {
						stoi(result.at(0)),
						result.at(1)
						}, stoi(result.at(3))
					});
				}
			else // shift
				{
				nextStateMap.insert(
					{
						{
							stoi(result.at(0)),
							result.at(1)
							}, stoi(result.at(3))
					});
				}
			}
		}

	int getNextState(int state, const string& sym) const
	{
		if (nextStateMap.find({ state, sym }) == nextStateMap.end()) return -1;
		return nextStateMap.find({ state, sym })->second;
	}
	
	pair<string, vector<string>> reduce(int state, string sym) const
	{
		if (reduceRuleMap.find({ state, sym }) == reduceRuleMap.end())
		{
			return { "", {} };
		}
		return prodRules[reduceRuleMap.find({ state, sym })->second];
	}
	
	pair<string, vector<string>> getFirstProdRule() const
	{
		return prodRules.at(0);
	}
};

//Skip the grammar part of the input.
void skipLine(istream& in)
{
	string s;
	getline(in, s);
}

void skipGrammarExceptProd(istream& in)
{
	int i, numTerm, numNonTerm;

	// read the number of terminals and move to the next line
	in >> numTerm;
	skipLine(in);

	// skip the lines containing the terminals
	for (i = 0; i < numTerm; i++) 
	{
		skipLine(in);
	}//end for

	// read the number of non-terminals and move to the next line
	in >> numNonTerm;
	skipLine(in);

	// skip the lines containing the non-terminals
	for (i = 0; i < numNonTerm; i++) 
	{
		skipLine(in);
	}//end for

	// skip the line containing the start symbol
	skipLine(in);
}

void LR_1(vector<string>& s, const LR1Machine& lr1)
{
	stack<int> stateStack;
	stack<string> symStack;
	stateStack.push(0);

	vector<pair<string, vector<string>>> rules;

	for (int i = 0; i < s.size(); i++) 
	{
		pair<string, vector<string>> prod = lr1.reduce(stateStack.top(), s.at(i));
		while (prod.first.empty())
		{
			rules.push_back(prod);
			const int RHS_size = prod.second.size();
			for (auto j = RHS_size; j > 0; j--) 
			{
				symStack.pop();
				stateStack.pop();
			}
			symStack.push(prod.first);
			stateStack.push(lr1.getNextState(stateStack.top(), prod.first));
			prod = lr1.reduce(stateStack.top(), s.at(i));
		}//end while

		symStack.push(s.at(i));
		int nextState = lr1.getNextState(stateStack.top(), s.at(i));
		if (nextState < 0)
		{
			throw Exception("ERROR at " + to_string(i + 1));
		}//end if
		stateStack.push(nextState);
	}//end for
	rules.push_back(lr1.getFirstProdRule());
	for (auto& rule : rules) printProdRule(rule);
}//end LR_1


// LR(1) parsing algorithm, output is unindented reversed rightmost derivation
auto run_lr1_example_1() -> int
{
	// Read in the LR1 file in stdin
	try
	{
		skipGrammarExceptProd(std::cin);
		// read the number of rules and move to the next line
		int numRules;
		std::cin >> numRules;
		skipLine(std::cin);

		// save lines containing the production rules
		vector<string> prodRules;
		string s;
		for (int i = 0; i < numRules; i++)
		{
			getline(std::cin, s);
			prodRules.push_back(s);
		} //end for

		int numStates, numLines;
		std::cin >> numStates;
		std::cin >> numLines;
		skipLine(std::cin);

		vector<string> lines;
		for (int i = 0; i < numLines; i++)
		{
			getline(std::cin, s);
			lines.push_back(s);
		} //end for

		const auto lr1 = LR1Machine(prodRules, lines);

		vector<string> input;
		while (std::cin >> s) input.push_back(s);
		LR_1(input, lr1);
	}
	catch (Exception e) // NOLINT(misc-throw-by-value-catch-by-reference)
	{
		std::cerr << e.toString() << std::endl;
		return 1;
	} //end try-catch
	
	return EXIT_SUCCESS;
}
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>
#include <sstream>
//#include <fstream> // not used

#include "../dist/util-mod/util.hpp"

using std::vector;
using std::pair;
using std::string;
using std::ostream;
using std::map;
using std::istringstream;
using std::istream;
using std::stack;
using std::to_string;

class Exception
{
private:
	std::string msg;
	std::string msg_;
public:
	Exception(std::string msg) :
		msg{std::move(msg)}, msg_(std::move(msg)) {}
	std::string toString() const
	{
	return msg;
	}
};

void printProdRule(const pair<string, vector<string>>& prod)
	{
	std::cout << prod.first;
	for (const auto& s : prod.second)
		std::cout << " " << s;
	std::cout << std::endl;
	}

class LR1Machine
{
private:
	using prod_rules_t = vector<pair<string, vector<string>>>;

	
	prod_rules_t prodRules;
	map<pair<int, string>, int> nextStateMap;
	map<pair<int, string>, int> reduceRuleMap;
	vector<string> lines_;
	const vector<string>& rules_;

public:
	LR1Machine(const vector<string>& rules, vector<string> lines):
	lines_(std::move(lines)), rules_(rules)
		{
		for (const auto& rule : rules) 
			{
			vector<string> result;
			istringstream iss(rule);
			string LHS;
			iss >> LHS;
			for (string s; iss >> s; ) result.push_back(s);
			prodRules.push_back({ LHS, result });
			}

		for (auto& line : lines)
			{
			vector<string> result;
			istringstream iss(line);
			for (string s; iss >> s; )
				result.push_back(s);
			if (result.at(2) == "reduce")
				{
				reduceRuleMap.insert(
				{
				  {
						stoi(result.at(0)),
						result.at(1)
						}, stoi(result.at(3))
					});
				}
			else // shift
				{
				nextStateMap.insert(
					{
						{
							stoi(result.at(0)),
							result.at(1)
							}, stoi(result.at(3))
					});
				}
			}
		}

	int getNextState(int state, const string& sym) const
	{
		if (nextStateMap.find({ state, sym }) == nextStateMap.end()) return -1;
		return nextStateMap.find({ state, sym })->second;
	}
	
	pair<string, vector<string>> reduce(int state, string sym) const
	{
		if (reduceRuleMap.find({ state, sym }) == reduceRuleMap.end())
		{
			return { "", {} };
		}
		return prodRules[reduceRuleMap.find({ state, sym })->second];
	}
	
	pair<string, vector<string>> getFirstProdRule() const
	{
		return prodRules.at(0);
	}
};

//Skip the grammar part of the input.
void skipLine(istream& in)
{
	string s;
	getline(in, s);
}

void skipGrammarExceptProd(istream& in)
{
	int i, numTerm, numNonTerm;

	// read the number of terminals and move to the next line
	in >> numTerm;
	skipLine(in);

	// skip the lines containing the terminals
	for (i = 0; i < numTerm; i++) 
	{
		skipLine(in);
	}//end for

	// read the number of non-terminals and move to the next line
	in >> numNonTerm;
	skipLine(in);

	// skip the lines containing the non-terminals
	for (i = 0; i < numNonTerm; i++) 
	{
		skipLine(in);
	}//end for

	// skip the line containing the start symbol
	skipLine(in);
}

void LR_1(vector<string>& s, const LR1Machine& lr1)
{
	stack<int> stateStack;
	stack<string> symStack;
	stateStack.push(0);

	vector<pair<string, vector<string>>> rules;

	for (int i = 0; i < s.size(); i++) 
	{
		pair<string, vector<string>> prod = lr1.reduce(stateStack.top(), s.at(i));
		while (prod.first.empty())
		{
			rules.push_back(prod);
			const int RHS_size = prod.second.size();
			for (auto j = RHS_size; j > 0; j--) 
			{
				symStack.pop();
				stateStack.pop();
			}
			symStack.push(prod.first);
			stateStack.push(lr1.getNextState(stateStack.top(), prod.first));
			prod = lr1.reduce(stateStack.top(), s.at(i));
		}//end while

		symStack.push(s.at(i));
		int nextState = lr1.getNextState(stateStack.top(), s.at(i));
		if (nextState < 0)
		{
			throw Exception("ERROR at " + to_string(i + 1));
		}//end if
		stateStack.push(nextState);
	}//end for
	rules.push_back(lr1.getFirstProdRule());
	for (auto& rule : rules) printProdRule(rule);
}//end LR_1


// LR(1) parsing algorithm, output is unindented reversed rightmost derivation
auto run_lr1_example_1() -> int
{
	// Read in the LR1 file in stdin
	try
	{
		skipGrammarExceptProd(std::cin);
		// read the number of rules and move to the next line
		int numRules;
		std::cin >> numRules;
		skipLine(std::cin);

		// save lines containing the production rules
		vector<string> prodRules;
		string s;
		for (int i = 0; i < numRules; i++)
		{
			getline(std::cin, s);
			prodRules.push_back(s);
		} //end for

		int numStates, numLines;
		std::cin >> numStates;
		std::cin >> numLines;
		skipLine(std::cin);

		vector<string> lines;
		for (int i = 0; i < numLines; i++)
		{
			getline(std::cin, s);
			lines.push_back(s);
		} //end for

		const auto lr1 = LR1Machine(prodRules, lines);

		vector<string> input;
		while (std::cin >> s) input.push_back(s);
		LR_1(input, lr1);
	}
	catch (Exception e) // NOLINT(misc-throw-by-value-catch-by-reference)
	{
		std::cerr << e.toString() << std::endl;
		return 1;
	} //end try-catch
	
	return EXIT_SUCCESS;
}
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>
#include <sstream>
//#include <fstream> // not used

#include "../dist/util-mod/util.hpp"

using std::vector;
using std::pair;
using std::string;
using std::ostream;
using std::map;
using std::istringstream;
using std::istream;
using std::stack;
using std::to_string;

class Exception
{
private:
	std::string msg;
	std::string msg_;
public:
	Exception(std::string msg) :
		msg{std::move(msg)}, msg_(std::move(msg)) {}
	std::string toString() const
	{
	return msg;
	}
};

void printProdRule(const pair<string, vector<string>>& prod)
	{
	std::cout << prod.first;
	for (const auto& s : prod.second)
		std::cout << " " << s;
	std::cout << std::endl;
	}

class LR1Machine
{
private:
	using prod_rules_t = vector<pair<string, vector<string>>>;

	
	prod_rules_t prodRules;
	map<pair<int, string>, int> nextStateMap;
	map<pair<int, string>, int> reduceRuleMap;
	vector<string> lines_;
	const vector<string>& rules_;

public:
	LR1Machine(const vector<string>& rules, vector<string> lines):
	lines_(std::move(lines)), rules_(rules)
		{
		for (const auto& rule : rules) 
			{
			vector<string> result;
			istringstream iss(rule);
			string LHS;
			iss >> LHS;
			for (string s; iss >> s; ) result.push_back(s);
			prodRules.push_back({ LHS, result });
			}

		for (auto& line : lines)
			{
			vector<string> result;
			istringstream iss(line);
			for (string s; iss >> s; )
				result.push_back(s);
			if (result.at(2) == "reduce")
				{
				reduceRuleMap.insert(
				{
				  {
						stoi(result.at(0)),
						result.at(1)
						}, stoi(result.at(3))
					});
				}
			else // shift
				{
				nextStateMap.insert(
					{
						{
							stoi(result.at(0)),
							result.at(1)
							}, stoi(result.at(3))
					});
				}
			}
		}

	int getNextState(int state, const string& sym) const
	{
		if (nextStateMap.find({ state, sym }) == nextStateMap.end()) return -1;
		return nextStateMap.find({ state, sym })->second;
	}
	
	pair<string, vector<string>> reduce(int state, string sym) const
	{
		if (reduceRuleMap.find({ state, sym }) == reduceRuleMap.end())
		{
			return { "", {} };
		}
		return prodRules[reduceRuleMap.find({ state, sym })->second];
	}
	
	pair<string, vector<string>> getFirstProdRule() const
	{
		return prodRules.at(0);
	}
};

//Skip the grammar part of the input.
void skipLine(istream& in)
{
	string s;
	getline(in, s);
}

void skipGrammarExceptProd(istream& in)
{
	int i, numTerm, numNonTerm;

	// read the number of terminals and move to the next line
	in >> numTerm;
	skipLine(in);

	// skip the lines containing the terminals
	for (i = 0; i < numTerm; i++) 
	{
		skipLine(in);
	}//end for

	// read the number of non-terminals and move to the next line
	in >> numNonTerm;
	skipLine(in);

	// skip the lines containing the non-terminals
	for (i = 0; i < numNonTerm; i++) 
	{
		skipLine(in);
	}//end for

	// skip the line containing the start symbol
	skipLine(in);
}

void LR_1(vector<string>& s, const LR1Machine& lr1)
{
	stack<int> stateStack;
	stack<string> symStack;
	stateStack.push(0);

	vector<pair<string, vector<string>>> rules;

	for (int i = 0; i < s.size(); i++) 
	{
		pair<string, vector<string>> prod = lr1.reduce(stateStack.top(), s.at(i));
		while (prod.first.empty())
		{
			rules.push_back(prod);
			const int RHS_size = prod.second.size();
			for (auto j = RHS_size; j > 0; j--) 
			{
				symStack.pop();
				stateStack.pop();
			}
			symStack.push(prod.first);
			stateStack.push(lr1.getNextState(stateStack.top(), prod.first));
			prod = lr1.reduce(stateStack.top(), s.at(i));
		}//end while

		symStack.push(s.at(i));
		int nextState = lr1.getNextState(stateStack.top(), s.at(i));
		if (nextState < 0)
		{
			throw Exception("ERROR at " + to_string(i + 1));
		}//end if
		stateStack.push(nextState);
	}//end for
	rules.push_back(lr1.getFirstProdRule());
	for (auto& rule : rules) printProdRule(rule);
}//end LR_1


// LR(1) parsing algorithm, output is unindented reversed rightmost derivation
auto run_lr1_example_1() -> int
{
	// Read in the LR1 file in stdin
	try
	{
		skipGrammarExceptProd(std::cin);
		// read the number of rules and move to the next line
		int numRules;
		std::cin >> numRules;
		skipLine(std::cin);

		// save lines containing the production rules
		vector<string> prodRules;
		string s;
		for (int i = 0; i < numRules; i++)
		{
			getline(std::cin, s);
			prodRules.push_back(s);
		} //end for

		int numStates, numLines;
		std::cin >> numStates;
		std::cin >> numLines;
		skipLine(std::cin);

		vector<string> lines;
		for (int i = 0; i < numLines; i++)
		{
			getline(std::cin, s);
			lines.push_back(s);
		} //end for

		const auto lr1 = LR1Machine(prodRules, lines);

		vector<string> input;
		while (std::cin >> s) input.push_back(s);
		LR_1(input, lr1);
	}
	catch (Exception e) // NOLINT(misc-throw-by-value-catch-by-reference)
	{
		std::cerr << e.toString() << std::endl;
		return 1;
	} //end try-catch
	
	return EXIT_SUCCESS;
}
