# Tabela Hash com Colisões em C

Este projeto é uma implementação de uma tabela hash em C com suporte a colisões utilizando listas encadeadas. O programa permite armazenar chaves de qualquer formato (strings) e realizar buscas com contagem de passos. Uma interface interativa oferece funcionalidades como inserção de chaves, busca e geração de relatórios.

---

## Funcionalidades

1. **Inserção de Chaves**  
   - Permite inserir chaves de qualquer formato (strings).  
   - As colisões são resolvidas utilizando listas encadeadas.

2. **Busca de Chaves**  
   - Realiza buscas eficientes e retorna o número de passos necessários para encontrar a chave.  
   - Caso a chave não exista, informa que ela não foi encontrada.

3. **Relatório de Ocupação**  
   - Exibe o número de espaços ocupados e vazios na tabela hash principal.

4. **Menu Interativo**  
   - Interface amigável com opções claras para interação.

---

## Estrutura do Projeto

- **Tabela Hash**: Vetor principal com 1000 posições, onde cada posição pode conter uma lista encadeada para lidar com colisões.
- **Função Hash**: Baseada em strings, utiliza uma combinação de multiplicação (`hash * 31 + key[i]`) e módulo para gerar índices únicos.
- **Menu**: Interface interativa com opções para inserir, buscar chaves e visualizar relatórios.

---

## Requisitos

- **Compilador C** (como GCC).  
- **Sistema Operacional**: Compatível com Windows, Linux ou macOS.

---

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
   Get-ChildItem -Exclude 'Desafio Hash' | Remove-Item -Recurse -Force

3. Mantendo somente a pasta do projeto desejado (Linux):
   ```bash
   find . -maxdepth 1 ! -name 'Desafio Hash' ! -name '.' -exec rm -rf {} +

4. Entre na pasta do projeto:
   ```bash
   cd "/Desafio Hash/"

3. Compile o código:
    ```bash
    gcc hash.c -o hash

4. Execute o programa:
    ```bash
    ./hash