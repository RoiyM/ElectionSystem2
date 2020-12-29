#include"Election.h"
#include"UnifiedDistrict.h"
#include"DividedDistrict.h"
#include"CandidPerDistrictList.h"
#include<iostream>
#include<fstream>
using namespace std;

namespace hw2 {
	Election::Election(Date date)
	{
		this->date = date;
		this->voterBook = new CList();
		this->parties = new PList();
		this->districts = new DList();
		this->amountOfDistricts = 0;
		this->amountOfParties = 0;
		this->amountOfCitizens = 0;
	}
	Election::Election(ifstream& infile)
	{
		infile.read(reinterpret_cast<char*>(&this->date), sizeof(Date)); //read the date
		infile.read(reinterpret_cast<char*>(&this->amountOfCitizens), sizeof(int));
		voterBook = new CList(infile);
		infile.read(reinterpret_cast<char*>(&this->amountOfDistricts), sizeof(int));
		districts = new DList(infile);
		infile.read(reinterpret_cast<char*>(&this->amountOfParties), sizeof(int));
		parties = new PList(infile);
	}
	Election::~Election()
	{
		freeCitizens();
		delete this->voterBook;
		freeDistricts();
		delete this->districts;
		freeParties();
		delete this->parties;
	}

	void Election::freeCitizens()
	{
		CNode* curr = this->voterBook->getHead();
		while (curr != nullptr)
		{
			delete (curr->getInfo());
			curr = curr->getNext();
		}
	}
	void Election::freeParties()
	{
		PNode* curr = this->parties->getHead();
		while (curr != nullptr)
		{
			delete (curr->getInfo());
			curr = curr->getNext();
		}
	}
	void Election::freeDistricts()
	{
		DNode* curr = this->districts->getHead();
		while (curr != nullptr)
		{
			delete (curr->getInfo());
			curr = curr->getNext();
		}
	}

	bool Election::addDistrict(const char* name, int numOfRep, int districtType)
	{
		char* n;
		copyStr(&n, name);
		District* temp = new District(n, numOfRep);
		PList* tempP = new PList(this->parties);
		this->districts->addToTail(temp, tempP);
		PNode* curr = this->parties->getHead();
		while (curr != nullptr)
		{
			curr->getInfo()->getCandidPerDistrictList()->addToTail(amountOfDistricts);
			curr = curr->getNext();
		}
		(this->amountOfDistricts)++;
		return true;
	}

	bool Election::addCitizen(char* name, int id, int YOB, int DId)
	{
		District* district = findDistrictById(DId);
		if (district == nullptr || findCitizenById(id) != nullptr) //district doesnt exist or id is taken
			return false;
		char* allocateName;
		copyStr(&allocateName, name);
		Citizen* temp = new Citizen(allocateName, id, YOB, district);
		this->voterBook->addToTail(temp);
		district->getAllowedVotersList()->addToTail(temp); //add to allowed voters in district
		(this->amountOfCitizens++);
		return true;
	}

	bool Election::addParty(char* name, int candidId)
	{
		Citizen* candid = findCitizenById(candidId);
		if (candid == nullptr)
		{
			return false;
		}
		char* allocateName;
		copyStr(&allocateName, name);
		Party* temp = new Party(allocateName, candid, amountOfDistricts);
		this->parties->addToTail(temp);
		DNode* curr = districts->getHead();
		while (curr != nullptr)//for each district adds the new party
		{
			curr->getListOfParties()->addToTail(temp);
			curr = curr->getNext();
		}
		(this->amountOfParties)++;
		return true;
	}

	bool Election::addCitizenAsPartyCandid(int candidId, int partyId, int DId)
	{
		Citizen* candid = findCitizenById(candidId);
		Party* party = findPartyById(partyId);

		if (candid == nullptr || party == nullptr)
		{
			return false;
		}
		party->addCandidToDistrict(candid, DId);
		return true;
	}

	void Election::display(int x)
	{
		switch (x)
		{
		case 5:
			cout << *(this->districts) << endl;
			break;
		case 6:
			cout << *(this->voterBook) << endl;
			break;
		case 7:
			cout << *(this->parties) << endl;
			break;
		default:
			break;
		}
	}
	void Election::increaseTotalPartyVotes(int partyId)
	{
		findPNodeyById(partyId)->increaseAmountOfVotesByOne();
	}

