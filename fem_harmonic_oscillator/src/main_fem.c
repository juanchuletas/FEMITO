#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_structures.h"

extern void user_input(int *Ne,double *x0, double *xN,double *hx);
extern void set_elements_2nd(struct Element *e,int Ne, double *x);
extern void overlap_matrix(double *mat,int N,int M,int option,struct Element *e);
extern void kinect_matrix(double *mat,int N,int M,int option,struct Element *e);
extern void print_matrix(char *str, int M,int N,double *a);
void second_grade_interpolation(int option)
{
	int Ne,M,N;
	double x0,xN,hx,*x;

	user_input(&Ne,&x0,&xN,&hx);


	M=(Ne*2)-1;
        N=(Ne*2)-1;
	
	double *s_mat,*v_mat,*h_mat,*k_mat,*ei,*ci;
	struct Element *e;

	e = (struct Element *)malloc(sizeof(struct Element)*Ne);
        s_mat = (double *)malloc(sizeof(double)*((Ne*2)-1)*((Ne*2)-1));
        k_mat = (double *)malloc(sizeof(double)*((Ne*2)-1)*((Ne*2)-1));
        v_mat = (double *)malloc(sizeof(double)*((Ne*2)-1)*((Ne*2)-1));
        h_mat = (double *)malloc(sizeof(double)*((Ne*2)-1)*((Ne*2)-1));
        ci = (double *)malloc(pow((Ne*2)-1,2)*sizeof(double));
	ei = (double *)malloc(((Ne*2)-1)*sizeof(double));
        x = (double *)malloc(sizeof(double)*(Ne+1));

	for(int i=0; i<Ne+1; i++)
        {       
                x[i] = x0 + hx*i;
                printf("Vertex value x[%d] = %lf\n",i,x[i]);
        
        }
	set_elements_2nd(e,Ne,x);
	for(int i=1; i<=Ne; i++)
        {
                for(int j=0; j<3; j++)
                {
                        printf("e[%d].n[%d].x = %lf\n",i,j,e[i].n[j].x);

                }
        }
	overlap_matrix(s_mat,M,N,option,e);
	print_matrix("OVERLAP MATRIX",M,N,s_mat);
	kinect_matrix(k_mat,M,N,option,e);
	print_matrix("KINECT ENERGY MATRIX",M,N,k_mat);


	free(s_mat);
	free(k_mat);



}

int main(void)
{
	
	int option;

        printf("*********************************************************************\n");
        printf("                   ********** FEMITO **********                      \n");
        printf("*********************************************************************\n");
        printf("***** Energy Levels Of The 1D Simple Harmonic Oscillator In The *****\n");
        printf("***** 		      Finite Element Method   			*****\n");
        printf("*****          With Linear Interpolation Functions              *****\n");
        printf("***** 				& 				*****\n");
        printf("*****          Second Grade Interpolation Functions             *****\n");
        printf("*********************************************************************\n");



        printf("*********************************************************************\n");
	printf("******                Select your option:                      ******\n");
	printf("******                1. Linear Interpolation                  ******\n");
	printf("******                2. Second Grade  Interpolation           ******\n");
        printf("*********************************************************************\n");
        printf("Number of option:\n");
	scanf("%d",&option);

	switch(option)
	{
		case 1:

			//linear_interpolation();
			break;
		case 2: 
			second_grade_interpolation(option);
			break;
	};

}
