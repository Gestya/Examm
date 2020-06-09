#ifndef SELECTINGSORT_H
#define SELECTINGSORT_H

#include <utility>
#include <math.h>

template<class T>
void selecting_sort(T* a, int low, int high, bool(*cmp)(const T&, const T&))
{
    while (low < high)
    {
        T min = a[low];
        int pos = low;

        int i = low + 1;
        while (i <= high)
        {
            if (cmp(a[i], min))
            {
                min = a[i];
                pos = i;
            }
            i++;
        }

        if (low != pos)
            std::swap(a[low], a[pos]);

        low++;
    }
}

#endif // SELECTINGSORT_H
