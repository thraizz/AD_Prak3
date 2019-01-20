
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <math.h>
#include <time.h>

#include "DVK.h"

using namespace std;

long diff(timespec start, timespec end){

    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp.tv_nsec /1000 + temp.tv_sec*1000000;
}

int main() {
	
	int choice;
	int anz;
	int datei=0;
	DVK* dvk=nullptr;

	string file;
	
	do{
		cout << "Menue:" << endl;
		cout << "'1' Verkettete Liste erzeugen." << endl;
		cout << "'2' Quicksort." << endl;
		cout << "'3' Selection Sort." << endl;
		cout << "'4' Programm beenden." << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			if (datei !=0) {
				datei = 0;
			}
			cout << "Geben Sie ein wieviele Objekte erstellt werden sollen (weniger als 1000000)" << endl;
			cin >> anz;
			if (anz > 1000000) {
				cout << "Zu grosse Zahl." << endl;
				break;
			}

				while ((datei!=2)&&(datei!=1))
				{
					cout << "Um Datei zu oeffnen druecken Sie '1' oder fuer Datei1 '2'" << endl;
					cin >> datei;
					switch (datei)
					{
					case 1:
						file = "Daten.csv";
						break;
					case 2:
						file = "Daten1.csv";
						break;
					default:cout << "Ungueltige Eingabe";
						break;
					}
				} 
				dvk = new DVK(anz, file);
				printf("MittelKoordinate betraegt: %i:%i:%f  %i:%i:%f\n ", dvk->getMiddle()->getBrGr(), dvk->getMiddle()->getBrMin(), dvk->getMiddle()->getBrSec(), dvk->getMiddle()->getLaGr(), dvk->getMiddle()->getLaMin(), dvk->getMiddle()->getLaSec());
				cout<< std::fixed << setprecision(2) << dvk->getMiddle()->getBr() << ":"<< dvk->getMiddle()->getLa()<< endl;
				dvk->indexCopy();
				
				break;
		case 2:{ 
			GEOKO** copy = dvk->indexCopy();
			
			timespec start, end;

			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
			dvk->heapSort(copy);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

			long sd = diff(start, end);

			cout << "Dauer der Sortierung: " << sd << "Mikrosekunden" << endl;

			

			switch (datei)
			{
			case 1: dvk->inDateiSchreiben("Daten_S.csv",copy);
				break;
			case 2:
				dvk->inDateiSchreiben("Daten1_S.csv",copy);
				break;
			default:
				break;
			}}
			break;

		case 3:{
			GEOKO** copy = dvk->indexCopy();
			
			timespec start, end;

			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
			dvk->SelectionSort(copy);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

			long sd = diff(start, end);

			cout << "Dauer der Sortierung: " << sd << "Mikrosekunden" << endl;
			

			switch (datei)
			{
				case 1: dvk->inDateiSchreiben("Daten_S.csv", copy);
					break;
				case 2:
					dvk->inDateiSchreiben("Daten1_S.csv", copy);
					break;
				default:
					break;
			}
		}
		break;
		case 4:
			break;
		default:
			cout << "Ungueltige Eingabe";
			break;
		}
	}
	while (choice != 4);

			
	
	
	getchar();
	getchar();

	return 0;
}
