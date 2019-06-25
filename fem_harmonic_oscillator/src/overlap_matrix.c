#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
void linear_overlap(double *mat,int M,int N,struct Element *e)
{

	int k=0;
	int ij=0;
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if((i-j)==0)
			{
				mat[k] = (1.0/3.0)*e[ij].h + (1.0/3.0)*e[ij+1].h;
				ij++;
				//printf("%d + %d\t",i+1,j+2);
			}
			else if((j-i)==1)
			{
				mat[k] = (1.0/6.0)*e[ij].h;
				//printf("%d\t",j);
			}
			else if((j-i)==-1)
			{
				mat[k] = (1.0/6.0)*e[ij].h;
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
void second_grade_overlap(double *mat,int M,int N,struct Element *e)
{
	int ij,k;
	k=0;
	ij=0;
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if((i-j)==0 && i%2==0)
			{
				mat[k] = 0.5*(16.0/15.0)*e[ij].h;
				//printf("%d\t",ij+1);
			}
			else if((i-j)==0 && i%2!=0)
			{
				mat[k] = 0.5*(4.0/15.0)*e[ij].h + 0.5*(4.0/15.0)*e[ij+1].h;
				//printf("%d + %d\t",ij+1,ij+2);
				ij++;
			}
			else if((j-i)==1)
			{
				mat[k] = 0.5*(2.0/15.0)*e[ij].h;
				//printf("%d\t",ij+1);

			}
			else if((j-i)==-1)
			{
				mat[k] = 0.5*(2.0/15.0)*e[ij].h;
				//printf("%d\t",ij+1);

			}
			else if((j-i)==2 && j%2!=0)
			{
				mat[k] = (-1.0)*0.5*(1.0/15.0)*e[ij].h;
				//printf("%d\t",ij+1);
			}
			else if((j-i)==-2 && j%2!=0)
			{
				mat[k] = (-1.0)*0.5*(1.0/15.0)*e[ij].h;
				// printf("%d\t",ij+1);
			}
			else
			{
				mat[k] = 0.0;
				//printf("0\t");
			}
			k++;
		}
	}

}
void overlap_matrix(double *mat,int M, int N,int option, struct Element *e)
{
	switch(option)
	{
		case 1:  //Linear Interpolation;      
			linear_overlap(mat,M,N,e);
			break;
		case 2: //Seconf grade interpolation
			second_grade_overlap(mat,M,N,e);
			break;

	};

}
