#include "GEOKO.h"
#include "cmath"

// Initialisierungskonstruktor
GEOKO::GEOKO(int brGr, int laGr, int brMin, int laMin, double brSec, double laSec, GEOKO *v, GEOKO *n) :DVKE(v, n){
	this->brGr = brGr;
	this->laGr = laGr;
	this->brMin = brMin;
	this->laMin = laMin;
	this->brSec = brSec;
	this->laSec = laSec;
}

// Konstruktor, ruft Initialisierungskonstruktor mit nullpointern auf
GEOKO::GEOKO(int brGr, int laGr, int brMin, int laMin, double brSec, double laSec) : GEOKO(brGr, laGr, brMin, laMin, brSec, laSec, nullptr, nullptr){
}


// Getter
int GEOKO::getBrGr() const{
	return this->brGr;
}

int GEOKO::getLaGr() const{
	return this->laGr;
}

int GEOKO::getBrMin() const{
	return this->brMin;
}

int GEOKO::getLaMin() const{
	return this->laMin;
}

double GEOKO::getBrSec() const{
	return this->brSec;
}

double GEOKO::getLaSec() const{
	return this->laSec;
}


// Überladen von >> für den Abstand
double GEOKO::operator>>(const GEOKO &ko) const{
	double brT, laT, brKo, laKo;

	timeToDez(this, &brT, &laT);
	timeToDez(&ko, &brKo, &laKo);

	return sqrt(pow(brT - brKo, 2) + pow(laT - laKo, 2));
}


// Destruktor
GEOKO:: ~GEOKO(){
}


// Rechnet Dezimalkooridinate in Zeitkooridinate um
// @param Breitengrad, Längengrad
// @return zeitkooridinate
GEOKO * dezToTime(double br, double la){
	int brGr, laGr, brMin, laMin;
	double	brSec, laSec;

	brGr = (int) br;
	laGr = (int) la;

	br = (br - brGr) * 60;
	la = (la - laGr) * 60;

	brMin = (int) br;
	laMin = (int) la;

	brSec = (br - brMin) * 60;
	laSec = (la - laMin) * 60;

	return new GEOKO(brGr, laGr, brMin, laMin, brSec, laSec);
}

// Rechnet Zeitkooridinate in Dezimalkooridinate um
// @param Zeitkooridinate, variable für DezBreitengrad, variable für DezLängengrad
void timeToDez(const GEOKO * ko, double * br, double * la){
	*br = (((ko->getBrSec() / 60) + ko->getBrMin()) / 60) + ko->getBrGr();
	*la = (((ko->getLaSec() / 60) + ko->getLaMin()) / 60) + ko->getLaGr();
}
