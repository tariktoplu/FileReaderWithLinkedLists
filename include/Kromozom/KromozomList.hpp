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

public:
	KromozomList();
	void yazdir();
	KromozomNode *FindPreviousByPosition(int);
	void processCommands(KromozomList &);
	void Caprazlama(int, int);
	void Mutasyon(int, int);
	KromozomNode *FindFromNodeByPosition(int);
	int Count() const;
	bool isEmpty() const;
	void add(const GenList &) throw(NoSuchElement);
	void removeAt(int) throw(NoSuchElement);
	void clear();
	friend ostream &operator<<(ostream &, KromozomList &);
	~KromozomList();
};

#endif