#ifndef COSINUSPOINTSGENERATOR_HPP
#define COSINUSPOINTSGENERATOR_HPP
#include <map>

#include"PointsGenerator.hpp"
#include "YasGraphicsLibrary.hpp"

class CosinePointsGenerator : public PointsGenerator
{
	public:
		virtual PointsSet* generatePoints(int numberOfNumbers, std::map<int, float>* numbers) override;
		virtual PointsSet* generateFloatPoints(int numberOfNumbers, std::map<float, float>* numbers) override;

};

#endif