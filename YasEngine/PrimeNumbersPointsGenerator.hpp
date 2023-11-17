#ifndef PRIMENUMBERSPOINTSGENERATOR_HPP
#define PRIMENUMBERSPOINTSGENERATOR_HPP
#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include"Math.hpp"
#include"Vector2D.hpp"

class PrimeNumbersPointsGenerator : public PointsGenerator
{
public:
	static std::vector<int> numbers;
	virtual PointsSet* generatePoints() override;
};

#endif