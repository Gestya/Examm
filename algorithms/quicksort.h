#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <utility>

template<class T>
void quick_sort(T* a, int low, int high, bool(*cmp)(const T&, const T&))
{
    if (low >= high)
        return;

    T pivot = a[(low + high) / 2 ];

    int i = low;
    int j = high;

    while (true)
    {
        while ( cmp(a[i], pivot))
            i++;

        while ( cmp(pivot, a[j]))
            j--;

        if (i >= j)
            break;

        std::swap(a[i], a[j]);
        i++;
        j--;
    }

    quick_sort(a, low, j, cmp);
    quick_sort(a, j + 1, high, cmp);
}

#endif // QUICKSORT_H
