#ifndef SINUSPOINTSGENERATOR_HPP
#define SINUSPOINTSGENERATOR_HPP
#include<map>

#include"PointsGenerator.hpp"
#include"PointsSet.hpp"

class SinePointsGenerator: public PointsGenerator
{
  public:
    ~SinePointsGenerator();
    PointsSet* generatePoints(int numberOfNumbers, std::map<int, float>* numbers) override;
    PointsSet* generateFloatPoints(int numberOfNumbers, std::map<float, float>* numbers) override;
};

#endif