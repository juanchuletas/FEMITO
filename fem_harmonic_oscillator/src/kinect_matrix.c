#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
void linear_kin(double *mat,int M,int N,struct Element *e)
{
	int k=0;
        for(int i=0; i<M; i++)
        {
                for(int j=0; j<N; j++)
                {
                        if((i-j)==0)
                        {
                                mat[k] = (1.0/e[i+1].h) + (1.0/e[j+2].h);
                                //printf("%d + %d\t",i+1,j+2);
                        }
                        else if((j-i)==1)
                        {
                                mat[k] = (1.0/e[j+1].h)*(-1.0);
                                //printf("%d\t",j);

                        }
                        else if((j-i)==-1)
                        {
                                mat[k] = (1.0/e[i+1].h)*(-1.0);

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
void second_grade_kin(double *mat,int M,int N,struct Element *e)
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
				mat[k] = (2.0/e[ij+1].h)*(8.0/3.0);
				//printf("%d\t",ij+1);
			}
			else if((i-j)==0 && i%2!=0)
			{
				mat[k] = (2.0/e[ij+1].h)*(7.0/6.0) + (2.0/e[ij+2].h)*(7.0/6.0);
				//printf("%d + %d\t",ij+1,ij+2);
				ij++;
			}
			else if((j-i)==1)
			{
				mat[k] = (-1.0)*(2.0/e[ij+1].h)*(4.0/3.0);
				//printf("%d\t",ij+1);

			}
			else if((j-i)==-1)
			{
				mat[k] = (-1.0)*(2.0/e[ij+1].h)*(4.0/3.0);
				//printf("%d\t",ij+1);

			}
			else if((j-i)==2 && j%2!=0)
			{
				mat[k] = (2.0/e[ij+1].h)*(7.0/6.0);
				//printf("%d\t",ij+1);
			}
			else if((j-i)==-2 && j%2!=0)
			{
				mat[k] = (2.0/e[ij+1].h)*(7.0/6.0);
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
void kinect_matrix(double *mat,int M, int N,int option, struct Element *e)
{
	switch(option)
	{
		case 1:  //Linear Interpolation;      
			linear_kin(mat,M,N,e);
			break;
		case 2: //Seconf grade interpolation
			second_grade_kin(mat,M,N,e);
			break;

	};

}
