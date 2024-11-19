import math
import matplotlib.pyplot as plt
import seaborn as sns
import sys
import time 

class Grafo:
    def __init__(self, vertices):
        self.qtd = len(vertices)
        self.matriz_distancias = [[0 for _ in range(self.qtd)] for _ in range(self.qtd)]
        self.vertices = vertices

    def adicionar_aresta(self, i, j):
        distancia = math.sqrt((self.vertices[i][0] - self.vertices[j][0]) ** 2 + (self.vertices[i][1] - self.vertices[j][1]) ** 2)
        self.matriz_distancias[i][j] = distancia
        self.matriz_distancias[j][i] = distancia

    def obter_distancia(self, i, j):
        return self.matriz_distancias[i][j]

def calcular_tamanho_rota(grafo, rota):
    tamanho = 0
    for i in range(len(rota) - 1):
        tamanho += grafo.obter_distancia(rota[i], rota[i + 1])
    tamanho += grafo.obter_distancia(rota[-1], rota[0])
    return tamanho

def dois_opt(rota, grafo):
    melhor_rota = rota
    melhor_tamanho = calcular_tamanho_rota(grafo, rota)
    melhor_encontrado = True
    plotar_rota(grafo, melhor_rota)
    time.sleep(5)
    while melhor_encontrado:
        print(melhor_rota)
        print(calcular_tamanho_rota(grafo, melhor_rota))
        melhor_encontrado = False
        for i in range(1, len(rota) - 2):
            for j in range(i + 1, len(rota)):
                nova_rota = melhor_rota[:]
                nova_rota[i:j + 1] = reversed(melhor_rota[i:j + 1])
                novo_tamanho = calcular_tamanho_rota(grafo, nova_rota)
                # plotar_rota(grafo, melhor_rota)
                # print
                if novo_tamanho < melhor_tamanho:
                    melhor_rota = nova_rota
                    melhor_tamanho = novo_tamanho
                    melhor_encontrado = True
                    break
            if melhor_encontrado:
                break
    
    return melhor_rota

def gerar_rota_inicial(num_cidades):
    return list(range(num_cidades))

def plotar_rota(grafo, rota):
    sns.set(style="whitegrid", palette="muted")
    plt.figure(figsize=(10, 10))
    cores = sns.color_palette("husl", len(grafo.vertices))
    for i, (x, y) in enumerate(grafo.vertices):
        plt.scatter(x, y, color=cores[i], s=100, edgecolor='black', zorder=5)
        plt.text(x, y, str(i), fontsize=12, ha='right', color='black')
    for i in range(len(rota) - 1):
        cidade_atual = grafo.vertices[rota[i]]
        cidade_proxima = grafo.vertices[rota[i + 1]]
        plt.plot([cidade_atual[0], cidade_proxima[0]], [cidade_atual[1], cidade_proxima[1]], 'b-', lw=2, alpha=0.8, zorder=3)
    cidade_atual = grafo.vertices[rota[-1]]
    cidade_proxima = grafo.vertices[rota[0]]
    plt.plot([cidade_atual[0], cidade_proxima[0]], [cidade_atual[1], cidade_proxima[1]], 'b-', lw=2, alpha=0.8, zorder=3)
    plt.title("Solução do Problema do Caixeiro Viajante", fontsize=16)
    plt.xlabel("Coordenada X", fontsize=12)
    plt.ylabel("Coordenada Y", fontsize=12)
    plt.legend(loc='upper right', fontsize=10, title="Cidades", title_fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.tight_layout()
    plt.show()

def ler_coordenadas_do_arquivo(arquivo):
    cidades = []
    try:
        with open(arquivo, 'r') as f:
            for linha in f:
                coords = linha.strip().split()
                cidades.append((float(coords[0]), float(coords[1])))
        return cidades
    except Exception as e:
        print(f"Erro ao ler o arquivo: {e}")
        return []

def main():
    if len(sys.argv) != 2:
        print("Uso: python programa.py <arquivo.txt>")
        sys.exit(1)
    arquivo = sys.argv[1]
    cidades = ler_coordenadas_do_arquivo(arquivo)
    if not cidades:
        print("Não foi possível ler o arquivo ou o arquivo está vazio.")
    else:
        grafo = Grafo(cidades)
        for i in range(len(cidades)):
            for j in range(i + 1, len(cidades)):
                grafo.adicionar_aresta(i, j)
        rota_inicial = gerar_rota_inicial(len(cidades))
        print("Rota Inicial:", rota_inicial)
        print("Tamanho da Rota Inicial:", calcular_tamanho_rota(grafo, rota_inicial))
        melhor_rota = dois_opt(rota_inicial, grafo)
        print("Melhor Rota após 2-opt:", melhor_rota)
        print("Tamanho da Melhor Rota:", calcular_tamanho_rota(grafo, melhor_rota))
        plotar_rota(grafo, melhor_rota)

if __name__ == "__main__":
    main()
