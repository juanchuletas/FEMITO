#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

void set_elements_size(struct Element *e,int Ne,double *x)
{       //struct Element *te;
	//te = (struct Element *)malloc(sizeof(struct Element)*Ne);
        /*for(int i=1; i<=Ne; i++)
        {       
                te[i].n = (struct Vertex *)malloc(sizeof(struct Vertex)*3);
                //for(int j=0; j<3; j++)
                //{     
                        te[i].n[0].x = x[i-1];
                        te[i].n[1].x = (x[i]+x[i-1])/2.0;
                        te[i].n[2].x = x[i];
                        //printf("e[%d].n[%d]\n",i,j);

                //}
        }*/
	for(int i=1; i<=Ne;i++)
	{
		e[i].h = x[i] - x[i-1];
	}

}
