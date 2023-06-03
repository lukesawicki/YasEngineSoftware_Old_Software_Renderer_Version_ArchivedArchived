#ifndef FIBONACCIPOINTSGENERATOR_HPP
#define FIBONACCIPOINTSGENERATOR_HPP
#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include "YasGraphicsLibrary.hpp"

class FibonacciPointsGenerator : public PointsGenerator
{
	public:
        static std::vector<int> numbers;
		virtual PointsSet* generatePoints() override;

};

#endif