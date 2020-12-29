#pragma once
#include"Party.h"
#include<iostream>
using namespace std;
namespace hw2 {
	class PNode
	{
	private:
		Party* info;
		int amountOfVotes;
		PNode* next;

	public:
		PNode(Party* info);
		~PNode();

		//Getters
		PNode* getNext()const;
		Party* getInfo()const;
		int getAmountOfVotes()const;

		//Setters
		bool setNext(PNode* next);
		bool setInfo(Party* info);
		bool increaseAmountOfVotesByOne();
		bool setAmountOfVotes(int amount) { this->amountOfVotes = amount; return true; }

		void save(ofstream& outfile)const;
		void serialSave(ofstream& outfile)const;
		void pSerialSave(ofstream& outfile)const;

	};

	class PList
	{
	private:
		int size;
		PNode* Head;
		PNode* Tail;

	public:
		PList();
		PList(PList* other);
		PList(ifstream& infile);
		~PList();

		friend ostream& operator<<(ostream& os, const PList& lst);

		//Getters
		PNode* getHead()const;
		PNode* getTail()const;
		int getSize()const;

		void addToHead(Party* value);
		void addToTail(Party* value);
		bool delHead();
		bool delTail();

		void save(ofstream& outfile)const;
		void serialSave(ofstream& outfile)const;
		void pSerialSave(ofstream& outfile)const;
		
	};
}