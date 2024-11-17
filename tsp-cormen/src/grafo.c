#include <math.h>
#include "../include/grafo.h"
#include "../include/heap_min_fp.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <float.h> // DBL_MAX, imprimir com %e


Grafo *criar_grafo(int qtd_vertices) {
	Grafo *g = (Grafo *) malloc(sizeof(Grafo));

	if (g) {
    	g->vertices = (Vertice *) malloc(qtd_vertices * sizeof(Vertice));

    	if (g->vertices) {
        	g->qtd_vertices = qtd_vertices;

        	for (int i = 0; i < g->qtd_vertices; i++)
            	g->vertices[i].lista_adjacencia = NULL;  	 
        	return g;
    	}
    	free(g);
	}
	return NULL;
}

void desalocar_grafo(Grafo *g) {
	if (g) {
    	if (g->vertices) {
        	No *no_atual = NULL, *prox = NULL;
       	 
        	for (int i = 0; i < g->qtd_vertices; i++) {
            	no_atual = g->vertices[i].lista_adjacencia;

            	while (no_atual) {
                	prox = no_atual->proximo_no;
                	free(no_atual);
                	no_atual = prox;
            	}
        	}
        	free(g->vertices);
    	}
    	free(g);
	}
}

No *criar_no_adjacente(int vertice, double peso) {  // "vertice" é a posição do vértice vizinho no array
	No *novo_no = (No *) malloc(sizeof(No));

	if (novo_no) {
    	novo_no->vertice = vertice;
    	novo_no->peso = peso;
    	novo_no->proximo_no = NULL;
    	return novo_no;
	}
	return NULL;
}

int aresta_existe(Grafo *g, int u, int v) {
	No *no_atual = g->vertices[u].lista_adjacencia;
    
	// Percorre a lista adj. de u para verificar se v já está nela
	while (no_atual) {
    	if (no_atual->vertice == v)
        	return 1; // (u,v) já existe   
    	no_atual = no_atual->proximo_no;
	}
	return 0; // (u,v) não existe no grafo
}

void inserir_aresta(Grafo *g, int u, int v, double peso) {
	if (g && !aresta_existe(g, u, v)) {
    	No *vizinho = criar_no_adjacente(v, peso);

    	if (vizinho) {
        	// Colocando v na lista adj. de u
        	vizinho->proximo_no = g->vertices[u].lista_adjacencia;
        	g->vertices[u].lista_adjacencia = vizinho;
       	 
        	// Coloca u na lista adj. de v, porque o grafo é simples
        	vizinho = criar_no_adjacente(u, peso);
        	if (vizinho) {
            	vizinho->proximo_no = g->vertices[v].lista_adjacencia;
            	g->vertices[v].lista_adjacencia = vizinho;
        	}
    	}
		printf("Aresta (%d,%d) com peso w(%d,%d) = %lf adicionada ao grafo (e sua contraparte também!).\n", u, v, u, v, peso);
	}
}

void exibir_lista_adjacencia(Grafo *g) {
	if (g) {
    	No *no_atual = NULL;

    	for (int i = 0; i < g->qtd_vertices; i++) {
        	no_atual = g->vertices[i].lista_adjacencia;
        	printf("\n[%d]", i);

        	while (no_atual) {
            	printf(" ~> [%d, %lf]", no_atual->vertice, no_atual->peso);
            	no_atual = no_atual->proximo_no;
        	}
    	}
    	printf("\n\n");
	}
}

void exibir_resumo(Grafo *g) {
    printf("Vértice  | Chave (d)                  | Pai (pi)\n");
    printf("---------|----------------------------|---------\n");

	double peso_total = 0;
    for (int i = 0; i < g->qtd_vertices; i++) {
        printf("%-8d | ", i);
        printf("%-26lf | ", g->vertices[i].d); // Mostrando chave com 6 casas decimais
        printf("%-8d\n", g->vertices[i].pai);
		peso_total += g->vertices[i].d;
    }

	printf("\nPeso total: %lf\n", peso_total);
}

void prim(Grafo *g, int r) {
	FilaPrioridade *Q = criar_fila_prioridade(g->qtd_vertices);
	assert(Q != NULL);

	for (int i = 0; i < g->qtd_vertices; i++) {
		g->vertices[i].d = DBL_MAX;
		g->vertices[i].pai = -1;
		g->vertices[i].enfileirado = true;
		Q->arr[i] = &g->vertices[i];
		Q->pos[i] = i;
	}

	diminuir_chave(Q, g, r, 0);

	int u = -1, v = -1;
	while (Q->m > 0) {
		min_heapify(Q, g, 0);

		Vertice *u_vertice = extrair_minimo(Q, g);
		u = u_vertice - g->vertices;
		g->vertices[u].enfileirado = false;

		No *adj = g->vertices[u].lista_adjacencia;
		while (adj) {
            v = adj->vertice;
            if (g->vertices[v].enfileirado && adj->peso < g->vertices[v].d) {
				g->vertices[v].pai = u;				// pai(v) = u
				diminuir_chave(Q, g, v, adj->peso); // key(v) = w(u,v)
            }
            adj = adj->proximo_no;
        }
	}
	desalocar_fila_prioridade(Q);
}


// implementação do percurso em pré-ordem