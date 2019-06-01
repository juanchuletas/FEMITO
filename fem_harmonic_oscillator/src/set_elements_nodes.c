#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"

void set_elements_nodes(struct Element *e,struct Vertex *n,int Ne,double *x)
{
        for(int i=1; i<=Ne; i++)
        {       
                        e[i].n[0].x = x[i-1];
                        e[i].n[1].x = (x[i]+x[i-1])/2.0;
                        e[i].n[2].x = x[i];

        }
}
