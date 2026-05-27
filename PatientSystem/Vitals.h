#pragma once

#include <iostream>


class Vitals
{
public:
	Vitals(float bt, int bp, int hr, int rr) :
		_bodyTemperature(bt),
		_bloodPressure(bp),
		_heartRate(hr),
		_respiratoryRate(rr) 
	{ }

	float BT() const { return _bodyTemperature; }
	int BP() const { return _bloodPressure; }
	int HR() const { return _heartRate; }
	int RR() const { return _respiratoryRate; }

	friend std::ostream& operator<<(std::ostream& os, const Vitals& p);

protected:
	float _bodyTemperature;
	int _bloodPressure;
	int _heartRate;
	int _respiratoryRate;

};

