#ifndef SINUSPOINTSGENERATOR_HPP
#define SINUSPOINTSGENERATOR_HPP
#include"PointsGenerator.hpp"
#include"Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

class SinusPointsGenerator: public PointsGenerator
{
	public:
		virtual Vector2D<float>* generatePoints() override;

};

#endif