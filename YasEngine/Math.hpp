#ifndef MATH_HPP
#define MATH_HPP
#include <map>
#include<vector>

#include "Vector2D.hpp"

std::map<float, float>* generateSinNumbers(int pointsNumber);
std::map<float, float>* generateCosNumbers(int pointsNumber);
std::vector<int> generatePrimeNumbersLessThanN(int n);
std::vector<int> generateNfibonaccinumbers(int n);
double distanceBetweenPoints(const Vector2D<int>& vector0, const Vector2D<int>& vector1);

#endif
