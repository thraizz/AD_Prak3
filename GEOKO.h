#pragma once
#include "DVKE.h"
class GEOKO :
	public DVKE{
private:
	// Werte der Kooridinaten in Zeit
	int brGr, laGr, brMin, laMin;
	double brSec, laSec;
public:
	// Initialisierungskonstruktor
	GEOKO(int, int, int, int, double, double, GEOKO*, GEOKO*);
	// Konstruktor, ruft Initialisierungskonstruktor mit nullpointern auf
	GEOKO(int, int, int, int, double, double);

	// Getter
	int getBrGr() const;
	int getLaGr() const;
	int getBrMin() const;
	int getLaMin() const;
	double getBrSec() const;
	double getLaSec() const;

	// Überladen von >> für den Abstand
	double operator>>(const GEOKO&) const;

	// Destruktor
	virtual ~GEOKO();
};

// Rechnet Dezimalkooridinate in Zeitkooridinate um
// @param Breitengrad, Längengrad
// @return zeitkooridinate
GEOKO * dezToTime(double, double);
// Rechnet Zeitkooridinate in Dezimalkooridinate um
// @param Zeitkooridinate, variable für DezBreitengrad, variable für DezLängengrad
void timeToDez(const GEOKO *, double *, double *);
