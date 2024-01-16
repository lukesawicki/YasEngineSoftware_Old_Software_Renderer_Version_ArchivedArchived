#ifndef FIBONACCIPOINTSGENERATOR_HPP
#define FIBONACCIPOINTSGENERATOR_HPP
#include <map>

#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include "YasGraphicsLibrary.hpp"

class FibonacciPointsGenerator : public PointsGenerator
{
	public:
		virtual PointsSet* generatePoints(int numberOfNumbers, std::map<int, float>* numbers) override;

};

#endif