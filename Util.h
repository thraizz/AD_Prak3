#pragma once

#include "fstream"
#include "GEOKO.h"

using namespace std;

// Liest einen Double-Wert von einem ifstream
// @param zu lesende Datei, endesymbol
double readDoubleFile(ifstream *, char);

// Liest einen Integer-Wert von der Konsole
int readInt();

// Schreibt den gegebenen Array in eine CSV-Datei
// @param zu schreibender Array, anzahl zu schreibender Elemente, Name der Datei
void writeListe(GEOKO *arr[], int anz, const string name);

// Kopiert die angegebene Anzahl an Elementen in einen neuen Array
// @param zu kopierender Array, anzahl zu kopierender Elemente
// @return Kopie des Arrays
GEOKO ** cpyArr(GEOKO *arr[], int anz);

// Tauscht die beiden Elemente im Array
void swap(int target, int source, GEOKO *arr[]);