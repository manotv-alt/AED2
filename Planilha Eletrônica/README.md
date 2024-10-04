# Planilha Eletrônica em C com Suporte a Fórmulas (NPR)

Este projeto implementa uma planilha eletrônica simples em C, que suporta a inserção de valores numéricos e fórmulas. O usuário pode inserir fórmulas em notação infixa (como `A1 + B1`), e o programa converte automaticamente para Notação Polonesa Reversa (NPR) para realizar o cálculo.

## Funcionalidades

- Suporte a uma grade de 10x10 células (A1 a J10).
- Inserção de valores numéricos simples diretamente em cada célula.
- Inserção de fórmulas em notação infixa (por exemplo: `A1 + B1`).
- Conversão automática de fórmulas infixas para Notação Polonesa Reversa (NPR).
- Cálculo automático das células com base nas fórmulas inseridas.
- Exibição da planilha atualizada após cada inserção.

## Como Funciona

1. **Inserir um valor**: Você pode inserir um valor numérico diretamente em qualquer célula da planilha.


2. **Inserir uma fórmula**: Fórmulas podem ser inseridas no formato infixo (por exemplo, `A1 + B1`). O programa converte essa fórmula para NPR e calcula automaticamente o resultado.


3. **Cálculo automático**: Após inserir uma fórmula, o programa atualiza o valor da célula com o resultado do cálculo e exibe a planilha.

4. **Sair do programa**: Digite `exit` a qualquer momento para encerrar o programa.

## Estrutura da Planilha

A planilha tem 10 colunas (A-J) e 10 linhas (1-10), totalizando 100 células. As células podem conter valores numéricos ou fórmulas, que podem se referir a outras células.

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
   Get-ChildItem -Exclude 'Planilha Eletrônica' | Remove-Item -Recurse -Force

3. Mantendo somente a pasta do projeto desejado (Linux):
   ```bash
   find . -maxdepth 1 ! -name 'Planilha Eletrônica' ! -name '.' -exec rm -rf {} +

4. Entre na pasta do projeto:
   ```bash
   cd "/Planilha Eletrônica/"

3. Compile o código:
    ```bash
    gcc planilha.c -o planilha

4. Execute o programa:
    ```bash
    ./planilha