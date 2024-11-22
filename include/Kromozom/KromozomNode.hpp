#ifndef KromozomNode_HPP
#define KromozomNode_HPP

#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
class GenList;

class KromozomNode
{
public:
	GenList *genList;
	KromozomNode *next;
	KromozomNode *prev;

	KromozomNode(GenList *genList = nullptr, KromozomNode *next = nullptr, KromozomNode *prev = nullptr);
	GenList *getGeneList() const;
};

#endif
