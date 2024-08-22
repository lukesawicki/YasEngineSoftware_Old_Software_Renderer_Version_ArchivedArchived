#ifndef COSINUSPOINTSGENERATOR_HPP
#define COSINUSPOINTSGENERATOR_HPP
#include<map>

#include"PointsGenerator.hpp"

class CosinePointsGenerator : public PointsGenerator {
  public:
    ~CosinePointsGenerator();
    PointsSet* generatePoints(int numberOfNumbers, std::map<int, float>* numbers) override;
    PointsSet* generateFloatPoints(int numberOfNumbers, std::map<float, float>* numbers) override;

};

#endif
