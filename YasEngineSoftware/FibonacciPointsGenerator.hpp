#ifndef FIBONACCIPOINTSGENERATOR_HPP
#define FIBONACCIPOINTSGENERATOR_HPP
#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include"Math.hpp"
#include"Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

class FibonacciPointsGenerator : public PointsGenerator
{
	public:
        static std::vector<float> numbers;
		virtual PointsSet* generatePoints() override;

};

#endif