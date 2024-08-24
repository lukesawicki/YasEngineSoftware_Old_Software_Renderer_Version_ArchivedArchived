#ifndef MATH_HPP
#define MATH_HPP
#include <map>
#include <vector>

#include "vector_2d.hpp"

std::map<float, float>* GenerateSineNumbers(int points_number);
std::map<float, float>* GenerateCosineNumbers(int points_number);
std::vector<int> GeneratePrimeNumbersLessThanN(int n);
std::vector<int> GenerateNfibonacciNumbers(int n);
double DistanceBetweenPoints(const Vector2D<int>& vector_0,
                             const Vector2D<int>& vector_1);

#endif
