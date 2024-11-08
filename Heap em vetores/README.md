# Gerenciador de Heap Máximo

Este projeto é uma implementação de um gerenciador de **Heap Máximo** utilizando um vetor estático em C. O programa possibilita a inserção e remoção de elementos no heap, bem como exibe o heap em formato de árvore, com conectores (`/` e `\`) para representar visualmente as relações entre nós.

## Funcionalidades

- **Inserção de elementos**: Insere um novo valor no heap e ajusta a estrutura para manter a propriedade de Heap Máximo.
- **Remoção do elemento máximo**: Remove o valor máximo (raiz) do heap e ajusta a estrutura.
- **Visualização do Heap em formato de árvore**: Exibe o heap em um diagrama em forma de árvore com conectores, mostrando os nós e suas relações hierárquicas.

## Estrutura do Projeto

- `heap.c`: Código principal que contém as funções de gerenciamento e impressão do Heap Máximo.

## Exemplo de Diagrama do Heap

Quando elementos são inseridos ou removidos, o heap é exibido em formato de árvore. Por exemplo:

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
   Get-ChildItem -Exclude 'Heap em vetores' | Remove-Item -Recurse -Force

3. Mantendo somente a pasta do projeto desejado (Linux):
   ```bash
   find . -maxdepth 1 ! -name 'Heap em vetores' ! -name '.' -exec rm -rf {} +

4. Entre na pasta do projeto:
   ```bash
   cd "/Heap em vetores/"

3. Compile o código:
    ```bash
    gcc heap.c -o heap

4. Execute o programa:
    ```bash
    ./heap