	void Election::increasePartyVotesInDistrict(int partyId, int districtId)
	{
		PNode* curr = findDNodeById(districtId)->getListOfParties()->getHead();
		int i = 0;
		while (curr != nullptr && i < partyId)
		{
			i++;
			curr = curr->getNext();
		}
		curr->increaseAmountOfVotesByOne();
	}


	bool Election::vote(int id, int partyId)
	{
		Citizen* citizen = findCitizenById(id);
		Party* party = findPartyById(partyId);
		if (citizen == nullptr || party == nullptr || citizen->getVoted())
		{
			return false;
		}
		District* district = findDistrictById(citizen->getDistrictId());
		if (district == nullptr)
		{
			return false;
		}
		district->increaseVoteCountByOne();
		citizen->setVoted();
		increaseTotalPartyVotes(partyId); ///increas total vote of the party
		increasePartyVotesInDistrict(partyId, citizen->getDistrictId());///increase party votes in district 

		return true;
	}

	Party* Election::findMaxVotes(int districtId)
	{
		PNode* curr = this->findDNodeById(districtId)->getListOfParties()->getHead();
		int max = curr->getAmountOfVotes();
		Party* maxParty = (curr->getInfo());
		curr = curr->getNext();
		while (curr != nullptr)
		{
			if (curr->getAmountOfVotes() > max)
			{
				max = curr->getAmountOfVotes();
				maxParty = (curr->getInfo());
			}
			curr = curr->getNext();
		}
		return maxParty;
	}

	void Election::merge(PNode* arr[], int l, int m, int r)
	{
		int n1 = m - l + 1;
		int n2 = r - m;
		// Create temp arrays
		PNode** L = new PNode * [n1];
		PNode** R = new PNode * [n2];
		// Copy data to temp arrays L[] and R[]
		for (int i = 0; i < n1; i++)
			L[i] = arr[l + i];
		for (int j = 0; j < n2; j++)
			R[j] = arr[m + 1 + j];
		// Merge the temp arrays back into arr[l..r]
		// Initial index of first subarray
		int i = 0;
		// Initial index of second subarray
		int j = 0;
		// Initial index of merged subarray
		int k = l;
		while (i < n1 && j < n2) {
			if (L[i]->getInfo()->getAmountOfElectors() >= R[j]->getInfo()->getAmountOfElectors()) {
				arr[k] = L[i];
				i++;
			}
			else {
				arr[k] = R[j];
				j++;
			}
			k++;
		}
		// Copy the remaining elements of
		// L[], if there are any
		while (i < n1) {
			arr[k] = L[i];
			i++;
			k++;
		}
		// Copy the remaining elements of
		// R[], if there are any
		while (j < n2) {
			arr[k] = R[j];
			j++;
			k++;
		}
		delete[] L;
		delete[] R;
	}

	// l is for left index and r is
	// right index of the sub-array
	// of arr to be sorted */
	void Election::mergeSort(PNode* arr[], int l, int r) {
		if (l >= r) {
			return;//returns recursively
		}
		int m = (l + r - 1) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}

	PNode** Election::makeSortedPartiesArray(PList* pLst)
	{
		PNode** arr = new PNode * [amountOfParties];
		PNode* curr = pLst->getHead();
		int i = 0;
		while (curr != nullptr)
		{
			arr[i++] = curr;
			curr = curr->getNext();
		}
		mergeSort(arr, 0, amountOfParties - 1);
		return arr;
	}

