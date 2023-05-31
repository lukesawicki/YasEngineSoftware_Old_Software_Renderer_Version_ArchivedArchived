#ifndef PRIMENUMBERSPOINTSGENERATOR_HPP
#define PRIMENUMBERSPOINTSGENERATOR_HPP
#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include"Math.hpp"
#include"Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

class PrimeNumbersPointsGenerator : public PointsGenerator
{
public:
	virtual PointsSet* generatePoints() override;
    static std::vector<float> numbers;
};

#endif