#include "DVKE.h"

DVKE::DVKE() :V(nullptr), N(nullptr)
{
}


DVKE::~DVKE()
{
}

DVKE* DVKE::getN() {
	return N;
}

DVKE* DVKE::getV() {
	return V;
}
void DVKE::setN(DVKE* obj){
	this->N = obj;
}
void DVKE::setV(DVKE* obj) {
	this->V = obj;
}