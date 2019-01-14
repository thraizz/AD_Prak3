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

	// �berladen von >> f�r den Abstand
	double operator>>(const GEOKO&) const;

	// Destruktor
	virtual ~GEOKO();
};

// Rechnet Dezimalkooridinate in Zeitkooridinate um
// @param Breitengrad, L�ngengrad
// @return zeitkooridinate
GEOKO * dezToTime(double, double);
// Rechnet Zeitkooridinate in Dezimalkooridinate um
// @param Zeitkooridinate, variable f�r DezBreitengrad, variable f�r DezL�ngengrad
void timeToDez(const GEOKO *, double *, double *);
