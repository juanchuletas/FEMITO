#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

void set_elements_2nd(struct Element *e,int Ne,double *x)
{       
        for(int i=1; i<=Ne; i++)
        {       
                e[i].n = (struct Vertex *)malloc(sizeof(struct Vertex)*3);
                //for(int j=0; j<3; j++)
                //{     
                        e[i].n[0].x = x[i-1];
                        e[i].n[1].x = (x[i]+x[i-1])/2.0;
                        e[i].n[2].x = x[i];
                        //printf("e[%d].n[%d]\n",i,j);

                //}
        }
	for(int i=1; i<=Ne;i++)
	{
		e[i].h = x[i] - x[i-1];
	}


}
