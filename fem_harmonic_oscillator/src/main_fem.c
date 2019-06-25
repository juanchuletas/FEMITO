#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_structures.h"

extern void user_input(int *Ne,double *x0, double *xN,double *hx);
extern void set_elements(struct Element *e,struct Vertex *n,int Ne, double *x,int option);
extern void overlap_matrix(double *mat,int N,int M,int option,struct Element *e);
extern void kinect_matrix(double *mat,int N,int M,int option,struct Element *e);
extern void hij_matrix(double *m,double *v,double *k,int N,int M);
extern void potential_matrix(double *mat,int N,int M,int option,struct Element *e,struct Vertex *n);
extern void print_matrix(char *str, int M,int N,double *a);
extern void diag (int n, double *h, double *s, double *e, double *v);
extern void pot_over_mesh(double *mat,int M, int N,int option, struct Element *e,struct Vertex *n);
void linear_interpolation(int option,int pot)
{
	int Ne,N,M;
        double x0,xN,hx;

        user_input(&Ne,&x0,&xN,&hx);


        M = (Ne-1);
        N = (Ne-1);
        double *x,*s_mat,*v_mat,*k_mat,*h_mat,*ei,*ci;
        struct Element *e;


        e = (struct Element *)malloc(sizeof(struct Element)*Ne);
        s_mat = (double *)malloc(sizeof(double)*(M*N));
        k_mat = (double *)malloc(sizeof(double)*(M*N));
        v_mat = (double *)malloc(sizeof(double)*(M*N));
        h_mat = (double *)malloc(sizeof(double)*(M*N));
        ci = (double *)malloc(pow(M,2)*sizeof(double));
        ei = (double *)malloc((N)*sizeof(double));
        x = (double *)malloc(sizeof(double)*(Ne+1));
	for(int i=0; i<Ne+1; i++)
        {       
                x[i] = x0 + hx*i;
               // printf("Vertex value x[%d] = %lf\n",i,x[i]);
        
        }
	set_elements(e,e->n,Ne,x,option);
	/*for(int i=0; i<Ne; i++)
        {
                        printf("e[%d].h = %lf\n",i,e[i].h);
        }
	for(int i=0; i<Ne; i++)
        {
                for(int j=0; j<2; j++)
                {
                        printf("e[%d].n[%d].x = %lf\n",i,j,e[i].n[j].x);

                }
        }*/
	overlap_matrix(s_mat,M,N,option,e);
	//print_matrix("OVERLAP MATRIX",M,N,s_mat);
	kinect_matrix(k_mat,M,N,option,e);
	//print_matrix("KINECT ENERGY MATRIX",M,N,k_mat);
	switch(pot)
	{
		case 1: //Analitic Potential
			potential_matrix(v_mat,M,N,option,e,e->n);
			//print_matrix("POTENTIAL ENERGY MATRIX",M,N,v_mat);
			break;
		case 2:
			pot_over_mesh(v_mat,M,N,option,e,e->n);
			//print_matrix("POTENTIAL ENERGY MATRIX",M,N,v_mat);
			break;
	};
	hij_matrix(h_mat,v_mat,k_mat,M,N);
	//print_matrix("H MATRIX",M,N,h_mat);
	diag(M,h_mat,s_mat,ei,ci);
	print_matrix("EIGENVALUES",1,M,ei);

	free(x);
        free(ci);
        free(ei);
        free(h_mat);
        free(v_mat);
        free(k_mat);
        free(s_mat);
        free(e);


}
void second_grade_interpolation(int option,int pot)
{
	int Ne,M,N;
	double x0,xN,hx,*x;

	user_input(&Ne,&x0,&xN,&hx);


	M=(Ne*2)-1;
        N=(Ne*2)-1;
	
	double *s_mat,*v_mat,*h_mat,*k_mat,*ei,*ci;
	struct Element *e;

	e = (struct Element *)malloc(sizeof(struct Element)*(Ne));
        s_mat = (double *)malloc(sizeof(double)*(M*N));
        k_mat = (double *)malloc(sizeof(double)*(M*N));
        v_mat = (double *)malloc(sizeof(double)*(M*N));
        h_mat = (double *)malloc(sizeof(double)*(M*N));
        ci = (double *)malloc(pow(M,2)*sizeof(double));
	ei = (double *)malloc((N)*sizeof(double));
        x = (double *)malloc(sizeof(double)*(Ne+1));

	for(int i=0; i<Ne+1; i++)
        {       
                x[i] = x0 + hx*i;
               // printf("Vertex value x[%d] = %lf\n",i,x[i]);
        
        }
	set_elements(e,e->n,Ne,x,option);
	/*for(int i=0; i<Ne; i++)
        {
                        printf("e[%d].h = %lf\n",i,e[i].h);
        }
	for(int i=0; i<Ne; i++)
        {
                for(int j=0; j<3; j++)
                {
                        printf("e[%d].n[%d].x = %lf\n",i,j,e[i].n[j].x);

                }
        }*/


	overlap_matrix(s_mat,M,N,option,e);
	print_matrix("OVERLAP MATRIX",M,N,s_mat);
	kinect_matrix(k_mat,M,N,option,e);
	print_matrix("KINECT ENERGY MATRIX",M,N,k_mat);
	potential_matrix(v_mat,M,N,option,e,e->n);
	print_matrix("POTENTIAL ENERGY MATRIX",M,N,v_mat);
	hij_matrix(h_mat,v_mat,k_mat,M,N);
	print_matrix("H MATRIX",M,N,h_mat);

	diag(M,h_mat,s_mat,ei,ci);
	print_matrix("EIGENVALUES",1,M,ei);


	free(x);
	free(ci);
	free(ei);
	free(h_mat);
	free(v_mat);
	free(k_mat);
	free(s_mat);
	free(e);



}

int main(void)
{
	
	int option;
	int pot;

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
	printf("******                2. Second Grade Interpolation           ******\n");
        printf("*********************************************************************\n");
        printf("Number of option:\n");
	scanf("%d",&option);
	switch(option)
	{
		case 1:
        		printf("*********************************************************************\n");
			printf("                      Linear Interpolation:			     \n");
        		printf("*********************************************************************\n");
			printf("******                Select your option:                      ******\n");
			printf("******                1. Analitic Potential                    ******\n");
			printf("******                2. Potential Over The Mesh               ******\n");
        		printf("*********************************************************************\n");
			scanf("%d",&pot);
			linear_interpolation(option,pot);
			break;
		case 2: 
        		printf("*********************************************************************\n");
			printf("                    Second Grade Interpolation:			     \n");
        		printf("*********************************************************************\n");
			printf("******                Select your option:                      ******\n");
			printf("******                1. Analitic Potential                    ******\n");
			printf("******                2. Potential Over The Mesh               ******\n");
        		printf("*********************************************************************\n");
			scanf("%d",&pot);
			second_grade_interpolation(option,pot);
			break;
	};

	return 0;

}
