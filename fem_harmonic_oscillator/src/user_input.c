#include <stdio.h>
#include <stdlib.h>

void user_input(int *Ne,double *x0, double *xN,double *hx)
{
        //MODULE TO GET THE USER INPUT
        printf("NUMBER OF ELEMENTS:\n");
        scanf("%d",Ne);
        printf("INITIAL AN FINAL POINTS: X COORDINATE\n");
        scanf("%lf %lf",x0,xN);
        *hx = (*xN-(*x0))/(double)(*Ne);
}

