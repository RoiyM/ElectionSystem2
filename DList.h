#pragma once
#include"District.h"
#include"UnifiedDistrict.h"
#include"DividedDistrict.h"
#include<iostream>
using namespace std;
namespace hw2 {
	class PList;
	class DNode
	{
	private:
		District* info;
		PList* listOfParties;
		DNode* next;

	public:
		DNode(District* info, PList* listOfParties);
		~DNode();

		//Getters
		DNode* getNext()const;
		District* getInfo()const;
		PList* getListOfParties()const;

		//Setters
		bool setNext(DNode* next);
		bool setInfo(District* info);
		bool setListOfParties(PList* listOfParties);

		void save(ofstream& outfile)const;
		void pSerialSave(ofstream& outfile)const;


	};

	class DList
	{
	private:
		int size;
		DNode* Head;
		DNode* Tail;

	public:
		DList();
		DList(ifstream& infile);
		~DList();

		//Getters
		DNode* getHead()const;
		DNode* getTail()const;
		int getSize()const;

		void printList()const;
		void addToHead(District* value, PList* listOfParties);
		void addToTail(District* value, PList* listOfParties);
		bool delHead();
		bool delTail();

		friend ostream& operator<<(ostream& os, DList& lst);

		void save(ofstream& outfile)const;
		void pSerialSave(ofstream& outfile)const;


	};
}