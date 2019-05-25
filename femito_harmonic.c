#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Vertex
{
	double x;
};
struct Element
{
	double h;
};
extern void dsyev(char*, char*, int*, double*, int*, double*, double*, int*, int*);
void print_matrix( char* desc, int m, int n, double* a)
{
        int i, j;
        printf( "*****   %s   *****\n", desc );
        for( i = 0; i < m; i++ ) {
                for( j = 0; j < n; j++ ) printf( "  %lf  ", a[i*n+j] );
                printf( "\n" );
        }
}
void diag (int n, double *h, double *s, double *e, double *v)
{
  int lwork, i, j, k, nn, ij, info;
  static double small = 1.0e-10;
  static char *V = "V";
  static char *U = "U";
  double *work, *aux, *uno;

  lwork=3*n;
  work = (double *) malloc( lwork * sizeof (double));

  aux = (double *) malloc( n * n * sizeof (double));
  for ( ij = 0; ij < n*n; ij++ )
  {
    aux[ij] = s[ij];
  }

  dsyev( V, U, &n, aux, &n, e, work, &lwork, &info );

  if ( info !=0 )
  {
    fprintf (stderr, "Overlap matrix diagonalization failed\n");
    exit (1);
  }
// print_matrix( "S matrix ", nbasis, nbasis, aux, nbasis );
 //printf("\n");

 nn = 0;
  for ( i = 0; i < n; i++ )
  {
    if ( e[i] > small)
    {
      for ( j = 0; j < n; j++ )
      {
        aux[j+nn*n] = aux[j+i*n] / sqrt(e[i]);
      }
      nn++;
    }
  }
  if ( nn < n )
  {
     fprintf (stdout, " # of linearly independent vectors = %d\n", nn);
  }

 //print_matrix( "X matrix ", nbasis, nbasis, aux, nbasis );
 //printf("\n");

  for ( i = 0; i < n; i++)
  {
    for ( j = 0; j < nn; j++)
    {
      v[i+j*n] = 0.0;
      for  ( k = 0; k < n; k++)
      {
        v[i+j*n] = v[i+j*n] + h[i+k*n] * aux[k+j*n];
      }
    }
  }
  uno = (double *) malloc( nn * nn * sizeof (double));
  for ( i = 0; i < nn; i++ )
  {
    for ( j = 0; j < nn; j++ )
    {
      uno[i+j*nn] = 0.0;
      for  ( k = 0; k < n; k++)
      {
        uno[i+j*nn] = uno[i+j*nn] + aux[k+i*n] * v[k+j*n];
      }
    }
  }
  //print_matrix( "F\' matrix ", nbasis, nbasis, uno, nbasis );
  //printf("\n");
   /* ---------------- Diagonalization of transformed F or H matrix -------------*/
  dsyev("V", "U", &nn, uno, &nn, e, work, &lwork, &info );

  if ( info !=0 )
  {
    fprintf (stderr, "Fock matrix diagonalization failed\n");
    exit (1);
  }


  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < nn; j++ )
    {
      v[i+j*n] = 0.0;
      for  ( k = 0; k < n; k++ )
      {
        v[i+j*n] = v[i+j*n] + aux[i+k*n] * uno[k+j*nn];
      }
    }
  }
	//print_matrix( "eigenvalues ", 1, nbasis, e, 1 );
  	//printf("\n");
  free(uno); free(aux); free(work);
  return;
}
void user_input(int *Ne,double *x0, double *xN,double *hx)
{
        //MODULE TO GET THE USER INPUT
        printf("NUMBER OF ELEMENTS IN X\n");
        scanf("%d",Ne);
        printf("INITIAL AN FINAL POINTS IN X COORDINATE\n");
        scanf("%lf %lf",x0,xN);
        *hx = (*xN-(*x0))/(double)(*Ne);
}
void potential_mat(double *mat,struct Element *e,struct Vertex *v,int M,int N)
{
	int k=0;
	double coeff[4];
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if((i-j)==0)
			{
				coeff[0] = (2.0/5.0)*v[i+1].x*v[i+1].x + (1.0/5.0)*v[i].x*v[i+1].x + (1.0/15.0)*v[i].x*v[i].x;
				coeff[3] = (2.0/5.0)*v[j+1].x*v[j+1].x + (1.0/5.0)*v[j+1].x*v[j+2].x + (1.0/15.0)*v[j+2].x*v[j+2].x;
				mat[k] = 0.5*e[i+1].h*coeff[0] + 0.5*e[j+2].h*coeff[3];
				//printf("%d + %d\t",i+1,j+2);
			}
			else if((j-i)==1)
			{
				coeff[1] = (1.0/10.0)*v[j+1].x*v[j+1].x + (2.0/15.0)*v[j+1].x*v[j].x +(1.0/10.0)*v[j].x*v[j].x;
				mat[k] = 0.5*e[j+1].h*coeff[1];
				//printf("%d\t",j);

			}
			else if((j-i)==-1)
			{
				coeff[2] = (1.0/10.0)*v[i+1].x*v[i+1].x + (2.0/15.0)*v[i+1].x*v[j].x +(1.0/10.0)*v[i].x*v[i].x;
				mat[k] = 0.5*e[i+1].h*coeff[2];

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
void overlap_mat(double *mat,struct Element *e,int M,int N)
{
        int k=0;
        for(int i=0; i<M; i++)
        {
                for(int j=0; j<N; j++)
                {
                        if((i-j)==0)
                        {
                                mat[k] = (1.0/3.0)*e[i+1].h + (1.0/3.0)*e[j+2].h;
                                //printf("%d + %d\t",i+1,j+2);
                        }
                        else if((j-i)==1)
                        {
                                mat[k] = (1.0/6.0)*e[j+1].h;
                                //printf("%d\t",j);

                        }
                        else if((j-i)==-1)
                        {
                                mat[k] = (1.0/6.0)*e[i+1].h;

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
void kinect_mat(double *mat,struct Element *e,int M,int N)
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
void hij_mat(double *h_mat,double *v_mat,double *k_mat,int M)
{
	for(int i=0; i<M*M; i++)
	{
		h_mat[i] = v_mat[i] + k_mat[i];
	}

}
int main (void)
{
	int Ne;
	double x0,xN;
	double hx;
	struct Element *e;
	struct Vertex *v;

	double *s_mat,*v_mat,*h_mat,*k_mat,*ei,*ci;


	user_input(&Ne,&x0,&xN,&hx);


	e = (struct Element *)malloc(sizeof(struct Element)*Ne);
	v = (struct Vertex *)malloc(sizeof(struct Vertex)*(Ne+1));
	s_mat = (double *)malloc(sizeof(double)*(Ne-1)*(Ne-1));
	v_mat = (double *)malloc(sizeof(double)*(Ne-1)*(Ne-1));
	h_mat = (double *)malloc(sizeof(double)*(Ne-1)*(Ne-1));
	k_mat = (double *)malloc(sizeof(double)*(Ne-1)*(Ne-1));
	ci =  (double *) malloc ( pow(Ne-1,2) * sizeof (double) );
	ei = (double *) malloc ((Ne-2)*sizeof(double));




	for(int i=0; i<Ne+1; i++)
	{
		v[i].x = x0 + hx*i;
		printf("Vertex value v[%d] = %lf\n",i,v[i].x);

	}
	for(int i=1; i<=Ne; i++)
	{
		e[i].h = v[i].x - v[i-1].x;
		printf("Size of element e[%d] = %lf\n",i,e[i].h);


	}
	potential_mat(v_mat,e,v,Ne-1,Ne-1);
	print_matrix("POTENTIAL ENERGY MATRIX",Ne-1,Ne-1,v_mat);
	overlap_mat(s_mat,e,Ne-1,Ne-1);
	print_matrix("OVERLAP MATRIX",Ne-1,Ne-1,s_mat);
	kinect_mat(k_mat,e,Ne-1,Ne-1);
	print_matrix("KINECT ENERGY MATRIX",Ne-1,Ne-1,k_mat);
	hij_mat(h_mat,v_mat,k_mat,Ne-1);
	print_matrix("H ENERGY MATRIX",Ne-1,Ne-1,h_mat);


	diag(Ne-1,h_mat,s_mat,ei,ci);
	print_matrix("EIGENVALUES",1,Ne-1,e);
	

	return 0;


}
