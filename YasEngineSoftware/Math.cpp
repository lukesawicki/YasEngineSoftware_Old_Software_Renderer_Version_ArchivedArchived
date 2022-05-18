#include"Math.hpp"

std::vector<int> generatePrimeNumbersLessThanN(int n)
{
    std::vector<int> primeNumbers;
    std::map<int, bool> numbers;

    for (int i = 2; i <= n; i++)
    {
        numbers.insert(std::pair<int, bool>(i, true));
    }
    int k = 0;
    int j = 0;
    for (int i = 2; i < sqrt(n); i++)
    {

        if (numbers.at(i))
        {
            while (true)//j < n)
            {

                j = (i * i) + (k * i);
                if (j <= n)
                {
                    numbers.at(j) = false;
                }
                else
                {
                    break;
                }
                k++;
            }
            k = 0;
            j = 0;
        }
    }

    for (int i = 2; i < numbers.size(); i++)
    {
        if (numbers.at(i))
        {
            primeNumbers.push_back(i);
        }
    }
    return primeNumbers;
}

//std::vector<int>
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