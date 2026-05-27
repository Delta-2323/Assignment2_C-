#pragma once

#include <ctime>
#include <string>


class Person {
public:
	Person(const std::string& firstName, const std::string& lastName, std::tm birthday);

	const std::string& firstName() const { return _firstName; }
	const std::string& lastName() const { return _lastName; }

protected:
	std::string _firstName;
	std::string _lastName;
	std::tm _birthday;

};

