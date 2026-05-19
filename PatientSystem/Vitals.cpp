#include "Vitals.h"

#include <iostream>


std::ostream& operator<<(std::ostream& os, const Vitals& p)
{
	os << p.BT() << "," << p.BP() << "," << p.HR() << "," << p.RR();
	return os;
}
