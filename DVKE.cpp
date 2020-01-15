#include "DVKE.h"

// Initialisierungskonstruktor
DVKE::DVKE(DVKE * v, DVKE * n){
	this->n = n;
	this->v = v;
}

// Konstruktor, ruft Initialisierungskonstruktor mit nullpointern auf
DVKE::DVKE() :DVKE(nullptr, nullptr){
}


// Getter und Setter
DVKE * DVKE::getV() const{
	return this->v;
}

void DVKE::setV(DVKE *v){
	this->v = v;
}

DVKE * DVKE::getN() const{
	return this->n;
}

void DVKE::setN(DVKE *n){
	this->n = n;
}


// Destruktor
DVKE::~DVKE(){
}
