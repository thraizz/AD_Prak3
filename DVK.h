#pragma once
#include "DVKE.h"
#include "GEOKO.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

class DVK: public DVKE{

private:

	DVK* V, *N;
	GEOKO* Mittelwert;
	GEOKO* Index = NULL;
	int ANZ, MAX;

public:

	DVK(int MAX,string path);
	DVK(GEOKO *geo);
	DVK();
	~DVK();

	int getAnz();
	GEOKO* getMiddle();
	GEOKO** indexCopy();
	DVK *current;

	void heapsort(int links, int rechts, GEOKO* index_neu[]);

	double distance(GEOKO* geoko);

	void anhaenge(GEOKO* geo);

	void inDateiSchreiben(string dat,GEOKO* index_neu[]);

	GEOKO* getMiddle()const;

	void SelectionSort(GEOKO* index_neu[]);

	void swap(int i, int zeiger, GEOKO * Arr[]);
	
	void writeListe(GEOKO * arr[], int anz, const  string name);

	void heapSort(GEOKO *[]);

	void heapify_max(GEOKO *[], int, int);

    void build_maxheap(GEOKO *[], int);
};

