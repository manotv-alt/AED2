# Árvore Binária de Busca em C

Este é um programa em C que implementa uma **Árvore Binária de Busca (ABB)**. O programa permite ao usuário inserir valores na árvore e, em seguida, buscar valores específicos, mostrando o caminho percorrido e o número de passos necessários para encontrar o valor.

## Funcionalidades

- **Inserção de Valores:** O usuário pode inserir valores na árvore, um de cada vez.
- **Busca de Valores:** O usuário pode buscar um valor na árvore. O programa exibe o caminho percorrido e quantos passos foram necessários para encontrar o valor (ou informa se o valor não foi encontrado).
- **Menu Interativo:** O programa apresenta um menu que permite:
  - Inserir novos valores
  - Buscar valores
  - Sair do programa

## Estrutura do Projeto

- `main.c`: Código-fonte do programa principal, incluindo as funções de criação, inserção e busca na árvore binária.

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
   Get-ChildItem -Exclude 'Árvore Binária de Busca' | Remove-Item -Recurse -Force

3. Mantendo somente a pasta do projeto desejado (Linux):
   ```bash
   find . -maxdepth 1 ! -name 'Árvore Binária de Busca' ! -name '.' -exec rm -rf {} +

4. Entre na pasta do projeto:
   ```bash
   cd "/Árvore Binária de Busca/"

3. Compile o código:
    ```bash
    gcc abb.c -o abb

4. Execute o programa:
    ```bash
    ./abb