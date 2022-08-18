#ifndef COSINUSPOINTSGENERATOR_HPP
#define COSINUSPOINTSGENERATOR_HPP
#include"PointsGenerator.hpp"
#include"Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

class CosinusPointsGenerator : public PointsGenerator
{
public:
	virtual Vector2D<float>* generatePoints() override;

};

#endif