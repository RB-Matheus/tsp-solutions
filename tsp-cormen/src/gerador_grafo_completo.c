#include <stdio.h>

int main(void) {
    int tamanho_grade = 3;
    int total_vertices = tamanho_grade * tamanho_grade;


//    printf("%-20s %-20s %-20s %-20s %-20s %-20s\n",
//           "id_vertice_partida", "x_vertice_partida", "y_vertice_partida",
//           "id_vertice_destino", "x_vertice_destino", "y_vertice_destino");
//    printf("%-20s %-20s %-20s %-20s %-20s %-20s\n",
//           "--------------------", "--------------------", "--------------------",
//           "--------------------", "--------------------", "--------------------");

    for (int i = 0; i < total_vertices; i++) { // Cidades de partida
        for (int j = 0; j < total_vertices; j++) { // Cidades de destino
            if (i == j) 
                continue; // Não deixa cidade ir para ela mesma

            // Calcula coordenadas do vértice de partida
            int x_vertice_partida = i / tamanho_grade;
            int y_vertice_partida = i % tamanho_grade;

            // Calcula coordenadas do vértice de destino
            int x_vertice_destino = j / tamanho_grade;
            int y_vertice_destino = j % tamanho_grade;

            printf("%-20d %-20d %-20d %-20d %-20d %-20d\n",
                   i, x_vertice_partida, y_vertice_partida,
                   j, x_vertice_destino, y_vertice_destino);
        }
    }

    return 0;
}

// < COMO COMPILAR >
// gcc src/gerador_grafo_completo.c -o bin/s -Wall -Wextra

// < COMO EXECUTAR >
// bin/s > tests/output1600.graph