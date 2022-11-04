#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"
#include "Musica.h"
//#inlcude "Artista.h"


struct vector
{
    VectorType *data;
    int tipo; // tipo de dados armazenados em data
    int n_alocados; // numero de alocados
    int n_add;      // numero de adicionados
};

// passar um enum como parametro para decidir qual tipo sera posto
Vector vector_create(enum type tipo)
{
    Vector v = (Vector)calloc(1, sizeof(struct vector));
    v->n_alocados = 50;
    v->n_add = 0;
    v->tipo = tipo;
    v->data = (VectorType *)calloc(v->n_alocados, sizeof(VectorType));
    return v;
}

void vector_add(Vector v, VectorType elem)
{
    if (v->n_add == v->n_alocados)
    {
        v->n_alocados *= 2;
        v->data = (VectorType *)realloc(v->data, v->n_alocados * sizeof(VectorType));
    }

    v->data[v->n_add] = elem;
    v->n_add++;
}

VectorType vector_get(Vector v, int idx)
{
    if (idx < 0 || idx >= v->n_add)
    {
        printf("Invalid idx '%d' for vector with size '%d'.\n", idx, v->n_add);
        exit(1);
    }

    return v->data[idx];
}

int vector_size(Vector v)
{
    return v->n_add;
}

void vector_destroy(Vector v)
{
    int n_musicas = vector_size(v);
    // destroi as musicas
	for (int i=0; i<n_musicas; i++){
		musica_destroy(v->data[i]);
	}
    free(v->data);
    free(v);
}