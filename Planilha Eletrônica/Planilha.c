#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROWS 10  // número de linhas
#define COLS 10  // número de colunas
#define MAX_FORMULA_LEN 100
#define STACK_SIZE 100

// Estrutura para representar uma célula
typedef struct {
    char formula[MAX_FORMULA_LEN];  // fórmula ou valor inserido
    int is_formula;  // indica se é uma fórmula (1) ou um valor simples (0)
    double value;    // valor calculado
} Cell;

// Planilha com células
Cell sheet[ROWS][COLS];

// Função para converter uma referência de célula (como "A1") para coordenadas de índice
int parse_cell_ref(char* ref, int* row, int* col) {
    if (strlen(ref) < 2) return 0;
    *col = toupper(ref[0]) - 'A';  // Coluna A=0, B=1, etc.
    *row = atoi(&ref[1]) - 1;      // Linha 1=0, 2=1, etc.
    return (*col >= 0 && *col < COLS && *row >= 0 && *row < ROWS);
}

// Função para verificar se a string dada é um número
int is_number(char* token) {
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i]) && token[i] != '.') return 0;
    }
    return 1;
}

// Função para determinar a precedência dos operadores
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Função para converter uma expressão infixa (normal) para NPR (Notação Polonesa Reversa)
void infix_to_rpn(const char* infix, char* rpn) {
    char stack[STACK_SIZE];
    int top = -1;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isalnum(token)) {  // Se for operando (número ou referência de célula)
            rpn[j++] = token;
            while (isalnum(infix[i + 1])) {
                rpn[j++] = infix[++i];  // Captura o resto da célula
            }
            rpn[j++] = ' ';  // Adiciona um espaço após o operando
        } else if (token == '(') {
            stack[++top] = token;  // Empilha parêntese esquerdo
        } else if (token == ')') {
            // Desempilha até encontrar o parêntese esquerdo correspondente
            while (top != -1 && stack[top] != '(') {
                rpn[j++] = stack[top--];
                rpn[j++] = ' ';
            }
            top--;  // Remove o '(' da pilha
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            // Enquanto o topo da pilha tiver um operador de maior ou igual precedência
            while (top != -1 && precedence(stack[top]) >= precedence(token)) {
                rpn[j++] = stack[top--];
                rpn[j++] = ' ';
            }
            stack[++top] = token;  // Empilha o operador atual
        }
    }

    // Desempilha os operadores restantes
    while (top != -1) {
        rpn[j++] = stack[top--];
        rpn[j++] = ' ';
    }

    rpn[j - 1] = '\0';  // Remove o último espaço e finaliza a string
}

// Função para avaliar uma fórmula NPR (Notação Polonesa Reversa)
double evaluate_rpn(const char* formula) {
    double stack[STACK_SIZE];
    int top = -1;
    char temp_formula[MAX_FORMULA_LEN];
    strcpy(temp_formula, formula);  // Faz uma cópia da fórmula original para ser tokenizada

    char* token = strtok(temp_formula, " ");

    while (token != NULL) {
        if (is_number(token)) {
            // Se for número, empilha
            stack[++top] = atof(token);
        } else if (isalpha(token[0])) {
            // Se for referência de célula (como "A1"), empilha o valor da célula
            int row, col;
            if (parse_cell_ref(token, &row, &col)) {
                stack[++top] = sheet[row][col].value;
            }
        } else {
            // Se for operador, desempilha dois valores e aplica a operação
            if (top < 1) return 0;  // Operação inválida se não houver dois operandos

            double b = stack[top--];
            double a = stack[top--];
            double result;

            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = (b != 0) ? a / b : 0; break;  // Evitar divisão por zero
                default: return 0;  // Operador inválido
            }

            stack[++top] = result;
        }

        token = strtok(NULL, " ");
    }

    // O valor final será o único valor restante na pilha
    return (top == 0) ? stack[top] : 0;
}

// Função para calcular os valores de todas as células da planilha
void calculate_sheet() {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (sheet[r][c].is_formula) {
                // Avalia a fórmula NPR para calcular o valor da célula
                sheet[r][c].value = evaluate_rpn(sheet[r][c].formula);
            }
        }
    }
}

// Função para inserir uma fórmula ou valor em uma célula
void set_cell_value(int row, int col, char* input) {
    if (strpbrk(input, "+-*/")) {  // Verifica se a fórmula contém operadores
        char rpn[MAX_FORMULA_LEN];
        infix_to_rpn(input, rpn);  // Converte a expressão infixa para NPR
        strcpy(sheet[row][col].formula, rpn);
        sheet[row][col].is_formula = 1;
    } else {
        sheet[row][col].value = atof(input);
        sheet[row][col].is_formula = 0;
    }
}

// Função para exibir a planilha
void display_sheet() {
    printf("\n   ");
    for (int c = 0; c < COLS; c++) {
        printf("   %c  ", 'A' + c);
    }
    printf("\n");

    for (int r = 0; r < ROWS; r++) {
        printf("%2d ", r + 1);
        for (int c = 0; c < COLS; c++) {
            if (sheet[r][c].is_formula) {
                // Exibe o valor calculado da fórmula
                printf("[%.2f]", sheet[r][c].value);
            } else {
                printf("[%.2f]", sheet[r][c].value);
            }
        }
        printf("\n");
    }
}


int main() {
    char input[MAX_FORMULA_LEN];
    char cell_ref[3];
    int row, col;

    // Exibe a planilha vazia no início
    display_sheet();

    // Loop para aceitar entradas do usuário
    while (1) {
        printf("\nDigite a célula (ex: A1) e o valor/fórmula (ou 'exit' para sair): ");
        scanf("%2s", cell_ref);

        if (strcmp(cell_ref, "exit") == 0) {
            break;
        }

        if (!parse_cell_ref(cell_ref, &row, &col)) {
            printf("Referência de célula inválida!\n");
            continue;
        }

        printf("Digite o valor ou fórmula operações suportadas (+,-,/,*) no formato: A1 + B1 para %s: ", cell_ref);
        scanf(" %[^\n]", input);

        set_cell_value(row, col, input);
        calculate_sheet();  // Calcula o valor após inserir a fórmula ou valor
        display_sheet();    // Exibe a planilha atualizada
    }

    return 0;
}
