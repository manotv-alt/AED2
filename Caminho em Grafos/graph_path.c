#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define V 5

void floydWarshall(int graph[V][V], int dist[V][V], int next[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            next[i][j] = (graph[i][j] != INF && i != j) ? j : -1;
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void printPath(int next[V][V], int u, int v) {
    if (next[u][v] == -1) {
        printf("Nao existe caminho entre %d e %d\n", u, v);
        return;
    }

    printf("Caminho: %d", u);
    while (u != v) {
        u = next[u][v];
        printf(" -> %d", u);
    }
    printf("\n");
}

void initializeGraph(int graph[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INF;
            }
        }
    }

    // Valores iniciais do grafo
    graph[0][1] = 3;
    graph[0][2] = 8;
    graph[1][3] = 1;
    graph[2][4] = 2;
    graph[3][4] = 4;
}

void modifyGraph(int graph[V][V]) {
    int u, v, w;
    printf("\nInsira as arestas no formato: origem destino peso (digite -1 -1 -1 para terminar).\n");

    while (1) {
        printf("Origem Destino Peso: ");
        scanf("%d %d %d", &u, &v, &w);

        if (u == -1 && v == -1 && w == -1) break;

        if (u < 0 || u >= V || v < 0 || v >= V || w < 0) {
            printf("Valores invalidos. Tente novamente.\n");
            continue;
        }

        graph[u][v] = w;
    }
}

void displayGraph(int graph[V][V]) {
    printf("\n### Grafo Atual ###\n");
    printf("Legenda: INF = Infinito (sem conexao)\n\n");

    for (int i = 0; i < V; i++) {
        printf("Vertice %d: ", i);
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == INF) {
                printf("(->%d: INF) ", j);
            } else {
                printf("(->%d: %d) ", j, graph[i][j]);
            }
        }
        printf("\n");
    }
}

void menu() {
    int graph[V][V];
    int dist[V][V], next[V][V];
    int option;

    initializeGraph(graph);
    floydWarshall(graph, dist, next);

    do {
        printf("\n=====================================\n");
        printf("   Simulador de Caminhos em Grafos   ");
        printf("\n=====================================\n");
        printf("1. Exibir grafo atual\n");
        printf("2. Modificar grafo\n");
        printf("3. Encontrar caminho entre vertices\n");
        printf("4. Sair");
        printf("\n=====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                displayGraph(graph);
                break;

            case 2:
                modifyGraph(graph);
                floydWarshall(graph, dist, next);
                printf("\nGrafo atualizado!\n");
                break;

            case 3: {
                int origin, destination;
                printf("\nDigite a origem (0 a %d): ", V - 1);
                scanf("%d", &origin);
                printf("Digite o destino (0 a %d): ", V - 1);
                scanf("%d", &destination);

                if (origin < 0 || origin >= V || destination < 0 || destination >= V) {
                    printf("Vertices invalidos. Tente novamente.\n");
                } else if (dist[origin][destination] == INF) {
                    printf("Nao existe caminho entre %d e %d\n", origin, destination);
                } else {
                    printf("Menor distancia: %d\n", dist[origin][destination]);
                    printPath(next, origin, destination);
                }
                break;
            }

            case 4:
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (option != 4);
}

int main() {
    menu();
    return 0;
}