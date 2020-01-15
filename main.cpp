#pragma once
#include "iostream"
#include "DVK.h"
#include "string"
#include "Util.h"
#include "time.h"

using namespace std;


void beginMessung(long long *g_LastCount, long long *g_FirstCount, long long *g_Frequency, double *nulltime){
	// Variablen
	long long g_FirstNullCount, g_LastNullCount;

	// Frequenz holen
	if(!QueryPerformanceFrequency((long int*) g_Frequency))
		printf("Performance Counter nicht vorhanden");

	double resolution = 1000000 / ((double) *g_Frequency);

	printf("Frequenz des Counters:  %lld kHz\n", *g_Frequency / 1000);  //lld -> long long darstellung
	printf("Dadurch maximale Aufloesung: %4.5f us\n", resolution);

	// null-messung
	QueryPerformanceCounter((long int*) &g_FirstNullCount);
	QueryPerformanceCounter((long int*) &g_LastNullCount);
	*nulltime = (((double) (g_LastNullCount - g_FirstNullCount)) / ((double) *g_Frequency));

	printf("Null-Zeit: %4.5f us\n", *nulltime * 1000000);

	// beginn messung
	QueryPerformanceCounter((long int*) g_FirstCount);
}

void endeMessung(long long g_LastCount, long long g_FirstCount, long long g_Frequency, double nulltime){

	// 2. Messung
	QueryPerformanceCounter((long int*) &g_LastCount);

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
		cout << "1 Verkettete Liste anlegen" << endl
			<< "2 Heap Sort" << endl
			<< "3 Selection Sort" << endl
			<< "4 Daten der Liste schreiben" << endl
			<< "5 Ende" << endl;

		choise = readInt();

		switch(choise){
			case 5:
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



			case 3:
			{
				long long g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
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

			case 2:
			{
				long long g_Frequency = 0, g_FirstCount = 0, g_LastCount = 0;
				double nulltime;

				GEOKO **arrCpy = cpyArr(liste->getIndex(), liste->getAnz());

				beginMessung(&g_LastCount, &g_FirstCount, &g_Frequency, &nulltime);
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
	} while(choise != 5);

	if(liste != nullptr){
		delete liste;
	}
}