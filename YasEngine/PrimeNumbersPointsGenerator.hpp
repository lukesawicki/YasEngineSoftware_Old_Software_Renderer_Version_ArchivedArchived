#ifndef PRIMENUMBERSPOINTSGENERATOR_HPP
#define PRIMENUMBERSPOINTSGENERATOR_HPP
#include <map>

#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include"Math.hpp"
#include"Vector2D.hpp"

class PrimeNumbersPointsGenerator : public PointsGenerator
{
public:
	static std::vector<int> numbers;
	virtual PointsSet* generatePoints(int numberOfNumbers, std::map<int, float>* numbers) override;
	virtual PointsSet* generateFloatPoints(int numberOfNumbers, std::map<float, float>* numbers) override;
};

#endif