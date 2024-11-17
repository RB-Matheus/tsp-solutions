#ifndef HEAP_MIN_FP_H
#define HEAP_MIN_FP_H

#include <math.h>

#define parent(i) ((i == 0) ? -1 : (int) floor((i - 1) / 2))
#define left(i) (2 * i + 1) 
#define right(i) (2 * i + 2)

typedef struct FilaPrioridade FilaPrioridade;

struct FilaPrioridade {
    int m;             // tamanho da heap
    int n;            // tamanho do arranjo
    Vertice **arr;   // arranjo de vértices onde a fila será estruturada
	int *pos;       // array para rastrear a posição de cada vértice na heap
};

FilaPrioridade *criar_fila_prioridade(int n);
void desalocar_fila_prioridade(FilaPrioridade *Q);
void trocar_vertices(FilaPrioridade *Q, Grafo *g, int i, int j);
void min_heapify(FilaPrioridade *Q, Grafo *g, int i);
Vertice *extrair_minimo(FilaPrioridade *Q, Grafo *g);
void diminuir_chave(FilaPrioridade *Q, Grafo *g, int alvo, float valor);

#endif