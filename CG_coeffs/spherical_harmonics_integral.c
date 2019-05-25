#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CG_coeffs.h"
#define PI 3.14159


int main (void)
{
	double coeff,res;
	double l1=5.0,l2=4.0,l3=1.0;

	coeff = sqrt(((2.0*l1+1.0)*(2.0*l2+1.0)*(2.0*l3+1.0))/4.0*PI);


	res = cg_coeff(l1,l2,l3,0.0,0.0,0.0);


	printf("The integral value is: %lf \n", res);

	return 0;

}
