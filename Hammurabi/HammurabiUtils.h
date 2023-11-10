#pragma once
#include <functional>
#include <iostream>
#include <random>

inline std::random_device randomDevice;
inline std::mt19937 gen(randomDevice());

namespace HammurabiUtils
{
    inline int GetValidInput(std::function<int(int value)> isValid, int tries, const std::string& message)
    {
        int result = 0;
        while (!(std::cin >> result) || !isValid(result))
        {
            if (std::cin.fail())
            {
                std::cin.clear();
			    std::cin.ignore(32767, '\n');
            }
            if (tries > 0 && --tries == 0)
            {
                return -1;
            }
            std::cout << message;
        }
        std::cout << std::endl;
        return result;
    }

    template <typename T>
    T RandBetween(T rangeBegin, T rangeEnd)
    {
        std::uniform_int_distribution<> dist(rangeBegin, rangeEnd);
        return dist(gen);
    }
}