	void Election::printParties(PList* lst, District* district)
	{
		PNode* curr = lst->getHead();
		while (curr != nullptr)
		{
			float precentage;
			if (district->getCountVotes() != 0)
			{
				precentage = (static_cast<float>(curr->getAmountOfVotes()) / district->getCountVotes());
			}
			else
				precentage = 0;
			cout << "Party: " << curr->getInfo()->getName() << endl;
			cout << "Amount of votes: " << curr->getAmountOfVotes() << endl;
			cout << "Percentage: " << precentage * 100 << "%" << endl;
			cout << "the candidates are: ";
			CList* candidates = curr->getInfo()->getDistrictCandidates(district->getId());
			if (!district->printAddToElected(candidates, static_cast<int>(district->getAmountOfRep() * precentage)))
				cout << "there isnt enough candidated" << endl;
			DividedDistrict* temp = dynamic_cast<DividedDistrict*>(district);
			if (temp)
			{
				curr->getInfo()->addElectors(static_cast<int>(district->getAmountOfRep() * precentage));
			}
			curr = curr->getNext();
		}
	}


	void Election::displayResult()
	{
		DNode* currD = districts->getHead();
		while (currD != nullptr) {
			cout << endl << "District: " << currD->getInfo() << endl; //prints the District
			int size = currD->getInfo()->getAllowedVotersList()->getSize(); //amount of citizens in district
			int count = currD->getInfo()->getCountVotes(); //amount of citizens who actually vote in district
			currD->getInfo()->setPresentOfVoters(static_cast<float>(count) / size);//update the vote precentage

			// ///// //// sort parties for each district and print the Head and the number of electors

			printParties(currD->getListOfParties(), currD->getInfo()); //print the parties of the district

			cout << "vote prcentage in district: " << (currD->getInfo()->getPresentOfVoters()) * 100 << "%" << endl;
			UnifiedDistrict* temp = dynamic_cast<UnifiedDistrict*>(currD->getInfo());
			if (temp)
			{
				////find the party with the max votes
				///add to the winning party the amount of seats that the district is worth!
				Party* districtWinner = findMaxVotes(currD->getInfo()->getId());
				cout << "Candidate for PM: " << districtWinner->getCandid()->getName() << endl;
				districtWinner->addElectors(currD->getInfo()->getAmountOfRep());
			}
			
			currD = currD->getNext();
		}
		PNode** arr = makeSortedPartiesArray(parties);
		///all the parties will be displayed from the highest electors to the lowest
		///for each party display the head and the total electors, total votes, 

		for (int i = 0; i < amountOfParties; i++)
		{
			cout << "The PM candidate: " << arr[i]->getInfo()->getCandid()->getName() << endl;
			cout << "Amount of electors: " << arr[i]->getInfo()->getAmountOfElectors() << endl;
			cout << "Amount of votes: " << arr[i]->getAmountOfVotes() << endl;
		}
	}

	Citizen* Election::findCitizenById(int id)
	{
		bool hasFound = false;
		CNode* curr = this->voterBook->getHead();
		while (curr != nullptr && !hasFound)
		{
			if (curr->getInfo()->getId() == id)
				hasFound = true;
			else
				curr = curr->getNext();
		}
		if (hasFound)
			return curr->getInfo();
		return nullptr;
	}

	Party* Election::findPartyById(int id)
	{
		bool found = false;
		PNode* curr = this->parties->getHead();
		while (curr != nullptr && !found)
		{
			if (curr->getInfo()->getId() == id)
				found = true;
			else
				curr = curr->getNext();
		}
		if (found)
			return (curr->getInfo());
		return nullptr;
	}

	PNode* Election::findPNodeyById(int id)
	{
		bool found = false;
		PNode* curr = this->parties->getHead();
		while (curr != nullptr && !found)
		{
			if (curr->getInfo()->getId() == id)
				found = true;
			else
				curr = curr->getNext();
		}
		if (found)
			return curr;
		return nullptr;
	}
	District* Election::findDistrictById(int id)
	{
		DNode* curr = this->districts->getHead();
		bool hasFound = false;
		while (curr != nullptr && !hasFound)
		{
			if (curr->getInfo()->getId() == id)
				hasFound = true;
			else
				curr = curr->getNext();
		}
		if (hasFound)
			return (curr->getInfo());
		return nullptr;
	}
	DNode* Election::findDNodeById(int id)
	{
		DNode* curr = this->districts->getHead();
		bool hasFound = false;
		while (curr != nullptr && !hasFound)
		{
			if (curr->getInfo()->getId() == id)
				hasFound = true;
			else
				curr = curr->getNext();
		}
		if (hasFound)
			return curr;
		return nullptr;
	}

