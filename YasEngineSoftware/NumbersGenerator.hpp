#ifndef NUMBERSGENERATOR_HPP
#define NUMBERSGENERATOR_HPP
#include "Vector2D.hpp"

class NumbersGenerator
{
public:

	NumbersGenerator()
	{
		numbersNumber = 0;
	}

	int numbersNumber;
	float* generateNumbers() = 0;

};

#endif
