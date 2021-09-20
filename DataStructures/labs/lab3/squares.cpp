#include <iostream>
#include <cmath>
#include <algorithm>

void compute_squares(unsigned int *a, unsigned int *b, unsigned int n)
{
    unsigned int *p;
    unsigned int *q;
    for (p = a, q = b; p < a + n; ++p, ++q)
    {
        *q = *p * *p;
    }
}

int main()
{
    unsigned int n = 10;
    unsigned int a[n] = {2, 3, 5, 7, 6, 5, 8, 2, 4, 6};
    unsigned int b[n];

    compute_squares(a, b, n);

    for (unsigned int i = 0; i < n; ++i)
    {
        std::cout << a[i] << " " << b[i] << " ";
    }
}