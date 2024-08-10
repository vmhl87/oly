#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
USE_VECTOR(int);

int main(){
	struct int_vector *v = int_vector_alloc();

	for(int i=-3; i<4; ++i) int_vector_push(v, i);
	while(v->size) printf("%d%c", int_vector_at(v, --v->size), " \n"[v->size==1]);
}
