#ifndef POINTSGENERATOR_HPP
#define POINTSGENERATOR_HPP
#include "PointsSet.hpp"

class PointsGenerator
{
	public:
		int pointsNumber = 0;
		virtual PointsSet* generatePoints(int numberOfNumbers, std::map<int, float>* numbers) = 0;
		
};

#endif
