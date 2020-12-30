#include"DList.h"
#include <typeinfo>
#include"PList.h"
using namespace std;
namespace hw2 {
	//Node
	DNode::DNode(District* info, PList* listOfParties) :next(nullptr), info(info), listOfParties(listOfParties)
	{
	}

	DNode::~DNode()
	{
		delete this->listOfParties;
	}

	//Getters
	DNode* DNode::getNext()const
	{
		return this->next;
	}

	PList* DNode::getListOfParties()const
	{
		return this->listOfParties;
	}

	District* DNode::getInfo()const
	{
		return this->info;
	}
	//Setters

	bool DNode::setNext(DNode* next)
	{
		this->next = next;
		return true;
	}
	bool DNode::setInfo(District* info)
	{
		this->info = info;
		return true;
	}

	bool DNode::setListOfParties(PList* listOfParties)
	{
		this->listOfParties = listOfParties;
		return true;
	}

	bool DNode::save(ofstream& outfile)const
	{
		return this->info->save(outfile);
		//listOfParties->serialSave(outfile);
	}
	bool DNode::pSerialSave(ofstream& outfile)const
	{
		if(!this->info->pSerialSave(outfile))
			return false;
		return this->listOfParties->serialSave(outfile);
	}

	//List
	DList::DList() :size(0), Head(nullptr), Tail(nullptr)
	{
	}
	DList::DList(ifstream& infile)
	{
		int type;
		District* temp;
		infile.read(reinterpret_cast<char*>(&this->size), sizeof(int)); //read the size
		for (int i = 0; i < this->size; i++)
		{
			infile.read(reinterpret_cast<char*>(&type), sizeof(int)); //read the type
			if (type == 1)
			{
				temp = new UnifiedDistrict(infile);
			}
			else
			{
				temp = new DividedDistrict(infile);

			}
			this->addToTail(temp,nullptr);
		}
	}

	DList::~DList()
	{
		while (Head != nullptr) {
			DNode* temp = Head;
			Head = Head->getNext();
			delete temp;
		}
	}
	//Getters
	DNode* DList::getHead()const
	{
		return this->Head;
	}
	DNode* DList::getTail()const
	{
		return this->Tail;
	}

	int DList::getSize()const
	{
		return this->size;
	}

	void DList::addToHead(District* value, PList* listOfParties)
	{
		(this->size)++;
		DNode* temp = new DNode(value, listOfParties);
		temp->setNext(this->Head);
		this->Head = temp;
		if (this->Tail == nullptr)
			this->Tail = this->Head;
	}
	void DList::addToTail(District* value, PList* listOfParties)
	{
		// create new item and set as tail of list
		(this->size)++;
		DNode* temp = new DNode(value, listOfParties);
		temp->setNext(nullptr);

		// handle empty list
		if (this->Head == nullptr)
			this->Head = this->Tail = temp;
		else
		{
			this->Tail->setNext(temp);
			this->Tail = temp;
		}

	}


	bool DList::delHead()
	{
		// remove head item from list
		DNode* temp = this->Head;
		this->Head = this->Head->getNext();

		// handle empty list
		if (this->Head == temp)
			this->Tail = nullptr;
		(this->size)--;

		delete temp;
		return true;
	}
	bool DList::delTail()
	{
		// remove tail item from list
		DNode* temp = this->Tail;
		this->Tail->setNext(nullptr);
		(this->size)--;

		// handle empty list
		if (this->Head == temp)
			this->Head = nullptr;

		delete temp;
		return true;
	}

	void DList::printList()const
	{
		DNode* curr = this->Head;
		while (curr != nullptr)
		{
			cout << curr->getInfo();
			curr = curr->getNext();
		}
	}

	ostream& operator<<(ostream& os, DList& lst)
	{
		DNode* curr = lst.getHead();
		while (curr != nullptr)
		{
			os << typeid(*curr->getInfo()).name() + 11 << "\b"; //prints the type
			os << curr->getInfo();
			curr = curr->getNext();
		}
		return os;
	}

	bool DList::save(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&this->size), sizeof(int)); //write the size
		DNode* curr = Head;
		while (curr != nullptr)
		{
			if(!curr->save(outfile))
				return false;
			curr = curr->getNext();
		}
		return true;
	}
	bool DList::pSerialSave(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&this->size), sizeof(int)); //write the size
		DNode* curr = Head;
		while (curr != nullptr)
		{
			if(!curr->pSerialSave(outfile))
				return false;
			curr = curr->getNext();
		}
		return true;
	}

}