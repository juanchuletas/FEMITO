#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
void second_grade_pot(double *mat,int M,int N,struct Element *e,struct Vertex *n)
{
	int ij,k;
	double coeff[7];
	k=0;
	ij=0;
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if((i-j)==0 && i%2==0)
			{
				coeff[0] = (32.0/105.0)*(e[ij].n[0].x*e[ij].n[0].x) + (16.0/35.0)*(e[ij].n[0].x*e[ij+1].n[2].x) + (32.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[0];
			}
			else if((i-j)==0 && i%2!=0)
			{
				coeff[1] = (22.0/105.0)*(e[ij].n[0].x*e[ij].n[0].x) + (1.0/21.0)*(e[ij].n[0].x*e[ij].n[2].x) + (1.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				coeff[2] = (22.0/105.0)*(e[ij+1].n[0].x*e[ij+1].n[0].x) + (1.0/21.0)*(e[ij+1].n[0].x*e[ij+1].n[2].x) + (1.0/105.0)*(e[ij+1].n[2].x*e[ij+1].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[1] + (e[ij+1].h/2.0)*coeff[2];
				ij++;
			}
			else if((j-i)==1)
			{
				coeff[3] = (4.0/35.0)*(e[ij].n[0].x*e[ij].n[0].x) + (4.0/105.0)*(e[ij].n[0].x*e[ij].n[2].x) - (2.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[3];

			}
			else if((j-i)==-1)
			{
				coeff[4] = (4.0/35.0)*(e[ij].n[0].x*e[ij].n[0].x) + (4.0/105.0)*(e[ij].n[0].x*e[ij].n[2].x) - (2.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[4];
			}
			else if((j-i)==2 && j%2!=0)
			{
				coeff[5] = (22.0/105.0)*(e[ij].n[0].x*e[ij].n[0].x) + (1.0/21.0)*(e[ij].n[0].x*e[ij+1].n[2].x) + (1.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[5];
			}
			else if((j-i)==-2 && j%2!=0)
			{
				coeff[6] = (22.0/105.0)*(e[ij].n[0].x*e[ij].n[0].x) + (1.0/21.0)*(e[ij].n[0].x*e[ij].n[2].x) + (1.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[6];
			}
			else
			{
				mat[k] = 0.0;
			}
			k++;
		}
	}

}
void potential_matrix(double *mat,int M, int N,int option, struct Element *e,struct Vertex *n)
{
	switch(option)
	{
		case 1:  //Linear Interpolation;      
			//linear_pot(mat,M,N,e);
			break;
		case 2: //Seconf grade interpolation
			second_grade_pot(mat,M,N,e,e->n);
			break;

	};

}
