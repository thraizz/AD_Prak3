#include "Util.h"
#include "string"
#include "iostream"
#include "algorithm"
#include "iomanip"

// Liest einen Double-Wert von einem ifstream
// @param zu lesende Datei, endesymbol
double readDoubleFile(ifstream *ifs, char det){
	string tmp;

	getline(*ifs, tmp, det);
	// Löschen der leerzeichen
	tmp.erase(remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());

	return stod(tmp);
}

// Liest einen Integer-Wert von der Konsole
int readInt(){
	string tmp;
	int bed = 1;
	int ret = NULL;

	do{
		cin >> tmp;
		try{
			ret = stoi(tmp);
			bed = 0;
		} catch(const invalid_argument& e){
			cout << "Kein gueltiger Integer-Wert" << endl;
		}
	} while(bed);

	return ret;
}

// Schreibt den gegebenen Array in eine CSV-Datei
// @param zu schreibender Array, anzahl zu schreibender Elemente, Name der Datei
void writeListe(GEOKO * arr[], int anz, const  string name){
	double br, la;
	ofstream datei(name);
	for(int i = 0; i < anz; i++){
		timeToDez(arr[i], &br, &la);
		// Rausschreiben mit 2 Nachkommastellen
		datei << std::fixed << setprecision(2) << "   " << br << ",   " << la << ";" << endl;
	}
	datei.close();
}

// Kopiert die angegebene Anzahl an Elementen in einen neuen Array
// @param zu kopierender Array, anzahl zu kopierender Elemente
// @return Kopie des Arrays
GEOKO ** cpyArr(GEOKO * arr[], int anz){

	GEOKO **arrCpy = new GEOKO*[anz];

	for(int i = 0; i < anz; i++){
		arrCpy[i] = arr[i];
	}

	return arrCpy;
}

// Tauscht die beiden Elemente im Array
void swap(int target, int source, GEOKO *arr[]){
	GEOKO *tmp = arr[target];
	arr[target] = arr[source];
	arr[source] = tmp;
}
