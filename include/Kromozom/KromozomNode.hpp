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

	KromozomNode(KromozomNode *next = NULL, KromozomNode *prev = NULL);
	~KromozomNode();
	GenList *getGeneList() const;
};

#endif
