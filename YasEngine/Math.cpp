#include"Math.hpp"
#include<cmath>
#include<map>

#include "Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

std::vector<int> generatePrimeNumbersLessThanN(int n) {
    std::vector<int> primeNumbers;
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
            primeNumbers.push_back(i);
        }
    }
    return primeNumbers;
}


std::map<float, float>* generateSineNumbers(int pointsNumber) {
    float divider = static_cast<float>(pointsNumber);
    float maximumXvalue = 2.0F * PI;
    float step = (maximumXvalue / divider);

    std::map<float, float>* sineMap = new std::map<float, float>();

    for (int i = 0; i < pointsNumber; i++) {
        float x = i * step;
        float y = sin(x);
        sineMap->insert(std::pair<float, float>(x, y));
    }
    return sineMap;
}

std::map<float, float>* generateCosineNumbers(int pointsNumber) {
    float divider = static_cast<float>(pointsNumber);
    float maximumXvalue = 2.0F * PI;
    float step = (maximumXvalue / divider);
    std::map<float, float>* cosineMap = new std::map<float, float>();
    for (int i = 0; i < pointsNumber; i++) {

        float x = i * step;
        float y = cos(x);
        cosineMap->insert(std::pair<float, float>(x, y));
    }
    return cosineMap;
}

std::vector<int> generateNfibonacciNumbers(int n) {
    std::vector<int> fibbonacciNumbers;
    fibbonacciNumbers.push_back(1);
    fibbonacciNumbers.push_back(1);
    fibbonacciNumbers.push_back(2);
    for (int i = 3; i < n; i++) {
        int newFib = fibbonacciNumbers.at(i - 1) + fibbonacciNumbers.at(i - 2);
        fibbonacciNumbers.push_back(newFib);
    }
    return fibbonacciNumbers;
}

double distanceBetweenPoints(const Vector2D<int>& vector0, const Vector2D<int>& vector1) {
    return sqrt(pow((vector0.x - vector1.x), 2) + pow((vector0.y - vector1.y), 2));
}
