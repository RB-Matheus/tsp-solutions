#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/grafo.h"


int main(void) {
    int u, v, r, qtd_vertices;
    double xu, yu, xv, yv;

    fscanf(stdin, "%d %d", &qtd_vertices, &r);

    Grafo *g = criar_grafo(qtd_vertices);
    assert(g != NULL);

    Vertice **H = alocar_ciclo(g->qtd_vertices);
    assert(H != NULL);

    while (fscanf(stdin, "%d %lf %lf %d %lf %lf", &u, &xu, &yu, &v, &xv, &yv) != EOF) {
            inserir_aresta(g, u, v, sqrt(pow(xv - xu, 2) + pow(yv - yu, 2)));
    }

    prim(g, r);
    double custo_total;
    realizar_percurso(g, r, H, &custo_total);
    exibir_resumo(g);
    exibir_ciclo(g, H, &custo_total);

    desalocar_grafo(g);
    free(H);
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
// cat tests/output400.graph | bin/m
