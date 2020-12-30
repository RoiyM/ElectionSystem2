#include "CandidPerDistrictList.h"
namespace hw2 {
	//Node
	CPDNode::CPDNode(int districId) :districId(districId), next(nullptr)
	{
		this->listOfCandidates = new CList();
	}

	CPDNode::~CPDNode()
	{
		delete this->listOfCandidates;
	}

	//Getters
	CPDNode* CPDNode::getNext()const
	{
		return this->next;
	}

	CList* CPDNode::getListOfCandidates()const
	{
		return this->listOfCandidates;
	}

	int CPDNode::getDistricId()const
	{
		return this->districId;
	}

	//Setters

	bool CPDNode::setNext(CPDNode* next)
	{
		this->next = next;
		return true;
	}
	bool CPDNode::setDistricId(int districId)
	{
		this->districId = districId;
		return true;
	}

	bool CPDNode::setListOfCandidates(CList* listOfCandidates)
	{
		this->listOfCandidates = listOfCandidates;
		return true;
	}

	bool CPDNode::serialSave(ofstream& outfile)const
	{
		//outfile.write(reinterpret_cast<const char*>(&districId), sizeof(int));
		return listOfCandidates->serialSave(outfile);
	}

	//List
	CandidPerDistrictList::CandidPerDistrictList(int amountOfDistricts) :size(0), Head(nullptr), Tail(nullptr)
	{
		for (int i = 0; i < amountOfDistricts; i++)
		{
			this->addToTail(i);
		}
	}

	CandidPerDistrictList::CandidPerDistrictList(const CandidPerDistrictList& other)
	{
		(*this) = other;
	}


	CandidPerDistrictList::~CandidPerDistrictList()
	{
		while (Head != nullptr) {
			CPDNode* temp = Head;
			Head = Head->getNext();
			delete temp;
		}
	}
	//Getters
	CPDNode* CandidPerDistrictList::getHead()const
	{
		return this->Head;
	}
	CPDNode* CandidPerDistrictList::getTail()const
	{
		return this->Tail;
	}

	int CandidPerDistrictList::getSize()const
	{
		return this->size;
	}

	void CandidPerDistrictList::addToHead(int districId)
	{
		(this->size)++;
		CPDNode* temp = new CPDNode(districId);
		temp->setNext(this->Head);
		this->Head = temp;
		if (this->Tail == nullptr)
			this->Tail = this->Head;
	}
	void CandidPerDistrictList::addToTail(int districId)
	{
		// create new item and set as tail of list
		(this->size)++;
		CPDNode* temp = new CPDNode(districId);
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


	bool CandidPerDistrictList::delHead()
	{
		// remove head item from list
		CPDNode* temp = this->Head;
		this->Head = this->Head->getNext();

		// handle empty list
		if (this->Head == temp)
			this->Tail = nullptr;
		(this->size)--;

		delete temp;
		return true;
	}
	bool CandidPerDistrictList::delTail()
	{
		// remove tail item from list
		CPDNode* temp = this->Tail;
		this->Tail->setNext(nullptr);
		(this->size)--;

		// handle empty list
		if (this->Head == temp)
			this->Head = nullptr;

		delete temp;
		return true;
	}

	ostream& operator<<(ostream& os, const CandidPerDistrictList& CPD)
	{
		CPDNode* curr = CPD.getHead();
		CNode* currC;
		while(curr!=nullptr)
		{
			currC = curr->getListOfCandidates()->getHead();
			os << "District number " << curr->getDistricId() << ": ";
			if (currC == nullptr)
			{
				os << "There arent candidates.";
			}
			while (currC != nullptr)
			{
				os << currC->getInfo()->getName() << " ";
				currC = currC->getNext();
			}
			os << endl;
			curr = curr->getNext();
		}
		return os;
	}

	const CandidPerDistrictList& CandidPerDistrictList::operator=(const CandidPerDistrictList& other)
	{
		if (this != &other)
		{
			this->size = other.size;
			CPDNode* curr = other.Head;
			while (curr != nullptr)
			{
				addToTail(curr->getDistricId());
				curr = curr->getNext();
			}
		}
		return *this;
	}
	bool CandidPerDistrictList::serialSave(ofstream& outfile)const
	{
		//outfile.write(reinterpret_cast<const char*>(this->size), sizeof(int)); //write the size
		CPDNode* curr = Head;
		while (curr != nullptr)
		{
			if(!curr->serialSave(outfile))
				return false;
			curr = curr->getNext();
		}
		return true;
	}

}