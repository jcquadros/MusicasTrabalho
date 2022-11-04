#ifndef _VECTOR_H_
#define _VECTOR_H_
typedef enum type Type;

typedef void *VectorType;

typedef struct vector *Vector;

// aloca espaco e inicializa um vector
Vector vector_create(enum type tipo);

// adiciona um elemento ao final de um vector
void vector_add(Vector v, VectorType elem);

// retorna o elemento da posicao idx do vector
VectorType vector_get(Vector v, int idx);

// retorna o numero de elementos inseridos em v
int vector_size(Vector v);

// busca o indice da primeira ocorrencia de elem em v, ou retorna -1 se o
// elem nao existir em v
int vector_find(Vector v, VectorType elem);

// remove o elemento da posicao idx em v
void vector_remove(Vector v, int idx);

// desaloca v e suas estruturas internas
void vector_destroy(Vector v);



#endif