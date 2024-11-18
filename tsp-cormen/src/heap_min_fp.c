#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <float.h> // DBL_MAX, imprimir com %e
//#include "../include/heap_min_fp.h"
#include "../include/grafo.h"


FilaPrioridade *criar_fila_prioridade(int n) { // n é o tamanho do arranjo onde a fila será estruturada
    FilaPrioridade *Q = (FilaPrioridade *) malloc(sizeof(FilaPrioridade));
	// m0
	if (Q) {
		Q->arr = (Vertice **) malloc(n * sizeof(Vertice *));
		Q->pos = (int *) malloc(n * sizeof(int));

		if (Q->arr && Q->pos) {
			Q->m = Q->n = n;

			return Q;
		}

		if (Q->arr) 
			free(Q->arr);

        if (Q->pos) 
			free(Q->pos);

		free(Q);
	}
	return NULL;
}

void desalocar_fila_prioridade(FilaPrioridade *Q) {
    if (Q) {
		free(Q->arr); 
		free(Q->pos);
        free(Q);
    }
}

void trocar_vertices(FilaPrioridade *Q, Grafo *g, int i, int j) {
    // Faz a troca dos ponteiros dos vértices nas posições i e j da heap
    Vertice *temp = Q->arr[i];
    Q->arr[i] = Q->arr[j];
    Q->arr[j] = temp;
    
    // Computa os índices dos vértices no array original do grafo
    int vertex_i = Q->arr[i] - g->vertices;
    int vertex_j = Q->arr[j] - g->vertices;
    
    // Atualiza o array de posições
    Q->pos[vertex_i] = i;
    Q->pos[vertex_j] = j;
}

void min_heapify(FilaPrioridade *Q, Grafo *g, int i) {
    int l = left(i), r = right(i), menor = i;
    
    if (l < Q->m && Q->arr[l]->d < Q->arr[i]->d) 
        menor = l;

    if (r < Q->m && Q->arr[r]->d < Q->arr[menor]->d) 
        menor = r;

    if (menor != i) {
        trocar_vertices(Q, g, i, menor);
        min_heapify(Q, g, menor);
    }    
}

Vertice *extrair_minimo(FilaPrioridade *Q, Grafo *g) {
    if (Q->m <= 0) return NULL;
    
    Vertice *min = Q->arr[0];
    Q->arr[0] = Q->arr[Q->m - 1];
    
    // Atualiza a posição do vértice que foi movido para a raiz
    int vertex_idx = Q->arr[0] - g->vertices;
    Q->pos[vertex_idx] = 0;
    
    Q->m--;
    min_heapify(Q, g, 0);
    return min;
}

// i: (in) chave | value: (in) novo valor para a chave i
void diminuir_chave(FilaPrioridade *Q, Grafo *g, int alvo, double valor) {
    printf("Diminuindo a chave do vértice %d para %lf.\n", alvo, valor);
    int i = Q->pos[alvo];  // Obtém a posição atual na heap usando o índice do vértice no grafo
    
    if (valor < Q->arr[i]->d) {
        Q->arr[i]->d = valor;
        
        while (i > 0 && Q->arr[parent(i)]->d > Q->arr[i]->d) {
            trocar_vertices(Q, g, i, parent(i));
            i = parent(i);
        }
    }
}