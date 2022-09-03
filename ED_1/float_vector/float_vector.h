#ifndef FLOAT_VECTOR_H
#define FLOAT_VECTOR_H

typedef struct FloatVector float_vector;

float_vector *create(int capacity);

void destroy(float_vector *vec);

void append(float_vector *vec, int val);

void print(float_vector *vec);

int size(float_vector *vec);

int capacity(float_vector *vec);

float get(float_vector *vec, int index);

float at(float_vector *vec, int index);

void set(float_vector *vec, int val, int index);

void my_remove(float_vector *vec, int index);

#endif