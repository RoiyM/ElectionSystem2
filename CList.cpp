#include"CList.h"
namespace hw2 {
	//Node
	CNode::CNode(Citizen* info) :next(nullptr), info(info)
	{
	}

	CNode::~CNode()
	{
	}

	//Getters
	CNode* CNode::getNext()const
	{
		return this->next;
	}


	Citizen* CNode::getInfo()const
	{
		return this->info;
	}
	//Setters
	bool CNode::setNext(CNode* next)
	{
		this->next = next;
		return true;
	}
	bool CNode::setInfo(Citizen* info)
	{
		this->info = info;
		return true;
	}
	void CNode::save(ofstream& outfile)const
	{
		this->info->save(outfile);
	}
	void CNode::serialSave(ofstream& outfile)const
	{
		this->info->serialSave(outfile);
	}
	void CNode::pSerialSave(ofstream& outfile)const
	{
		this->info->pSerialSave(outfile);
	}


	//List
	CList::CList() :Head(nullptr), Tail(nullptr), size(0)
	{
	}

	CList::CList(ifstream& infile)
	{
		infile.read(reinterpret_cast<char*>(&this->size), sizeof(int)); //write the size
		for (int i = 0; i < this->size; i++)
		{
			Citizen* temp = new Citizen(infile);
			this->addToTail(temp);
		}
	}


	CList::~CList()
	{
		while (Head != nullptr) {
			CNode* temp = Head;
			Head = Head->getNext();
			delete temp;
		}
	}
	//Getters
	CNode* CList::getHead()const
	{
		return this->Head;
	}
	CNode* CList::getTail()const
	{
		return this->Tail;
	}

	int CList::getSize()const {
		return this->size;
	}


	void CList::addToHead(Citizen* value)
	{
		CNode* temp = new CNode(value);
		temp->setNext(this->Head);
		this->Head = temp;
		if (this->Tail == nullptr)
			this->Tail = this->Head;
		(this->size)++;
	}
	void CList::addToTail(Citizen* value)
	{
		(this->size)++;
		// create new item and set as tail of list
		CNode* temp = new CNode(value);
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
	bool CList::delHead()
	{
		// remove head item from list
		CNode* temp = this->Head;
		this->Head = this->Head->getNext();

		// handle empty list
		if (this->Head == temp)
			this->Tail = nullptr;
		(this->size)--;

		delete temp;
		return true;
	}
	bool CList::delTail()
	{
		// remove tail item from list
		CNode* temp = this->Tail;
		this->Tail->setNext(nullptr);

		// handle empty list
		if (this->Head == temp)
			this->Head = nullptr;

		(this->size)--;

		delete temp;
		return true;
	}

	ostream& operator<<(ostream& os, const CList& lst)
	{
		CNode* curr = lst.getHead();
		while (curr != nullptr)
		{
			os << curr->getInfo();
			curr = curr->getNext();
		}
		return os;
	}

	bool CList::printXNodesfromList(int x)
	{
		int i = 0;
		CNode* curr = this->getHead();
		while (i < x && curr != nullptr)
		{
			cout << curr->getInfo()->getName() << " ";
			i++;
			curr = curr->getNext();
		}
		if (i == x)
			return true;
		return false;
	}

	void CList::save(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&this->size), sizeof(int)); //write the size
		CNode* curr = Head;
		while (curr!=nullptr)
		{
			curr->save(outfile);
			curr = curr->getNext();
		}

	}
	void CList::serialSave(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&this->size), sizeof(int)); //write the size
		CNode* curr = Head;
		while (curr != nullptr)
		{
			curr->serialSave(outfile);
			curr = curr->getNext();
		}
	}
	void CList::pSerialSave(ofstream& outfile)const
	{
		outfile.write(reinterpret_cast<const char*>(&this->size), sizeof(int)); //write the size
		CNode* curr = Head;
		while (curr != nullptr)
		{
			curr->pSerialSave(outfile);
			curr = curr->getNext();
		}
	}
}