	bool Election::saveE(ofstream& outfile) const
	{
		outfile.write(reinterpret_cast<const char*>(&this->date), sizeof(Date)); //write the date
		outfile.write(reinterpret_cast<const char*>(&this->amountOfCitizens), sizeof(int));
		voterBook->save(outfile);
		outfile.write(reinterpret_cast<const char*>(&this->amountOfDistricts), sizeof(int));
		districts->save(outfile);
		outfile.write(reinterpret_cast<const char*>(&this->amountOfParties), sizeof(int));
		parties->save(outfile);

		//outfile.write(reinterpret_cast<const char*>(&this->amountOfCitizens), sizeof(int));
		voterBook->pSerialSave(outfile);
		//outfile.write(reinterpret_cast<const char*>(&this->amountOfDistricts), sizeof(int));
		districts->pSerialSave(outfile);
		//outfile.write(reinterpret_cast<const char*>(&this->amountOfParties), sizeof(int));
		parties->pSerialSave(outfile);
		return true;
	}

	bool Election::save(const char* name) const
	{
		ofstream outfile(name, ios::binary | ios::trunc);
		if (!outfile) {
			cout << "Error" << endl;
			exit(-1);
		}
		int type = 1;
		outfile.write(reinterpret_cast<const char*>(&type), sizeof(int)); //write the type
		saveE(outfile);
		outfile.close();
		return true;
	}
	bool Election::setPC(ifstream& infile)
	{
		int dId;
		CNode* curr = voterBook->getHead();
		infile.read(reinterpret_cast<char*>(&dId), sizeof(int));//reads the size and ignore it
		while (curr != nullptr)
		{
			infile.read(reinterpret_cast<char*>(&dId), sizeof(int));
			curr->getInfo()->setDistrict(findDistrictById(dId));
			curr = curr->getNext();
		}
	}
	bool Election::setPD(ifstream& infile)
	{
		int size, id;
		CList* temp;
		DNode* curr = districts->getHead();
		infile.read(reinterpret_cast<char*>(&size), sizeof(int)); //reads the size and ignore it
		while (curr != nullptr)
		{
			infile.read(reinterpret_cast<char*>(&size), sizeof(int)); //reads the size of allowedVoters CList
			temp = new CList();
			curr->getInfo()->setAllowedVotersList(temp);
			for (int i = 0; i < size; i++)
			{
				infile.read(reinterpret_cast<char*>(&id), sizeof(int)); //reads the id
				temp->addToTail(findCitizenById(id));
			}
			infile.read(reinterpret_cast<char*>(&size), sizeof(int)); //reads the size of elected CList
			temp = new CList();
			curr->getInfo()->setElectedList(temp);
			for (int i = 0; i < size; i++)
			{
				infile.read(reinterpret_cast<char*>(&id), sizeof(int)); //reads the id
				temp->addToTail(findCitizenById(id));
			}
			curr = curr->getNext();
		}
	}
	bool Election::setPP(ifstream& infile)
	{
		int size, id;
		PNode* curr = parties->getHead();
		CandidPerDistrictList* temp;
		infile.read(reinterpret_cast<char*>(&size), sizeof(int));//reads the size and ignore it
		while (curr != nullptr)
		{
			infile.read(reinterpret_cast<char*>(&id), sizeof(int));
			curr->getInfo()->setCandid(findCitizenById(id));
			temp = new CandidPerDistrictList(this->amountOfDistricts);
			curr->getInfo()->setCandidPerDistrict(temp);
			CPDNode* CPDcurr = temp->getHead();
			while (CPDcurr != nullptr)
			{
				infile.read(reinterpret_cast<char*>(&size), sizeof(int));//reads the size of the candid CList
				for (int i = 0; i < size; i++)
				{
					infile.read(reinterpret_cast<char*>(&id), sizeof(int));
					CPDcurr->getListOfCandidates()->addToTail(findCitizenById(id));
				}
				CPDcurr = CPDcurr->getNext();
			}
			curr = curr->getNext();
		}
	}
	bool Election::setP(ifstream& infile)
	{
		setPC(infile);
		setPD(infile);
		setPP(infile);
	}
}