#pragma once
class DVKE{
private:
	// vorg�nger
	DVKE *v;
	// nachvolger
	DVKE *n;
public:
	// Initialisierungskonstruktor
	DVKE(DVKE*, DVKE*);
	// Konstruktor, ruft Initialisierungskonstruktor mit nullpointern auf
	DVKE();

	// Getter und Setter
	DVKE* getV() const;
	void setV(DVKE*);
	DVKE* getN() const;
	void setN(DVKE*);

	// Destruktor
	~DVKE();
};