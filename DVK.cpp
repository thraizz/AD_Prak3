#include "DVK.h"

DVK::DVK(){}

DVK::DVK(GEOKO *geo){
	this->data = geo;
}

DVK::DVK( int MAX, string path ){


	this->ANZ = new int(0);
	this->MAX = &MAX;

	this->current = this;

	string line;
	GEOKO* temp;
	double xb,xl;
	double br_ges=0, la_ges=0;

	current->Index = (GEOKO *)malloc(*this->MAX*sizeof(GEOKO));
	current->Index = new GEOKO[*this->MAX]; 
		
	ifstream file(path);

	double br, la, brSec, laSec;

	int brGr, brMin, laGr, laMin;


	while (*current->ANZ<*current->MAX){

		getline(file, line, ',');
		line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
		br = stod(line);

		getline(file, line, ';');	
		line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());			
		la = stod(line);

		brGr = (int)(br/3600);
		laGr = (int)(la/3600);

		xb = (br/3600 - brGr) * 60;
		xl = (la/3600 - laGr) * 60;

		brMin = (int)xb;
		laMin = (int)xl;
		
		brSec = (double)((xb - brMin) * 60);
		laSec = (double)((xl  - laMin) * 60);

		temp = new GEOKO(brGr, laGr, brMin, laMin, brSec, laSec,br,la);
		
		br_ges += br;
		la_ges += la;

		
		if (*current->ANZ == 0){
			current->data = temp;
			current->Index[*current->ANZ] = *temp;
			*current->ANZ += 1;

		} else {

	
		
		
		current->Index[*current->ANZ] = *temp;
		current->anhaenge(temp);



		

		}
	
cout << "end " << endl;
cout << "ANZ: " << *current->ANZ << " MAX: " << *current->MAX << endl;
		

	}

/*
	br_ges /= *this->MAX;
	la_ges /= *this->MAX;
	brGr = (int)(br_ges / 3600);
	laGr = (int)(la_ges / 3600);
	xb = (br_ges / 3600 - brGr) * 60;
	xl = (la_ges / 3600 - laGr) * 60;
	brMin = (int)xb;
	laMin = (int)xl;

	brSec = (double)((xb - brMin) * 60);
	laSec = (double)((xl - laMin) * 60);

	this->Mittelwert = new GEOKO(brGr, laGr, brMin, laMin, brSec, laSec, br, la);

	file.close();
*/

}



DVK::~DVK()
{
}


int DVK::getAnz()
{
	return *this->MAX;
}

void DVK::anhaenge(GEOKO* geo){


	if (current->ANZ == current->MAX)
		return;

	current->N = new DVK(geo);
	
	current->N->V = current;
	
	current = current->N;
	
	current->ANZ = current->V->ANZ;

	current->MAX = current->V->MAX;

	*current->ANZ += 1;


}

GEOKO* DVK::getMiddle()
{
	return Mittelwert;
}

GEOKO** DVK::indexCopy()
{
	GEOKO** index_neu = new GEOKO*[*this->MAX];

	for (int i = 0; i < *this->MAX; i++) {
		*index_neu[i] = Index[i];
	}
	return index_neu;
}

void DVK::heapSort(GEOKO *arr[]){
	int anz = *this->MAX - 1;
	build_maxheap(arr, anz);
	for(int i = anz; i > 0; i--){
		swap(i, 0, arr);
		heapify_max(arr, 0, i - 1);
	}
}


void DVK::heapify_max(GEOKO *arr[], int nodeP, int anz){

	if(anz <= 0) return;
	int child = 2 * nodeP, node = nodeP;

	while(child <= anz){
		// 2 Kinder und 2. Kind größer als 1.?
		if(child < anz && (*arr[child + 1] >> *this->Mittelwert) > (*arr[child] >> *this->Mittelwert)){
			// auf 2. setzen
			child++;
		}
		// kind größer als Knoten?
		if(((*arr[node] >> *this->Mittelwert) - (*arr[child] >> *this->Mittelwert)) < 0.0001){
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


double DVK::distance(GEOKO* geoko)
{
	double distance = sqrt(pow(geoko->getBr() -this->Mittelwert->getBr(), 2) + pow(geoko->getLa()-this->Mittelwert->getLa(), 2));
	return distance;
}

void DVK::inDateiSchreiben(string dat,GEOKO* index_neu[])
{
	
	ofstream datei(dat);
	for (int i = 0; i < *this->MAX; i++) {
		// Rausschreiben mit 2 Nachkommastellen
		datei << std::fixed << setprecision(2) << index_neu[i]->getBr() << ": " << index_neu[i]->getLa() << ";" << " Abstand zum Mittelpunkt: " << (*Mittelwert>>*index_neu[i])<< endl;
	}
	datei.close();
}

GEOKO * DVK::getMiddle() const
{
	return this->Mittelwert;
}

void DVK::SelectionSort(GEOKO *arrCpy[]){

	for(int x = 0; x < *this->MAX - 1; x++){
		int kl = x;
		for(int i = x + 1; i < *this->MAX; i++){
			if(((*arrCpy[kl] >> *this->Mittelwert) - (*arrCpy[i] >> *this->Mittelwert)) > 0.0001){
				kl = i;
			}
		}
		swap(x, kl, arrCpy);
	}
}

void DVK::swap(int i, int zeiger, GEOKO *Arr[]) {
	GEOKO *tmp = Arr[i];
	Arr[i] = Arr[zeiger];
	Arr[zeiger] = tmp;
}

void DVK::writeListe(GEOKO * arr[], int anz, const  string name) {
	double br, la;
	ofstream datei(name);
	for (int i = 0; i < anz; i++) {
		br= (((arr[i]->getBrSec() / 60) + arr[i]->getBrMin()) / 60) + arr[i]->getBrGr();
		la= (((arr[i]->getLaSec() / 60) + arr[i]->getLaMin()) / 60) + arr[i]->getLaGr();
		// Rausschreiben mit 2 Nachkommastellen
		datei << std::fixed << setprecision(2) << "   " << br << ",   " << la << ";" << endl;
	}
	datei.close();
}