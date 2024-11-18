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

        	for (int i = 0; i < g->qtd_vertices; i++) {
            	g->vertices[i].lista_adjacencia = NULL;
				g->vertices[i].ultimo_vizinho = NULL;
			}  	 
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
            // Inserindo v na lista adj de u
            if (g->vertices[u].ultimo_vizinho)
                g->vertices[u].ultimo_vizinho->proximo_no = vizinho; // Já tem vizinho => atualiza o último vizinho para apontar para o novo nó
            else 
                g->vertices[u].lista_adjacencia = vizinho; // Lista de adjacência estava vazia
    
            // Atualiza o ponteiro para o último vizinho inserido
            g->vertices[u].ultimo_vizinho = vizinho;

            // Inserindo u na lista adj de v porque o grafo é não direcionado
            vizinho = criar_no_adjacente(u, peso);
            if (vizinho) {
                if (g->vertices[v].ultimo_vizinho)
                    g->vertices[v].ultimo_vizinho->proximo_no = vizinho;
                else
                    g->vertices[v].lista_adjacencia = vizinho;

                g->vertices[v].ultimo_vizinho = vizinho;
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
		printf("O vértice %d foi extraído da heap.\n", u);

		No *adj = g->vertices[u].lista_adjacencia;
		while (adj) {
            v = adj->vertice;
            if (g->vertices[v].enfileirado && adj->peso < g->vertices[v].d) {
				g->vertices[v].pai = u;				// pai(v) = u
				printf("O vértice vizinho %d agora tem pai = %d\n", v, g->vertices[v].pai);
				diminuir_chave(Q, g, v, adj->peso); // key(v) = w(u,v)
            }
            adj = adj->proximo_no;
        }
	}
	desalocar_fila_prioridade(Q);
}

/*void percurso_pre_ordem(Grafo *g, int vertice, Vertice *H, int *contador) {
	(*contador)++;
	H[*contador] = g->vertices[vertice];

	if (left(vertice) < g->qtd_vertices)
		percurso_pre_ordem(g, left(vertice), H, contador);
	
	if (right(vertice) < g->qtd_vertices)
		percurso_pre_ordem(g, right(vertice), H, contador);
}
*/

// criar rotina que chama o percurso em pré-ordem e depois adiciona a raiz como último elemento de H e adiciona ao custo total o peso da aresta que liga o penúltimo e último elemento de H?
// ajustar o exibir_ciclo para incluir seu último elemento também
void realizar_percurso(Grafo *g, int raiz, Vertice **H, double *custo_total) {
    if (g && H && custo_total && raiz > -1 && raiz < g->qtd_vertices) {
		int contador = -1; // Inicia o contador do percurso
		*custo_total = 0;

		// Chama o percurso em pré-ordem a partir da raiz
		percurso_pre_ordem(g, raiz, H, &contador, custo_total);

		// Adiciona a raiz como o último elemento de H e incrementa o custo total
		No *adj = g->vertices[H[contador] - g->vertices].lista_adjacencia;
		while (adj) {
			if (adj->vertice == H[0] - g->vertices) { // Conecta ao início
				contador++;
				H[contador] = H[0]; // Retorna à raiz
				*custo_total += adj->peso; // Adiciona o custo da volta
				break;
			}
			adj = adj->proximo_no;
		}

		if (contador == g->qtd_vertices)
			printf("Percurso completo com sucesso, incluindo o retorno à origem.\n");
		else
			printf("Erro ao conectar o retorno à origem.\n");
    }
}

void percurso_pre_ordem(Grafo *g, int vertice, Vertice **H, int *contador, double *custo_total) {
	if (g && vertice > -1 && vertice < g->qtd_vertices && *contador >= -1) {
		// Visita o vértice atual
    	(*contador)++;
    	H[*contador] = &g->vertices[vertice];
    
		//printf("H[%d] = %d\n", *contador, vertice); // vertice
		//printf("H[%d] = %ld\n", *contador, &g->vertices[vertice] - g->vertices);   Imprime a mesma coisa de cima

    	// Anda na lista de adjacência procurando os filhos
    	No *atual = g->vertices[vertice].lista_adjacencia;
		int v = -1;
    	while (atual) {
        	v = atual->vertice;

        	// Se este vértice adjacente é filho na árvore (seu pai é o vértice atual)
        	if (g->vertices[v].pai == vertice) {
				printf("O vértice %d é vizinho e filho do vértice %d.\n", atual->vertice, vertice);
				*custo_total += atual->peso;
            	percurso_pre_ordem(g, v, H, contador, custo_total);
			}

        	atual = atual->proximo_no;
    	}
	}
}

Vertice **alocar_ciclo(int qtd_vertices) {
	Vertice **H = (Vertice **) malloc((qtd_vertices + 1) * sizeof(Vertice *));

	if (H)
		return H;
	return NULL;
}

void exibir_ciclo(Grafo *g, Vertice **H, double *custo_total) {
	printf("\nPercurso: ");
    for (int i = 0; i <= g->qtd_vertices; i++) {
        printf("~> %ld ", H[i] - g->vertices);
		//printf("~> H[%d] = %ld ", i, H[i] - g->vertices);
	}
	printf("\n");
	printf("Custo total: %lf.\n", *custo_total);
}