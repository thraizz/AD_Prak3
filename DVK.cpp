#include "DVK.h"
#include "malloc.h"
#include "iostream"
#include "fstream"
#include "Util.h"

// Initialisierungskonstruktor
DVK::DVK(long anzahl, string nameDatei){
	this->anz = anzahl;

	// Aktuelles gelesenes Element
	GEOKO *tmp;
	// Einzulesende Datei
	ifstream datei(nameDatei);

	// Einlesen der Datenpaare
	for(int i = 0; i < anzahl; i++){

		//eingelesener Breiten- und Längengrad
		double br, la;

		br = readDoubleFile(&datei, ',');
		la = readDoubleFile(&datei, ';');

		tmp = dezToTime(br, la);

		// Eintragen in Array
		this->index[i] = tmp;

		// vorderen Anker setzen
		if(i == 0){
			this->anker_V = tmp;
		}
		// Eintrage als Nachvolger im vorgänger und vorgänger eintragen
		if(i > 0 && i < anzahl){
			this->index[i - 1]->setN(tmp);
			tmp->setV(this->index[i - 1]);
		}
		// hinteren Anker setzen
		if(i == anzahl - 1){
			this->anker_R = tmp;
		}
	}
	datei.close();

	// middle neu berechnen
	middleNew();
}


// Getter
GEOKO * DVK::getMiddle() const{
	return this->middle;
}

GEOKO ** DVK::getIndex(){
	return this->index;
}

int DVK::getAnz() const{
	return this->anz;
}


// Berechnet den Mittelwert neu
void DVK::middleNew(){
	// alten Mittelwert löschen, falls vorhanden
	if(this->middle != nullptr){
		delete this->middle;
	}

	// Breiten- und Längengrad durchschnitt, wert des Aktuellen paares
	double brAvg = 0.0, laAvg = 0.0, brTmp, laTmp;

	// Alle werte zusammen rechnen
	for(int i = 0; i < this->anz; i++){
		timeToDez(index[i], &brTmp, &laTmp);
		brAvg += brTmp;
		laAvg += laTmp;
	}

	// Durch anzahl Elemente teilen
	brAvg /= this->anz;
	laAvg /= this->anz;

	// middle neu setzen
	this->middle = dezToTime(brAvg, laAvg);
}

// Implementierung des Bubble-Sort-Algorythmus
void DVK::bubbleSort(GEOKO *arrCpy[]){
	// Anzahl Durchlaeufe
	for(int run = 1; run < this->anz; run++){
		// Durchlaufen
		for(int i = 0; i < this->anz - run; i++){
			// Element groesser als nachfolger ?
			if(((*arrCpy[i] >> *this->middle) - (*arrCpy[i + 1] >> *this->middle)) > 0.0001){
				// Vertauschen
				swap(i, i + 1, arrCpy);
			}
		}
	}
}

// Implementierung des Insertion-Sort-Algorythmus
void DVK::insertionSort(GEOKO *arrCpy[]){
	for(int i = 1; i < this->anz; i++){
		GEOKO *sort = arrCpy[i];
		int j = i;
		// Element kleiner als Vorgänger ?
		while(j > 0 && (((*arrCpy[j - 1] >> *this->middle) - (*arrCpy[j] >> *this->middle)) > 0.0001)){
			arrCpy[j] = arrCpy[j - 1];
			j--;
			arrCpy[j] = sort;
		}

	}
}

// Implementierung des Quick-Sort-Algorythmus
void DVK::quicksort(int links, int rechts, GEOKO *arr[]){
	int pivot = links;
	for(int i = links + 1; i <= rechts; i++){
		if(((*arr[pivot] >> *this->middle) - (*arr[i] >> *this->middle)) > 0.0001){
			change(pivot, i, arr);
			pivot++;
		}
	}
	// Like Liste
	if(links < pivot - 1){
		quicksort(links, pivot - 1, arr);
	}
	// Rechte Liste
	if(rechts > pivot + 1){
		quicksort(pivot + 1, rechts, arr);
	}
}

// Verschiebt das rechte Element hinter das linke
void DVK::change(int links, int rechts, GEOKO *arr[]){
	while(links < rechts){
		swap(rechts, rechts - 1, arr);
		rechts--;
	}
}

// Implementierung des Selection-Sort-Algorythmus
void DVK::selectionSort(GEOKO *arrCpy[]){

	for(int x = 0; x < this->anz - 1; x++){
		int kl = x;
		for(int i = x + 1; i < this->anz; i++){
			if(((*arrCpy[kl] >> *this->middle) - (*arrCpy[i] >> *this->middle)) > 0.0001){
				kl = i;
			}
		}
		swap(x, kl, arrCpy);
	}
}

// Implementierung des Merge-Sort-Algorythmus
void DVK::mergeSort(int left, int right, GEOKO *arr[]){
	int middle = (int) ceil((left + right) / 2.0);

	if((middle - left) > 1)
		mergeSort(left, middle, arr);
	if(right - (middle) > 1)
		mergeSort(middle, right, arr);
	merge(left, middle, right, arr);
}

// Fürht "Beide" Listen zusammen
void DVK::merge(int left, int middle, int right, GEOKO *arr[]){
	int leftNum = middle - left, rightNum = right - middle;

	while(leftNum != 0 && rightNum != 0){
		if((*arr[left] >> *this->middle) - (*arr[middle] >> *this->middle) > 0.0){
			change(left, middle, arr);
			left++;
			middle++;
			rightNum--;
		} else{
			left++;
			leftNum--;
		}
	}
}

// Implementierung des Heap-Sort-Algorythmus
void DVK::heapSort(GEOKO *arr[]){
	int anz = this->anz - 1;
	build_maxheap(arr, anz);
	for(int i = anz; i > 0; i--){
		// Größtes Element raus nehmen, letztes einfügen und einsortieren
		swap(i, 0, arr);
		heapify_max(arr, 0, i - 1);
	}
}

// Einsortieren des Ellements i in seinem Zweig
void DVK::heapify_max(GEOKO *arr[], int nodeP, int anz){
	// gültige Anzahl?
	if(anz <= 0) return;
	int child = 2 * nodeP, node = nodeP;

	while(child <= anz){
		// 2 Kinder und 2. Kind größer als 1.?
		if(child < anz && (*arr[child + 1] >> *this->middle) > (*arr[child] >> *this->middle)){
			// auf 2. setzen
			child++;
		}
		// kind größer als Knoten?
		if(((*arr[node] >> *this->middle) - (*arr[child] >> *this->middle)) < 0.0001){
			swap(node, child, arr);
			node = child;
			child = 2 * child;
		} else break;
	}
}

// Max-Heap aufbauen
void DVK::build_maxheap(GEOKO *arr[], int anz){
	// Für jeden Knoten mit Kinder(n)
	for(int node = anz / 2; node >= 0; node--){
		heapify_max(arr, node, anz);
	}
}


// Destrukort
DVK::~DVK(){
	delete middle;
	delete[] * index;
}
