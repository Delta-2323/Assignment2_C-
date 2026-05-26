// PatientSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <string>

#include "PatientManagementSystem.h"

int main()
{
	auto pms = std::make_unique<PatientManagementSystem>();

	pms->init();
	pms->run();

	return 0;
}
