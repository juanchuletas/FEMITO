#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

//extern void pot_mesh(double *f);
void linear_pot_over_mesh(double *mat,int M,int N,struct Element *e,struct Vertex *n)
{
	int k=0;
	int ij=0;
	double coeff[4];
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if((i-j)==0)
			{
				coeff[0] = (1.0/6.0)*e[ij].n[0].x*e[ij].n[0].x + (1.0/2.0)*e[ij].n[1].x*e[ij].n[1].x;
				coeff[3] = (1.0/6.0)*e[ij+1].n[0].x*e[ij+1].n[0].x + (1.0/2.0)*e[ij+1].n[1].x*e[ij+1].n[1].x;
				mat[k] = 0.5*e[ij].h*coeff[0] + 0.5*e[ij+1].h*coeff[3];
				ij++;
				//printf("%d + %d\t",i+1,j+2);
			}
			else if((j-i)==1)
			{
				coeff[1] = (1.0/6.0)*e[ij].n[1].x*e[ij].n[1].x + (1.0/6.0)*e[ij].n[0].x*e[ij].n[0].x;
				mat[k] = 0.5*e[ij].h*coeff[1];
				//printf("%d\t",j);

			}
			else if((j-i)==-1)
			{
				coeff[2] = (1.0/6.0)*e[ij].n[1].x*e[ij].n[1].x + (1.0/6.0)*e[ij].n[0].x*e[ij].n[0].x;
				mat[k] = 0.5*e[ij].h*coeff[2];

				//printf("%d\t",i);
			}
			else
			{
				mat[k] = 0.0;
				//printf("%d\t",0);
			}
			k++;
		}
		//printf("\n");
}
}
/*void second_grade_pot(double *mat,int M,int N,struct Element *e,struct Vertex *n)
{
	int ij,k;
	double coeff[9];
	k=0;
	ij=0;
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if((i-j)==0 && i%2==0)
			{
				coeff[0] = (32.0/105.0)*(e[ij].n[0].x*e[ij].n[0].x) + (16.0/35.0)*(e[ij].n[0].x*e[ij].n[2].x) + (32.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[0];
			}
			else if((i-j)==0 && i%2!=0)
			{
				coeff[1] = (1.0/105.0)*(e[ij].n[0].x*e[ij].n[0].x) + (1.0/21.0)*(e[ij].n[0].x*e[ij].n[2].x) + (22.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				coeff[2] = (22.0/105.0)*(e[ij+1].n[0].x*e[ij+1].n[0].x) + (1.0/21.0)*(e[ij+1].n[0].x*e[ij+1].n[2].x) + (1.0/105.0)*(e[ij+1].n[2].x*e[ij+1].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[1] + (e[ij+1].h/2.0)*coeff[2];
				ij++;
			}
			else if((j-i)==1 && j%2==0)
			{
				coeff[3] = (4.0/35.0)*(e[ij].n[0].x*e[ij].n[0].x) + (4.0/105.0)*(e[ij].n[0].x*e[ij].n[2].x) - (2.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[3];

			}
			else if((j-i)==-1 && i%2==0)
			{
				coeff[4] = (4.0/35.0)*(e[ij].n[0].x*e[ij].n[0].x) + (4.0/105.0)*(e[ij].n[0].x*e[ij].n[2].x) - (2.0/105.0)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (e[ij].h/2.0)*coeff[4];
			}
			else if((j-i)==1 && j%2!=0)
			{
				coeff[5] = (4.0/35.0)*(e[ij].n[2].x*e[ij].n[2].x) + (4.0/105.0)*(e[ij].n[0].x*e[ij].n[2].x) - (2.0/105.0)*(e[ij].n[0].x*e[ij].n[0].x);
				mat[k] = (e[ij].h/2.0)*coeff[5];
			}
			else if((j-i)==-1 && i%2!=0)
			{
				coeff[6] = (4.0/35.0)*(e[ij].n[2].x*e[ij].n[2].x) + (4.0/105.0)*(e[ij].n[0].x*e[ij].n[2].x) - (2.0/105.0)*(e[ij].n[0].x*e[ij].n[0].x);
				mat[k] = (e[ij].h/2.0)*coeff[6];

			}
			else if((j-i)==2 && j%2!=0)
			{
				coeff[7] = (1.0/42)*(e[ij].n[0].x*e[ij].n[0].x) + (2.0/105)*(e[ij].n[0].x*e[ij].n[2].x) + (1.0/42)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (-1.0)*(e[ij].h/2.0)*coeff[7];
			}
			else if((j-i)==-2 && j%2!=0)
			{
				coeff[8] = (1.0/42)*(e[ij].n[0].x*e[ij].n[0].x) + (2.0/105)*(e[ij].n[0].x*e[ij].n[2].x) + (1.0/42)*(e[ij].n[2].x*e[ij].n[2].x);
				mat[k] = (-1.0)*(e[ij].h/2.0)*coeff[8];
			}
			else
			{
				mat[k] = 0.0;
			}
			k++;
		}
	}

}*/
void pot_over_mesh(double *mat,int M, int N,int option, struct Element *e,struct Vertex *n)
{
	switch(option)
	{
		case 1:  //Linear Interpolation;      
			linear_pot_over_mesh(mat,M,N,e,e->n);
			break;
		case 2: //Seconf grade interpolation
			//second_grade_pot(mat,M,N,e,e->n);
			break;

	};

}
