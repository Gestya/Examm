#include "algorithms/rndtxt.h"
#include <cstdlib>

std::string randomText(int min_length, int max_length, int capital /*= 1*/)
{
    std::string res;
    if (min_length >= 0 || min_length <= max_length)
    {
        int len = (rand() % (max_length - min_length)) + min_length;
        for (int i = 0; i < len; ++i)
        {
            char ch = 'a' + (rand() % ('z' - 'a'));
            if (capital)
            {
                ch -= 'a' - 'A';
                capital = 0;
            }
            res += ch;
        }
    }
    return res;
}
