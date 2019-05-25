#include <stdio.h>

double fact(double n)
{
        int i;
        double result = 1.0;

        for (i=1;i<=n;i++)
        {
                result = result*i;
        }
        return result;
}
