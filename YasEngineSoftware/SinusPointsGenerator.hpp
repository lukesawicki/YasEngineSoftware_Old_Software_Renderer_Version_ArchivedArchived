#ifndef SINUSPOINTSGENERATOR_HPP
#define SINUSPOINTSGENERATOR_HPP
#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include"Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

class SinusPointsGenerator: public PointsGenerator
{
	public:
        static std::vector<double> numbers; // FOR GAMEPLAY PURPOSE!!
		virtual PointsSet* generatePoints() override;
};

#endif