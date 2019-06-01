#include<stdio.h>
#include<stdlib.h>
#include "data_structures.h"

void print_elements(struct Element *e,struct Vertex *n,int M,int N)
{
	double c1,c2,c3,c4,c5,c6,c7;
	int ij,k;
	k=0;
	ij=0;
        for(int i=0; i<M; i++)
        {
                for(int j=0; j<N; j++)
                {
                        if((i-j)==0 && i%2==0)
                        {
                                c1 = (32.0/105.0)*(e[ij+1].n[0].x*e[ij+1].n[0].x) + (16.0/35.0)*(e[ij+1].n[0].x*e[ij+1].n[2].x) + (32.0/105.0)*(e[ij+1].n[2].x*e[ij+1].n[2].x);
                                //mat[k] = (e[ij+1].h/2.0)*c1;
                                printf("%lf\t",c1);
                                //printf("%d\t",ij+1);
                        }
                        else if((i-j)==0 && i%2!=0)
                        {
                                c2 = (22.0/105.0)*(e[ij+1].n[0].x*e[ij+1].n[0].x) + (1.0/21.0)*(e[ij+1].n[0].x*e[ij+1].n[2].x) + (1.0/105.0)*(e[ij+1].n[2].x*e[ij+1].n[2].x);
                                c3 = (22.0/105.0)*(e[ij+2].n[0].x*e[ij+2].n[0].x) + (1.0/21.0)*(e[ij+2].n[0].x*e[ij+2].n[2].x) + (1.0/105.0)*(e[ij+2].n[2].x*e[ij+2].n[2].x);
                                //mat[k] = (e[ij+1].h/2.0) + (e[ij+2].h/2.0);
                                printf("%lf\t",c2 + c3);
                                //printf("%d + %d\t",ij+1,ij+2);
                                ij++;
                        }
                        else if((j-i)==1)
                        {
                                c4 = (4.0/35.0)*(e[ij+1].n[0].x*e[ij+1].n[0].x) + (4.0/105.0)*(e[ij+1].n[0].x*e[ij+1].n[2].x) - (2.0/105.0)*(e[ij+1].n[2].x*e[ij+1].n[2].x);
                                //mat[k] = (e[ij+1].h/2.0);
                                printf("%lf\t",c4);
                                //printf("%d\t",ij+1);

                        }
                        else if((j-i)==-1)
                        {
                                c5 = (4.0/35.0)*(e[ij+1].n[0].x*e[ij+2].n[0].x) + (4.0/105.0)*(e[ij+1].n[0].x*e[ij+1].n[2].x) - (2.0/105.0)*(e[ij+1].n[2].x*e[ij+1].n[2].x);
                                //mat[k] = (e[ij+1].h/2.0);
                                printf("%lf\t",c5);
                                //printf("%d\t",ij+1);

                        }
                        else if((j-i)==2 && j%2!=0)
                        {
                                c6 = (22.0/105.0)*(e[ij+1].n[0].x*e[ij+1].n[0].x) + (1.0/21.0)*(e[ij+1].n[0].x*e[ij+1].n[2].x) + (1.0/105.0)*(e[ij+1].n[2].x*e[ij+1].n[2].x);
                                //mat[k] = (e[ij+1].h/2.0);
                                printf("%lf\t",c6);
                                //printf("%d\t",ij+1);
                        }
                        else if((j-i)==-2 && j%2!=0)
                        {
                                c7 = (22.0/105.0)*(e[ij+1].n[0].x*e[ij+1].n[0].x) + (1.0/21.0)*(e[ij+1].n[0].x*e[ij+1].n[2].x) + (1.0/105.0)*(e[ij+1].n[2].x*e[ij+1].n[2].x);
                                printf("%lf\t",c7);
                                //mat[k] = (e[ij+1].h/2.0);
                                // printf("%d\t",ij+1);
                        }
			else
                        {
                                //mat[k] = 0.0;
                                printf("0.000000\t");
                        }
                        k++;
                }
			printf("\n");
        }


}
