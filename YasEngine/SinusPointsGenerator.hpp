#ifndef SINUSPOINTSGENERATOR_HPP
#define SINUSPOINTSGENERATOR_HPP
#include <map>

#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include"Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

class SinusPointsGenerator: public PointsGenerator
{
	public:
		virtual PointsSet* generatePoints(int numberOfNumbers, std::map<int, float>* numbers) override;
		virtual PointsSet* generateFloatPoints(int numberOfNumbers, std::map<float, float>* numbers) override;
};

#endif