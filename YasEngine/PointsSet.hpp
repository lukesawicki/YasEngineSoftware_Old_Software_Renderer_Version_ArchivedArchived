#ifndef POINTSSET_HPP
#define POINTSSET_HPP
#include "Vector2D.hpp"

class PointsSet
{
  public:
    PointsSet()
    {
      points = nullptr;
      pointsNumber = 0;
    }
    ~PointsSet()
    {
      delete[] points;
      pointsNumber = 0;
    }
    PointsSet(Vector2D<float>* newPoints, long pointsNumber)
    {
      points = newPoints;
      this->pointsNumber = pointsNumber;
    }
    Vector2D<float>* points =  nullptr;
    long pointsNumber;

  
};

#endif
