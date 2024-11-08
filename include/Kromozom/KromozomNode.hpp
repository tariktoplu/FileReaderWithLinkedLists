#ifndef KromozomNode_HPP
#define KromozomNode_HPP

#include <iostream>
using namespace std;
#include <fstream>
#include "../Gen/GenList.hpp"

class KromozomNode
{
public:
	GenList *genList;
	KromozomNode *next;
	KromozomNode *prev;

	KromozomNode(KromozomNode *next = NULL, KromozomNode *prev = NULL)
	{
		this->genList = new GenList();
		this->next = next;
		this->prev = prev;
	}
	~KromozomNode()
	{
		delete genList;
	}
	GenList *getGeneList() const
	{
		return genList;
	}
};

#endif
