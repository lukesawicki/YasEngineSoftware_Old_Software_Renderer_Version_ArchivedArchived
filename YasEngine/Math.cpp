#include"Math.hpp"
#include<cmath>
#include<map>

#include "Vector2D.hpp"
#include "YasGraphicsLibrary.hpp"

std::vector<int> generatePrimeNumbersLessThanN(int n)
{
    std::vector<int> primeNumbers;
    std::map<int, bool> numbers;

    for (int i = 2; i <= n; i++)
    {
        numbers.insert(std::pair<int, bool>(i, true));
    }

    int j = 0;

    for (int i = 2; i < sqrt(n); i++)
    {
        if (numbers.at(i))
        {
            j = i * i;
            while (j <= n)
            {
                numbers.at(j) = false;
                j = j + i;
            }
        }
    }

    for (unsigned int i = 2; i < numbers.size(); i++)
    {
        if (numbers.at(i))
        {
            primeNumbers.push_back(i);
        }
    }

    return primeNumbers;
}

// std::vector<int> generatePrimeNumbersLessThanN(int n)
// {
//     std::vector<int> primeNumbers;
//     std::map<int, bool> numbers;
//
//     for (int i = 2; i <= n; i++)
//     {
//         numbers.insert(std::pair<int, bool>(i, true));
//     }
//     int k = 0;
//     int j = 0;
//     for (int i = 2; i < sqrt(n); i++)
//     {
//
//         if (numbers.at(i))
//         {
//             while (true)
//             {
//
//                 j = (i * i) + (k * i);
//                 if (j <= n)
//                 {
//                     numbers.at(j) = false;
//                 }
//                 else
//                 {
//                     break;
//                 }
//                 k++;
//             }
//             k = 0;
//             j = 0;
//         }
//     }
//
//     for (unsigned int i = 2; i < numbers.size(); i++)
//     {
//         if (numbers.at(i))
//         {
//             primeNumbers.push_back(i);
//         }
//     }
//
//
//
//     ///////////////////////////////////////////////////////
//     return primeNumbers;
// }

std::vector<int> generateNfibonaccinumbers(int n)
{
    std::vector<int> fibbonacciNumbers;
    fibbonacciNumbers.push_back(1);
    fibbonacciNumbers.push_back(1);
    fibbonacciNumbers.push_back(2);
    for (int i = 3; i < n; i++)
    {
        int newFib = fibbonacciNumbers.at(i - 1) + fibbonacciNumbers.at(i - 2);
        fibbonacciNumbers.push_back(newFib);
    }
    return fibbonacciNumbers;
}

// std::map<float, float>* cosecants(float divider) {
//     std::map<float, float> cosecants* = new std::map<float, float>();
//     float maximumXvalue = 2.0F * PI;
//     float step = (maximumXvalue / divider);
//
//     for (int i = 0; i < divider; i++)
//     {
//         float x = i * step;
//         cosecants->insert({ i * step, cos(x) });
//     }
//     return cosecants;
// }
//
// std::map<float, float>* secants(float divider) {
//     std::map<float, float> secants* = new std::map<float, float>();
//     float maximumXvalue = 2.0F * PI;
//     float step = (maximumXvalue / divider);
//
//     for (int i = 0; i < divider; i++)
//     {
//         float x = i * step;
//         secants->insert({ i * step, sin(x) });
//     }
//     return secants;
// }

// secants
//tangent
// cotangent

double distanceBetweenPoints(const Vector2D<int>& vector0, const Vector2D<int>& vector1)
{
    return sqrt(pow((vector0.x - vector1.x), 2) + pow((vector0.y - vector1.y), 2));
}