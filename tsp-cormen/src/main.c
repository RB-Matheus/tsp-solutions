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

    //exibir_lista_adjacencia(g);
    //exibir_resumo(g);

//Vértice  | Chave (d)                  | Pai (pi)
//---------|----------------------------|---------
//0        | 0.000000                   | -1      
//1        | 2.000000                   | 0       
//2        | 1.414214                   | 1       
//3        | 1.414214                   | 4       
//4        | 1.414214                   | 5       
//5        | 2.000000                   | 1       
//6        | 1.414214                   | 4       
//7        | 2.236068                   | 1
// Peso total: 11.892922

    Vertice **H = alocar_ciclo(g->qtd_vertices);
    double custo_total;
    // testar se H != NULL
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
// cat tests/test3.graph | bin/m