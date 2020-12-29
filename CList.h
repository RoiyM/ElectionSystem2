#pragma once
#include"Citizen.h"
#include<fstream>
#include<iostream>
using namespace std;
namespace hw2 {
	class CNode
	{
	private:
		Citizen* info;
		CNode* next;

	public:
		CNode(Citizen* info);
		~CNode();

		//Getters
		CNode* getNext()const;
		Citizen* getInfo()const;

		//Setters
		bool setNext(CNode* next);
		bool setInfo(Citizen* info);

		void save(ofstream& outfile)const;
		void serialSave(ofstream& outfile)const;
		void pSerialSave(ofstream& outfile)const;
	};

	class CList
	{
	private:
		int size;
		CNode* Head;
		CNode* Tail;
	public:
		CList();
		CList(ifstream& infile);

		~CList();

		//Getters
		CNode* getHead()const;
		CNode* getTail()const;
		int getSize()const;

		void addToHead(Citizen* value);
		void addToTail(Citizen* value);
		bool delHead();
		bool delTail();

		bool printXNodesfromList(int x);
		
		friend ostream& operator<<(ostream& os, const CList& lst);

		void save(ofstream& outfile)const;
		void serialSave(ofstream& outfile)const;
		void pSerialSave(ofstream& outfile)const;
	};
}