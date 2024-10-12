#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100  // Tamanho máximo da pilha

typedef struct {
    double data[MAX];
    int top;
} Stack;

// Funções da pilha
void initStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, double value) {
    if (isFull(s)) {
        printf("Erro: Pilha cheia\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = value;
}

double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
    return s->data[(s->top)--];
}

double top(Stack *s) {
    if (isEmpty(s)) {
        printf("Erro: Pilha vazia\n");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top];
}

// Função para verificar se um caractere é um operador
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Função para realizar uma operação entre dois operandos
double performOperation(char operator, double operand1, double operand2) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': 
            if (operand2 == 0) {
                printf("Erro: Divisão por zero\n");
                exit(EXIT_FAILURE);
            }
            return operand1 / operand2;
        default:
            printf("Erro: Operador inválido\n");
            exit(EXIT_FAILURE);
    }
}

// Função para avaliar uma expressão pós-fixada
double evaluatePostfix(const char *expression) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        // Ignora espaços em branco
        if (expression[i] == ' ') continue;

        // Se for um número, empilha
        if (isdigit(expression[i])) {
            double num = 0;

            // Converte sequência de dígitos em um número
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Corrige o incremento extra do loop
            push(&stack, num);
        } 
        // Se for um operador, realiza a operação
        else if (isOperator(expression[i])) {
            double operand2 = pop(&stack);
            double operand1 = pop(&stack);
            double result = performOperation(expression[i], operand1, operand2);
            push(&stack, result);
        } else {
            printf("Erro: Caractere inválido na expressão: %c\n", expression[i]);
            exit(EXIT_FAILURE);
        }
    }

    // O resultado final deve estar no topo da pilha
    if (stack.top != 0) {
        printf("Erro: Expressão inválida\n");
        exit(EXIT_FAILURE);
    }
    return pop(&stack);
}

void printBanner() {
    printf("========================================\n");
    printf("      🧮 CALCULADORA PÓS-FIXADA 🧮     \n");
    printf("========================================\n");
    printf("  Digite uma expressão em notação RPN:  \n");
    printf("  Exemplos: 10 5 + 2 *   ou   3 4 + 7 - \n");
    printf("        Ou digite 'exit' para sair      \n");
    printf("----------------------------------------\n");
}

void printResult(double result) {
    printf("----------------------------------------\n");
    printf("📊 Resultado: %.2lf\n", result);
    printf("========================================\n");
}

int main() {
    char expression[100];

    while(1) {
        printBanner();

        printf("➤ ");
        fgets(expression, sizeof(expression), stdin);
        expression[strcspn(expression, "\n")] = '\0';  // Remove o '\n'

        if(expression == "exit") break;

        double result = evaluatePostfix(expression);
        printResult(result);
    }
    
    return 0;
}