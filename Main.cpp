#include "iostream"
#include "DVK.h"
#include "string"
#include "Util.h"
#include "windows.h"

using namespace std;


void beginMessung(LONGLONG *g_LastCount, LONGLONG *g_FirstCount, LONGLONG *g_Frequency, double *nulltime){

	//----------------------------------------------------------------------
	//
	//    Zeitmessung im æs-Bereich
	//    TESTANWENDUNG
	//    Author: tbird
	//    Date: 20.11.2007
	//
	//----------------------------------------------------------------------

	// Variablen
	LONGLONG g_FirstNullCount, g_LastNullCount;

	// Frequenz holen
	if(!QueryPerformanceFrequency((LARGE_INTEGER*) g_Frequency))
		printf("Performance Counter nicht vorhanden");

	double resolution = 1000000 / ((double) *g_Frequency);

	printf("Frequenz des Counters:  %lld kHz\n", *g_Frequency / 1000);  //lld -> LONGLONG darstellung
	printf("Dadurch maximale Aufloesung: %4.5f us\n", resolution);

	// null-messung
	QueryPerformanceCounter((LARGE_INTEGER*) &g_FirstNullCount);
	QueryPerformanceCounter((LARGE_INTEGER*) &g_LastNullCount);
	*nulltime = (((double) (g_LastNullCount - g_FirstNullCount)) / ((double) *g_Frequency));

	printf("Null-Zeit: %4.5f us\n", *nulltime * 1000000);

	// beginn messung
	QueryPerformanceCounter((LARGE_INTEGER*) g_FirstCount);
}

void endeMessung(LONGLONG g_LastCount, LONGLONG g_FirstCount, LONGLONG g_Frequency, double nulltime){

	// 2. Messung
	QueryPerformanceCounter((LARGE_INTEGER*) &g_LastCount);

	double dTimeDiff = (((double) (g_LastCount - g_FirstCount)) / ((double) g_Frequency));

	// Von der gemessenen Zeit die "Null-Zeit" abziehen, um genauer zu werden
	double time = (dTimeDiff - nulltime) * 1000000; //mikro-sekunden
	printf("Zeit: %4.5f us\n", time);
}

void schreiben(GEOKO *arrCpy[], int anz, string nameDat){
// Schreiben in Datei
	if(nameDat == datei1){
		writeListe(arrCpy, anz, "Daten_S.csv");
	}
	if(nameDat == datei2){
		writeListe(arrCpy, anz, "Daten1_S.csv");
	}
}

int main(){
	int choise = 0;
	DVK *liste = nullptr;
	string nameDat;

	do{
		cout << "0 Ende" << endl
			<< "1 Verkettete Liste anlegen" << endl
			<< "2 Bubble Sort" << endl
			<< "3 Insertion Sort" << endl
			<< "4 Quick Sort" << endl
			<< "5 Selection Sort" << endl
			<< "6 Merge Sort" << endl
			<< "7 Heap Sort" << endl;

		choise = readInt();

		switch(choise){
			case 0:
				cout << "Auf wiedersehen" << endl;
				break;

			case 1:
			{
				if(liste != nullptr){
					delete liste;
				}
				int anz;

				do{
					cout << "1 Daten.csv" << endl
						<< "2 Daten1.csv" << endl;

					choise = readInt();
				} while(!(choise == 1 || choise == 2));

				switch(choise){
					case 1:
						nameDat = datei1;
						break;
					case 2:
						nameDat = datei2;
						break;
				}

				cout << "Anzahl der Kooridinatenpaare ? (max " << MAXELE << "):" << endl;
				do{
					anz = readInt();
				} while(anz > MAXELE || anz < 1);

				liste = new DVK(anz, nameDat);

				double br, la;

				timeToDez(liste->getMiddle(), &br, &la);
				cout << "Breitengrad: " << br << ", Laengengrad: " << la << endl;
			}
			break;

			case 2:
			{
				LONGLONG g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
				double nulltime;

				GEOKO **arrCpy = cpyArr(liste->getIndex(), liste->getAnz());

				beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);

				// ###############
				// # Bubble Sort #
				// ###############
				liste->bubbleSort(arrCpy);

				endeMessung(g_LastCount, g_FirstCount, g_Frequency, nulltime);

				// Schreiben in Datei
				schreiben(arrCpy, liste->getAnz(), nameDat);
			}
			break;

			case 3:
			{
				LONGLONG g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
				double nulltime;

				GEOKO **arrCpy = cpyArr(liste->getIndex(), liste->getAnz());

				beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);

				// ##################
				// # Insertion Sort #
				// ##################
				liste->insertionSort(arrCpy);

				endeMessung(g_LastCount, g_FirstCount, g_Frequency, nulltime);

				// Schreiben in Datei
				schreiben(arrCpy, liste->getAnz(), nameDat);
			}
			break;

			case 4:
			{
				LONGLONG g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
				double nulltime;

				GEOKO **arrCpy = cpyArr(liste->getIndex(), liste->getAnz());

				beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);

				// ##############
				// # Quick Sort #
				// ##############
				liste->quicksort(0, liste->getAnz() - 1, arrCpy);

				endeMessung(g_LastCount, g_FirstCount, g_Frequency, nulltime);

				// Schreiben in Datei
				schreiben(arrCpy, liste->getAnz(), nameDat);

			}
			break;

			case 5:
			{
				LONGLONG g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
				double nulltime;
				GEOKO **arrCpy = cpyArr(liste->getIndex(), liste->getAnz());

				beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);

				// ##################
				// # Selection Sort #
				// ##################
				liste->selectionSort(arrCpy);

				endeMessung(g_LastCount, g_FirstCount, g_Frequency, nulltime);

				// Schreiben in Datei
				schreiben(arrCpy, liste->getAnz(), nameDat);
			}
			break;

			case 6:
			{
				LONGLONG g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
				double nulltime;

				GEOKO **arrCpy = cpyArr(liste->getIndex(), liste->getAnz());

				beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);

				// ##############
				// # Merge Sort #
				// ##############
				liste->mergeSort(0, liste->getAnz() - 1, arrCpy);

				endeMessung(g_LastCount, g_FirstCount, g_Frequency, nulltime);

				// Schreiben in Datei
				schreiben(arrCpy, liste->getAnz(), nameDat);
			}
			break;

			case 7:
			{
				LONGLONG g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
				double nulltime;

				GEOKO **arrCpy = cpyArr(liste->getIndex(), liste->getAnz());

				beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);

				// #############
				// # Heap Sort #
				// #############
				liste->heapSort(arrCpy);

				endeMessung(g_LastCount, g_FirstCount, g_Frequency, nulltime);

				// Schreiben in Datei
				schreiben(arrCpy, liste->getAnz(), nameDat);
			}
			break;
			default:
				cout << "ungueltige eingabe!" << endl;
				break;
		}
	} while(choise != 0);

	if(liste != nullptr){
		delete liste;
	}
}