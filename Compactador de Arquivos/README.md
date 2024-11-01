# Algoritmo de Compressão e Descompressão com Árvores de Huffman

Este projeto implementa um algoritmo de compressão e descompressão de arquivos usando a árvore de Huffman, que é um método de compressão de dados sem perda de informações. A compressão de Huffman é amplamente utilizada em sistemas que requerem eficiência na codificação de dados, como em algoritmos de compressão de arquivos e transmissão de dados.

## Descrição do Algoritmo

O algoritmo de Huffman funciona atribuindo códigos de bits menores para caracteres que ocorrem com maior frequência, resultando em uma compressão eficaz. Os passos principais do algoritmo são:

1. Calcular a frequência de cada caractere no arquivo.
2. Construir uma árvore binária (Árvore de Huffman) onde os caracteres mais frequentes estão mais próximos da raiz.
3. Gerar códigos de bits únicos para cada caractere com base no caminho da raiz até as folhas da árvore.
4. Escrever o arquivo comprimido usando os códigos de Huffman e armazenar as informações de frequência para que possam ser recuperadas na descompressão.

## Estrutura do Código

### Principais Funções

- **createMinHeap**: Inicializa uma min-heap para auxiliar na construção da árvore.
- **minHeapify** e **insertMinHeap**: Mantêm a estrutura da min-heap durante a construção.
- **buildHuffmanTree**: Cria a árvore de Huffman com base nas frequências dos caracteres.
- **generateCodes**: Gera os códigos de Huffman para cada caractere.
- **compress**: Lê o arquivo de entrada, calcula as frequências e gera o arquivo comprimido.
- **decompress**: Lê o arquivo comprimido e reconstrói o conteúdo original.

### Estrutura de Dados

- **MinHeapNode**: Representa um nó na árvore de Huffman.
- **MinHeap**: Estrutura auxiliar para construir a árvore de Huffman.

## Arquivos de Entrada e Saída

- `input.txt`: Arquivo de texto que será comprimido.
- `compressed_output.bin`: Arquivo binário gerado após a compressão.
- `decompressed_output.txt`: Arquivo gerado após a descompressão, contendo o conteúdo original de `input.txt`.

## Como Usar

### Requisitos

- Compilador C (como `gcc`).
- Terminal ou console para rodar o programa.

### Instruções

1. Coloque o texto a ser comprimido no arquivo "input.txt".

2. Esse texto não deve conter caracteres especiais ou acentuações.

### Passos para Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/manotv-alt/AED2.git

2. Entre na pasta do repositório:
   ```bash
   cd ./AED2/

3. Mantendo somente a pasta do projeto desejado (Windows):
   ```bash
   Get-ChildItem -Exclude 'Compactador de Arquivos' | Remove-Item -Recurse -Force

3. Mantendo somente a pasta do projeto desejado (Linux):
   ```bash
   find . -maxdepth 1 ! -name 'Compactador de Arquivos' ! -name '.' -exec rm -rf {} +

4. Entre na pasta do projeto:
   ```bash
   cd "/Compactador de Arquivos/"

3. Compile o código:
    ```bash
    gcc huffman.c -o huffman

4. Execute o programa:
    ```bash
    ./huffman
