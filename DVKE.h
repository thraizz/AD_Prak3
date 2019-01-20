#pragma once
class DVKE
{

protected:
	DVKE* V;
	DVKE* N;
	void* data;

public:
	DVKE();
	~DVKE();
	DVKE* getV();
	DVKE* getN();
	void setV(DVKE* obj);
	void setN(DVKE* obj);
};

