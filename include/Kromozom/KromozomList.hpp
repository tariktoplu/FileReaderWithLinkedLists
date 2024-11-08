#ifndef KROMOZOMLIST_HPP
#define KROMOZOMLIST_HPP

#include "KromozomNode.hpp"
#include "../Exceptions/NoSuchElement.hpp"
/* suanlık hata yok */

/* circ doulbliknedlist */

class KromozomList
{
private:
	KromozomNode *head;
	int size;

	KromozomNode *FindPreviousByPosition(int index)
	{
		KromozomNode *prv = head;
		int i = 1;
		for (KromozomNode *itr = head; i != index; itr = itr->next, i++)
		{
			prv = prv->next;
		}
		return prv;
	}

public:
	KromozomList()
	{
		head = NULL;
		size = 0;
	}
	void Caprazlama(int index1, int index2)
	{
		if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size)
		{
			throw NoSuchElement("Invalid index for crossover.");
		}
		KromozomNode *kromozom1 = elementAt(index1 - 1)->next;
		KromozomNode *kromozom2 = FindPreviousByPosition(index2)->next;

		GenList *genList1 = kromozom1->genList;
		GenList *genList2 = kromozom2->genList;

		genList1->Caprazlama(genList1, genList2);
	}

	void Mutasyon()
	{
	}
	int Count() const
	{
		return size;
	}
	bool isEmpty() const
	{
		return size == 0;
	}
	void add(const char &item)
	{
		insert(size, item);
	}
	void insert(int index, const char &item) throw(NoSuchElement)
	{
		if (index < 0 || index > size)
			throw NoSuchElement("No Such Element");
		if (index == 0)
		{
			if (size == 0)
			{
				head = new KromozomNode(item, head);
				head->next = head->prev = head;
			}
			else
			{
				head = new KromozomNode(item, head, head->prev);
				head->next->prev = head;
				head->prev->next = head;
			}
		}
		else
		{
			KromozomNode *prv = FindPreviousByPosition(index);
			prv->next = new KromozomNode(item, prv->next, prv);
			prv->next->next->prev = prv->next;
		}
		size++;
	}
	const char &first() throw(NoSuchElement) /* sanırım class Gen olacak  */
	{
		if (isEmpty())
			throw NoSuchElement("No Such Element");
		return head->data;
	}
	const char &last() throw(NoSuchElement)
	{
		if (isEmpty())
			throw NoSuchElement("No Such Element");
		return head->prev->data;
	}
	int indexOf(const char &item) throw(NoSuchElement)
	{
		int index = 0;
		for (KromozomNode *itr = head; index < size; itr = itr->next)
		{
			if (itr->data == item)
				return index;
			index++;
		}
		throw NoSuchElement("No Such Element");
	}
	void remove(const char &item)
	{
		int index = indexOf(item);
		removeAt(index);
	}
	void removeAt(int index) throw(NoSuchElement)
	{
		if (index < 0 || index >= size)
			throw NoSuchElement("No Such Element");
		KromozomNode *del;
		if (index == 0)
		{
			del = head;
			if (size == 1)
				head = NULL;
			else
			{
				head = head->next;
				head->prev = del->prev;
				del->prev->next = head;
			}
		}
		else
		{
			KromozomNode *prv = FindPreviousByPosition(index);
			del = prv->next;
			prv->next = del->next;
			del->next->prev = prv;
		}
		size--;
		delete del;
	}
	bool find(const char &item)
	{
		int index = 0;
		for (KromozomNode *itr = head; index < size; itr = itr->next, index++)
		{
			if (itr->data == item)
				return true;
		}
		return false;
	}
	/* elementat düzenlendi ... */
	const GenList &elementAt(int index) throw(NoSuchElement)
	{
		if (index < 0 || index >= size)
			throw NoSuchElement("No Such Element");
		if (index == 0)
			return *head->genList;
		return *FindPreviousByPosition(index)->next->genList;
	}
	void clear()
	{
		while (!isEmpty())
			removeAt(0);
	}
	friend ostream &operator<<(ostream &screen, KromozomList &rgt)
	{
		int index = 0;
		for (KromozomNode *itr = rgt.head; index < rgt.size; itr = itr->next, index++)
		{
			screen << itr->data << " <-> ";
		}
		screen << endl;
		return screen;
	}
	void printNodesFromPositionInReverseOrder(int index) throw(NoSuchElement)
	{
		int i = 0;
		if (index < 0 || index >= size)
			throw NoSuchElement("No Such Element");
		for (KromozomNode *itr = FindPreviousByPosition(index + 1); i < size; itr = itr->prev, i++)
		{
			cout << itr->data << " <-> ";
		}
		cout << endl;
	}
	void printNodesFromPositionInOrder(int index) throw(NoSuchElement)
	{
		int i = 0;
		if (index < 0 || index >= size)
			throw NoSuchElement("No Such Element");
		for (KromozomNode *itr = FindPreviousByPosition(index + 1); i < size; itr = itr->next, i++)
		{
			cout << itr->data << " <-> ";
		}
		cout << endl;
	}
	void printReverseOrder()
	{
		printNodesFromPositionInReverseOrder(size - 1);
	}
	~KromozomList()
	{
		clear();
	}
};

#endif