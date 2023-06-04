#ifndef COSINUSPOINTSGENERATOR_HPP
#define COSINUSPOINTSGENERATOR_HPP
#include"PointsGenerator.hpp"
#include "YasGraphicsLibrary.hpp"

class CosinusPointsGenerator : public PointsGenerator
{
	public:
        static std::vector<double> numbers; // FOR GAMEPLAY PURPOSE!!
		virtual PointsSet* generatePoints() override;

};

#endif