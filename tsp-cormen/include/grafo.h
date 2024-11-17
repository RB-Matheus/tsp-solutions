#ifndef GRAFO_H
#define GRAFO_H

#include "heap_min_fp.h"

typedef struct No No;
typedef struct Vertice Vertice;
typedef struct Grafo Grafo;

struct No {
    int vertice;
    double peso;
    struct No *proximo_no;
};

struct Vertice {
    int pai;
    double d; // key
    int enfileirado;
    No *lista_adjacencia;
};

struct Grafo {
    int qtd_vertices;
    Vertice *vertices;
};

Grafo *criar_grafo(int qtd_vertices);
void desalocar_grafo(Grafo *g);
No *criar_no_adjacente(int vertice, double peso);
int aresta_existe(Grafo *g, int u, int v);
void inserir_aresta(Grafo *g, int u, int v, double peso);
void exibir_lista_adjacencia(Grafo *g);

Vertice **prim(Grafo *g, int r);

#endif