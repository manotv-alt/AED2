#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ALUNOS 10
#define MAX_FORMULA 100
#define MAX_PILHA 100

// Estrutura para armazenar as informações dos alunos
typedef struct {
    float prova1;
    float prova2;
    float frequencia;
} Aluno;

// Pilha usada para conversão e avaliação
typedef struct {
    char itens[MAX_PILHA];
    int topo;
} PilhaChar;

typedef struct {
    float itens[MAX_PILHA];
    int topo;
} PilhaFloat;

// Funções para pilha de char
void inicializarPilhaChar(PilhaChar *p) {
    p->topo = -1;
}

int pilhaVaziaChar(PilhaChar *p) {
    return p->topo == -1;
}

void empilharChar(PilhaChar *p, char valor) {
    if (p->topo < MAX_PILHA - 1) {
        p->itens[++(p->topo)] = valor;
    }
}

char desempilharChar(PilhaChar *p) {
    if (!pilhaVaziaChar(p)) {
        return p->itens[(p->topo)--];
    }
    return '\0'; // Erro: pilha vazia
}

char topoChar(PilhaChar *p) {
    if (!pilhaVaziaChar(p)) {
        return p->itens[p->topo];
    }
    return '\0'; // Erro: pilha vazia
}

// Funções para pilha de float
void inicializarPilhaFloat(PilhaFloat *p) {
    p->topo = -1;
}

int pilhaVaziaFloat(PilhaFloat *p) {
    return p->topo == -1;
}

void empilharFloat(PilhaFloat *p, float valor) {
    if (p->topo < MAX_PILHA - 1) {
        p->itens[++(p->topo)] = valor;
    }
}

float desempilharFloat(PilhaFloat *p) {
    if (!pilhaVaziaFloat(p)) {
        return p->itens[(p->topo)--];
    }
    return 0; // Erro: pilha vazia
}

// Função para determinar a precedência dos operadores
int precedencia(char operador) {
    switch (operador) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
            return 0;
    }
    return -1; // Operador inválido
}

// Função para converter a expressão infixa para pós-fixa (notação polonesa reversa)
void infixoParaPosfixo(char* infixo, char* posfixo) {
    PilhaChar pilha;
    inicializarPilhaChar(&pilha);
    int j = 0;

    for (int i = 0; infixo[i] != '\0'; i++) {
        char c = infixo[i];

        // Se for um operando (P1, P2, F), apenas adiciona à saída
        if (isalnum(c)) {
            posfixo[j++] = c;
        }
        // Se for um parêntese de abertura, empilha
        else if (c == '(') {
            empilharChar(&pilha, c);
        }
        // Se for um parêntese de fechamento, desempilha até encontrar o parêntese de abertura
        else if (c == ')') {
            while (!pilhaVaziaChar(&pilha) && topoChar(&pilha) != '(') {
                posfixo[j++] = desempilharChar(&pilha);
            }
            desempilharChar(&pilha); // Remove o '(' da pilha
        }
        // Se for um operador, desempilha operadores de maior ou igual precedência e empilha o atual
        else if (strchr("+-*/", c)) {
            while (!pilhaVaziaChar(&pilha) && precedencia(topoChar(&pilha)) >= precedencia(c)) {
                posfixo[j++] = desempilharChar(&pilha);
            }
            empilharChar(&pilha, c);
        }
    }

    // Desempilha o que sobrou na pilha
    while (!pilhaVaziaChar(&pilha)) {
        posfixo[j++] = desempilharChar(&pilha);
    }

    posfixo[j] = '\0'; // Termina a string
}

// Função para avaliar a expressão pós-fixa
float avaliarPosfixo(char* posfixo, Aluno aluno) {
    PilhaFloat pilha;
    inicializarPilhaFloat(&pilha);
    
    for (int i = 0; posfixo[i] != '\0'; i++) {
        char c = posfixo[i];

        // Se for um operando, empilha o valor correspondente
        if (c == 'P') {
            i++; // Avança para o número da prova
            if (posfixo[i] == '1') {
                empilharFloat(&pilha, aluno.prova1);
            } else if (posfixo[i] == '2') {
                empilharFloat(&pilha, aluno.prova2);
            }
        } else if (c == 'F') {
            empilharFloat(&pilha, aluno.frequencia);
        }
        // Se for um operador, desempilha dois operandos, realiza a operação e empilha o resultado
        else if (strchr("+-*/", c)) {
            float op2 = desempilharFloat(&pilha);
            float op1 = desempilharFloat(&pilha);

            switch (c) {
                case '+':
                    empilharFloat(&pilha, op1 + op2);
                    break;
                case '-':
                    empilharFloat(&pilha, op1 - op2);
                    break;
                case '*':
                    empilharFloat(&pilha, op1 * op2);
                    break;
                case '/':
                    if (op2 != 0) {
                        empilharFloat(&pilha, op1 / op2);
                    } else {
                        printf("Erro: Divisão por zero.\n");
                        return 0;
                    }
                    break;
            }
        }
    }

    return desempilharFloat(&pilha); // O resultado final será o único valor restante na pilha
}

int main() {
    int numAlunos;
    Aluno alunos[MAX_ALUNOS];
    char formula[MAX_FORMULA], posfixa[MAX_FORMULA];

    // Solicitar o número de alunos
    printf("Digite o número de alunos (máximo %d): ", MAX_ALUNOS);
    scanf("%d", &numAlunos);

    // Entrada de dados para cada aluno
    for (int i = 0; i < numAlunos; i++) {
        printf("\nAluno %d:\n", i + 1);

        printf("Nota da Prova 1: ");
        scanf("%f", &alunos[i].prova1);

        printf("Nota da Prova 2: ");
        scanf("%f", &alunos[i].prova2);

        printf("Frequência (em %%): ");
        scanf("%f", &alunos[i].frequencia);
    }

    // Leitura da fórmula para cálculo da média
    printf("\nDigite a fórmula para calcular a média (use P1, P2, F): ");
    scanf("%s", formula);

    // Converter a fórmula infixa para pós-fixa
    infixoParaPosfixo(formula, posfixa);
    printf("Fórmula em notação pós-fixa: %s\n", posfixa);

    // Cálculo da média para cada aluno usando a fórmula pós-fixa
    for (int i = 0; i < numAlunos; i++) {
        float media = avaliarPosfixo(posfixa, alunos[i]);
        printf("Média final do aluno %d: %.2f\n", i + 1, media);
    }

    return 0;
}