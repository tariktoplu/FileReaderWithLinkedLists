#ifndef KROMOZOMLIST_HPP
#define KROMOZOMLIST_HPP

#include "KromozomNode.hpp"
#include "../Exceptions/NoSuchElement.hpp"

using namespace std;

class KromozomList
{
private:
	KromozomNode *head;
	int size;
	KromozomNode *quarterNode;
	KromozomNode *midNode;
	KromozomNode *threeQuarterNode;

	int quarterIndex;
	int midIndex;
	int threeQuarterIndex;

	void updateReferencePoints();
	KromozomNode *FindPreviousByPosition(int index);

public:
	KromozomList();
	void Caprazlama(int index1, int index2);
	void Mutasyon(int index, int column);
	KromozomNode *FindKromNodeByPosition(int index);
	int Count() const;
	bool isEmpty() const;
	void add(GenList *genList) throw(NoSuchElement);
	void removeAt() throw(NoSuchElement);
	void clear();
	friend ostream &operator<<(ostream &screen, KromozomList &rgt);
	~KromozomList();
};

#endif