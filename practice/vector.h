// USAGE:
//   USE_VECTOR(typename) : instantiate vector of select type
//
// METHODS:  (ASSUME TYPE = INT)
//   int_vector* int_vector_alloc();
//   void        int_vector_push(int_vector *v, int value);
//   void        int_vector_pop(int_vector *v);
//   int         int_vector_at(int_vector *v, size_t index);

#ifndef VECTOR_EXISTS
#define VECTOR_EXISTS

#include <stdlib.h>

#define USE_VECTOR(TYPE) \
	struct TYPE##_vector { TYPE *content; size_t size, capacity; }; \
	struct TYPE##_vector* TYPE##_vector##_alloc(){ \
		struct TYPE##_vector *ret = malloc(sizeof(struct TYPE##_vector)); \
		ret->content = malloc(sizeof(TYPE)); \
		ret->size = 0, ret->capacity = 1; \
		return ret; \
	} \
	void TYPE##_vector##_push(struct TYPE##_vector *v, TYPE next){ \
		v->content[v->size++] = next; \
		if(v->size == v->capacity){ \
			v->capacity *= 2; \
			TYPE *sector = malloc(sizeof(TYPE) * v->capacity); \
			for(size_t i=0; i!=v->size; ++i) sector[i] = v->content[i]; \
			free(v->content), v->content = sector; \
		} \
	} \
	void TYPE##_vector##_pop(struct TYPE##_vector *v) { --v->size; } \
	TYPE TYPE##_vector##_at(struct TYPE##_vector *v, size_t index) { return v->content[index]; } \

#endif
