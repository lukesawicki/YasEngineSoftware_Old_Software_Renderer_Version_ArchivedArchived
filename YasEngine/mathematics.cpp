#include "mathematics.hpp"

#include <cmath>
#include <map>

#include "vector_2d.hpp"
#include "yas_graphics_library.hpp"

std::vector<int> GeneratePrimeNumbersLessThanN(int n) {
  std::vector<int> prime_numbers;
  std::map<int, bool> numbers;

  for (int i = 2; i <= n; i++) {
    numbers.insert(std::pair<int, bool>(i, true));
  }

  int j = 0;

  for (int i = 2; i < sqrt(n); i++) {
    if (numbers.at(i)) {
      j = i * i;
      while (j <= n) {
        numbers.at(j) = false;
        j = j + i;
      }
    }
  }

  for (unsigned int i = 2; i < numbers.size(); i++) {
    if (numbers.at(i)) {
      prime_numbers.push_back(i);
    }
  }
  return prime_numbers;
}

std::map<float, float>* GenerateSineNumbers(int points_number) {
  float divider = static_cast<float>(points_number);
  float maximum_x_value = 2.0F * kPi;
  float step = (maximum_x_value / divider);

  std::map<float, float>* sine_map = new std::map<float, float>();

  for (int i = 0; i < points_number; i++) {
    float x = i * step;
    float y = sin(x);
    sine_map->insert(std::pair<float, float>(x, y));
  }
  return sine_map;
}

std::map<float, float>* GenerateCosineNumbers(int points_number) {
  float divider = static_cast<float>(points_number);
  float maximum_x_value = 2.0F * kPi;
  float step = (maximum_x_value / divider);
  std::map<float, float>* cosine_map = new std::map<float, float>();
  for (int i = 0; i < points_number; i++) {
    float x = i * step;
    float y = cos(x);
    cosine_map->insert(std::pair<float, float>(x, y));
  }
  return cosine_map;
}

std::vector<int> GenerateNfibonacciNumbers(int n) {
  std::vector<int> fibonacci_numbers;
  fibonacci_numbers.push_back(1);
  fibonacci_numbers.push_back(1);
  fibonacci_numbers.push_back(2);
  for (int i = 3; i < n; i++) {
    int newFib = fibonacci_numbers.at(i - 1) + fibonacci_numbers.at(i - 2);
    fibonacci_numbers.push_back(newFib);
  }
  return fibonacci_numbers;
}

double DistanceBetweenPoints(const Vector2D<int>& vector_0,
                             const Vector2D<int>& vector_1) {
  return sqrt(pow((vector_0.x_ - vector_1.x_), 2) +
              pow((vector_0.y_ - vector_1.y_), 2));
}
