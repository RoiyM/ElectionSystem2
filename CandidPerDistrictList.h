#pragma once
#include"District.h"
#include<iostream>
using namespace std;
namespace hw2 {
	class CList;
	class CPDNode
	{
	private:
		int districId;
		CList* listOfCandidates;
		CPDNode* next;

	public:
		CPDNode(int amountOfDistricts);
		~CPDNode();

		//Getters
		CPDNode* getNext()const;
		int getDistricId()const;
		CList* getListOfCandidates()const;

		//Setters
		bool setNext(CPDNode* next);
		bool setDistricId(int districId);
		bool setListOfCandidates(CList* listOfCandidates);

		bool serialSave(ofstream& outfile)const;

	};
	class CandidPerDistrictList
	{
	private:
		int size;
		CPDNode* Head;
		CPDNode* Tail;

	public:
		CandidPerDistrictList(int amountOfDistricts);
		CandidPerDistrictList(const CandidPerDistrictList& other);

		~CandidPerDistrictList();

		//Getters
		CPDNode* getHead()const;
		CPDNode* getTail()const;
		int getSize()const;

		void addToHead(int districId);
		void addToTail(int districId);
		bool delHead();
		bool delTail();
		friend ostream& operator<<(ostream& os, const CandidPerDistrictList& CPD);
		const CandidPerDistrictList& operator=(const CandidPerDistrictList& other);
		bool serialSave(ofstream& outfile)const;

	};
}