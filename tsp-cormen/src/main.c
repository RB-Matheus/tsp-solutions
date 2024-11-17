#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/grafo.h"


int main(void) {
    int u, v, r, qtd_vertices;
    double peso;

    fscanf(stdin, "%d %d", &qtd_vertices, &r);
    Grafo *g = criar_grafo(qtd_vertices);

    while (fscanf(stdin, "%d %d %lf", &u, &v, &peso) != EOF) {
        inserir_aresta(g, u, v, peso);
    }

    prim(g, r);
    exibir_lista_adjacencia(g);
    exibir_resumo(g);
    desalocar_grafo(g);
    return EXIT_SUCCESS;
}

// < RESTRIÇÕES >
// O grafo passado tem que:
// - Ser completo (cada vértice tem caminho para os outros)
// - Ser simples (não direcionado)
// - Ter só arestas de peso não negativo

// < COMO COMPILAR >
// gcc src/main.c src/grafo.c src/heap_min_fp.c -o bin/m -Iinclude -lm -Wall -Wextra

// < COMO EXECUTAR >
// cat tests/test1.graph | bin/m
// cat tests/test2.graph | bin/m