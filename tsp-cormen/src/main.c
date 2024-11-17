#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/grafo.h"


int main(void) {
    int u, v, r, qtd_vertices;
    double xu, xv, yu, yv;

    fscanf(stdin, "%d %d", &qtd_vertices, &r);
    Grafo *g = criar_grafo(qtd_vertices);

    while (fscanf(stdin, "%d %lf %lf %d %lf %lf", &u, &xu, &yu, &v, &xv, &yv) != EOF) {
        inserir_aresta(g, u, v, sqrt(pow(xv - xu, 2) + pow(yv - yu, 2)));
    }

    exibir_lista_adjacencia(g);
    desalocar_grafo(g);
    return EXIT_SUCCESS;
}

// < RESTRIÇÕES >
// O grafo passado tem que:
// - Ser completo (cada vértice tem caminho para os outros)
// - Ser simples (não direcionado)
// - Ter só arestas de peso não negativo

// < COMO COMPILAR >
// gcc src/main.c src/grafo.c -o bin/m -Iinclude -lm -Wall -Wextra

// < COMO EXECUTAR >
// cat tests/test.graph | bin/m