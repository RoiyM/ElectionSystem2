#include"PList.h"
//
namespace hw2 {

	//Node
	PNode::PNode(Party* info) :next(nullptr), info(info), amountOfVotes(0)
	{
	}

	PNode::~PNode()
	{
	}

	//Getters
	PNode* PNode::getNext()const
	{
		return this->next;
	}

	int PNode::getAmountOfVotes()const
	{
		return this->amountOfVotes;
	}

	Party* PNode::getInfo()const
	{
		return this->info;
	}
	//Setters

	bool PNode::setNext(PNode* next)
	{
		this->next = next;
		return true;
	}
	bool PNode::setInfo(Party* info)
	{
		this->info = info;
		return true;
	}

	bool PNode::increaseAmountOfVotesByOne()
	{
		(this->amountOfVotes)++;
		return true;
	}

	bool PNode::save(ofstream& outfile)const
	{
		if(!this->info->save(outfile))
			return false;
		outfile.write(reinterpret_cast<const char*>(&amountOfVotes), sizeof(int));
		return outfile.good();
	}
	bool PNode::serialSave(ofstream& outfile)const
	{
		return this->info->serialSave(outfile);
	}
	bool PNode::pSerialSave(ofstream& outfile)const
	{
		return this->info->pSerialSave(outfile);
	}


	//List
	PList::PList() :Head(nullptr), Tail(nullptr),size(0)
	{
	}
	PList::PList(PList* other) : Head(nullptr), Tail(nullptr),size(other->size)
	{
		PNode* curr = other->Head;
		while (curr != nullptr)
		{
			addToTail(curr->getInfo());
			curr = curr->getNext();
		}
	}
	PList::PList(ifstream& infile)
	{
		infile.read(reinterpret_cast<char*>(&this->size), sizeof(int)); //read the size
		for (int i = 0; i < this->size; i++)
		{
			Party* temp = new Party(infile);
			this->addToTail(temp);
			int aov;
			infile.read(reinterpret_cast<char*>(&aov), sizeof(int)); //read the amount of votes
			this->Tail->setAmountOfVotes(aov);
		}
	}
	PList::~PList()
	{
		while (Head != nullptr) {
			PNode* temp = Head;
			Head = Head->getNext();
			delete temp;
		}
	}
	//Getters
	PNode* PList::getHead()const
	{
		return this->Head;
	}
	PNode* PList::getTail()const
	{
		return this->Tail;
	}
	int PList::getSize()const
	{
		return this->size;
	}


	void PList::addToHead(Party* value)
	{
		PNode* temp = new PNode(value);
		temp->setNext(this->Head);
		this->Head = temp;
		if (this->Tail == nullptr)
			this->Tail = this->Head;
		size++;
	}
	void PList::addToTail(Party* value)
	{
		// create new item and set as tail of list
		PNode* temp = new PNode(value);
		temp->setNext(nullptr);

		// handle empty list
		if (this->Head == nullptr)
			this->Head = this->Tail = temp;
		else
		{
			this->Tail->setNext(temp);
			this->Tail = temp;
		}
		size++;

	}
	bool PList::delHead()
	{
		// remove head item from list
		PNode* temp = this->Head;
		this->Head = this->Head->getNext();

		// handle empty list
		if (this->Head == temp)
			this->Tail = nullptr;
		size--;
		delete temp;
		return true;
	}
	bool PList::delTail()
	{
		// remove tail item from list
		PNode* temp = this->Tail;
		this->Tail->setNext(nullptr);

		// handle empty list
		if (this->Head == temp)
			this->Head = nullptr;
		size--;
		delete temp;
		return true;
	}

	ostream& operator<<(ostream& os, const PList& lst)
	{
		PNode* curr = lst.getHead();
		while (curr != nullptr)
		{
			os << curr->getInfo();
			curr = curr->getNext();
		}
		return os;
	}

	bool PList::save(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&this->size), sizeof(int)); //write the size
		PNode* curr = Head;
		while (curr != nullptr)
		{
			if(!curr->save(outfile))
				return false;
			curr = curr->getNext();
		}
		return true;
	}
	bool PList::serialSave(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&this->size), sizeof(int)); //write the size
		PNode* curr = Head;
		while (curr != nullptr)
		{
			if(!curr->serialSave(outfile))
				return false;
			curr = curr->getNext();
		}
		return true;
	}
	bool PList::pSerialSave(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&this->size), sizeof(int)); //write the size
		PNode* curr = Head;
		while (curr != nullptr)
		{
			if(!curr->pSerialSave(outfile))
				return false;
			curr = curr->getNext();
		}
		return true;
	}

}