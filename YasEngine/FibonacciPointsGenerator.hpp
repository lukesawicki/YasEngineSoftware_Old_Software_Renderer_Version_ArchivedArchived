#ifndef FIBONACCIPOINTSGENERATOR_HPP
#define FIBONACCIPOINTSGENERATOR_HPP
#include<map>

#include"PointsGenerator.hpp"
#include"PointsSet.hpp"

class FibonacciPointsGenerator : public PointsGenerator
{
	public:
		~FibonacciPointsGenerator();
		PointsSet* generatePoints(int numberOfNumbers, std::map<int, float>* numbers) override;
		PointsSet* generateFloatPoints(int numberOfNumbers, std::map<float, float>* numbers) override;

};

#endif