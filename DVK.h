#pragma once
#define MAXELE 1000000
#define datei1 "Daten.csv"
#define datei2 "Daten1.csv"

#include "GEOKO.h"
#include "string"

using namespace std;

class DVK{
private:
	// Anker der Liste, Mittelwert aller einträge, Liste mit allen Elementen
	GEOKO * anker_V, *anker_R, *middle, *index[MAXELE];
	// Anzahl der Elemente in der Liste
	int anz;
public:
	// Initialisierungskonstruktor
	DVK(long, string);


	// Getter
	GEOKO * getMiddle() const;

	GEOKO ** getIndex();

	int getAnz() const;


	// Berechnet den Mittelwert neu
	void middleNew();

	// Implementierung des Bubble-Sort-Algorythmus
	void bubbleSort(GEOKO *[]);

	// Implementierung des Insertion-Sort-Algorythmus
	void insertionSort(GEOKO *[]);

	// Implementierung des Quick-Sort-Algorythmus
	void quicksort(int, int, GEOKO *[]);

	// Verschiebt das rechte Element hinter das linke
	void change(int, int, GEOKO *[]);

	// Implementierung des Selection-Sort-Algorythmus
	void selectionSort(GEOKO *[]);

	// Implementierung des Merge-Sort-Algorythmus
	void mergeSort(int, int, GEOKO *[]);

	// Fürht "Beide" Listen zusammen
	void merge(int, int, int, GEOKO *[]);

	void heapSort(GEOKO *[]);

	void heapify_max(GEOKO *[], int, int);

	void build_maxheap(GEOKO *[], int);


	// Destrukort
	~DVK();
};

