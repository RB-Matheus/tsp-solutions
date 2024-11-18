#ifndef GRAFO_H
#define GRAFO_H

typedef struct No No;
typedef struct Vertice Vertice;
typedef struct Grafo Grafo;

#include "heap_min_fp.h"

struct No {
    int vertice;
    double peso;
    struct No *proximo_no;
};

struct Vertice {
    int pai;
    double d; // peso mínimo de qualquer aresta conectando este vértice a outro na árvore
    int enfileirado;
    No *lista_adjacencia;
    No *ultimo_vizinho;
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
void exibir_resumo(Grafo *g);

void prim(Grafo *g, int r);
Vertice **alocar_ciclo(int qtd_vertices);
void realizar_percurso(Grafo *g, int raiz, Vertice **H, double *custo_total);
void percurso_pre_ordem(Grafo *g, int vertice, Vertice **H, int *contador, double *custo_total);
void exibir_ciclo(Grafo *g, Vertice **H, double *custo_total);

#endif