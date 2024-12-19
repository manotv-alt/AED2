# Simulador de Caminhos em Grafos

Este projeto implementa o algoritmo de Floyd-Warshall para encontrar o caminho mais curto entre todos os pares de vértices em um grafo direcionado e ponderado. O algoritmo também exibe o caminho entre dois vértices específicos, além de permitir a modificação dinâmica do grafo.

## Descrição

O algoritmo de Floyd-Warshall calcula a menor distância entre todos os pares de vértices em um grafo, e também constrói uma matriz que permite reconstruir o caminho mais curto entre dois vértices. O grafo é representado por uma matriz de adjacência e o algoritmo leva em consideração todas as arestas do grafo, atualizando as distâncias conforme a iteratividade do processo.

### Funcionalidades

1. **Exibição do Grafo Atual**: Exibe o grafo atual, mostrando as distâncias entre os vértices. Se não houver conexão direta entre dois vértices, é mostrado "INF" (infinito).
   
2. **Modificação do Grafo**: Permite que o usuário adicione ou modifique as arestas do grafo, com o peso das arestas sendo inserido pelo usuário.

3. **Cálculo de Caminhos Mínimos**: Após a modificação do grafo, o algoritmo calcula as distâncias mínimas entre todos os pares de vértices, permitindo a consulta de caminhos entre dois vértices específicos.

4. **Menu Interativo**: O programa oferece um menu interativo onde o usuário pode escolher entre visualizar o grafo, modificar o grafo, encontrar caminhos mínimos entre dois vértices ou sair do programa.

## Estrutura do Código

### Funções Principais

- **floydWarshall**: Calcula as distâncias mínimas entre todos os pares de vértices e atualiza a matriz de caminhos.
- **printPath**: Exibe o caminho mínimo entre dois vértices.
- **initializeGraph**: Inicializa o grafo com valores padrão.
- **modifyGraph**: Permite ao usuário modificar o grafo inserindo arestas e seus respectivos pesos.
- **displayGraph**: Exibe o grafo atual no formato de matriz de adjacência.
- **menu**: Exibe o menu principal do programa e lida com as entradas do usuário.

### Estruturas de Dados

- **Graph (matriz de adjacência)**: Representação do grafo com as distâncias entre os vértices.
- **Dist (matriz de distâncias)**: Armazena a menor distância entre cada par de vértices.
- **Next (matriz de próximos vértices)**: Auxilia na reconstrução do caminho mais curto entre dois vértices.


## Como Usar

### Requisitos

- Compilador C (como `gcc`).
- Terminal ou console para rodar o programa.

### Passos para Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/manotv-alt/AED2.git

2. Entre na pasta do repositório:
   ```bash
   cd ./AED2/

3. Mantendo somente a pasta do projeto desejado (Windows):
   ```bash
   Get-ChildItem -Exclude 'Caminho em Grafos' | Remove-Item -Recurse -Force

3. Mantendo somente a pasta do projeto desejado (Linux):
   ```bash
   find . -maxdepth 1 ! -name 'Caminho em Grafos' ! -name '.' -exec rm -rf {} +

4. Entre na pasta do projeto:
   ```bash
   cd "/Caminho em Grafos/"

3. Compile o código:
    ```bash
    gcc graph_path.c -o graph_path

4. Execute o programa:
    ```bash
    ./graph_path
