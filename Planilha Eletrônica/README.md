Planilha Eletrônica em C com Suporte a Fórmulas (NPR)
Este projeto implementa uma planilha eletrônica simples em C, que suporta inserção de valores numéricos e fórmulas. O usuário pode inserir fórmulas em notação infixa (como A1 + B1), e o programa converte automaticamente para Notação Polonesa Reversa (NPR) para realizar o cálculo.

Funcionalidades
Suporte a uma grade de 10x10 células (A1 a J10).
Inserção de valores numéricos simples diretamente em cada célula.
Inserção de fórmulas em notação infixa (por exemplo: A1 + B1).
Conversão automática de fórmulas infixas para Notação Polonesa Reversa (NPR).
Cálculo automático das células com base nas fórmulas inseridas.
Exibição da planilha atualizada após cada inserção.
Como Funciona
Inserir um valor: Você pode inserir um valor numérico diretamente em qualquer célula da planilha.

Exemplo:

less
Copiar código
Digite a célula (ex: A1) e o valor/fórmula (ou 'exit' para sair): A1
Digite o valor ou fórmula (infixa) para A1: 5
Inserir uma fórmula: Fórmulas podem ser inseridas no formato infixo (por exemplo, A1 + B1). O programa converte essa fórmula para NPR e calcula automaticamente o resultado.

Exemplo:

less
Copiar código
Digite a célula (ex: A1) e o valor/fórmula (ou 'exit' para sair): C1
Digite o valor ou fórmula (infixa) para C1: A1 + B1
Cálculo automático: Após inserir uma fórmula, o programa atualiza o valor da célula com o resultado do cálculo e exibe a planilha.

Sair do programa: Digite exit a qualquer momento para encerrar o programa.

Estrutura da Planilha
A planilha tem 10 colunas (A-J) e 10 linhas (1-10), o que resulta em um total de 100 células. As células podem conter valores numéricos ou fórmulas. As fórmulas podem se referir a outras células da planilha.

Exemplo de planilha após algumas inserções:

css
Copiar código
      A     B     C     D     E     F     G     H     I     J  
 1 [5.00][6.00][11.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 2 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 3 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 4 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 5 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 6 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 7 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 8 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 9 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
10 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
Como Usar
Requisitos
Compilador C (como gcc).
Terminal ou console para rodar o programa.
Passos para Executar
Clone o repositório ou copie o código fonte.

bash
Copiar código
git clone https://github.com/seu-usuario/seu-repositorio.git
Compile o código:

Copiar código
gcc planilha.c -o planilha
Execute o programa:

bash
Copiar código
./planilha
Exemplo de Uso
Após iniciar o programa, ele exibirá a planilha vazia e pedirá para o usuário inserir uma célula e um valor ou fórmula.

less
Copiar código
   A     B     C     D     E     F     G     H     I     J  
 1 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 2 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 3 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 4 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 5 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 6 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 7 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 8 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
 9 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]
10 [0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00][0.00]

Digite a célula (ex: A1) e o valor/fórmula (ou 'exit' para sair):
Para inserir um valor:

less
Copiar código
Digite a célula (ex: A1) e o valor/fórmula (ou 'exit' para sair): A1
Digite o valor ou fórmula (infixa) para A1: 5
Para inserir uma fórmula:

less
Copiar código
Digite a célula (ex: A1) e o valor/fórmula (ou 'exit' para sair): C1
Digite o valor ou fórmula (infixa) para C1: A1 + B1