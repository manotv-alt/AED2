#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000
#define MAX_KEY_LENGTH 100 // Tamanho máximo para as chaves

// Estrutura para a lista encadeada (nó para colisões)
typedef struct Node {
    char key[MAX_KEY_LENGTH];
    struct Node* next;
} Node;

// Tabela Hash principal
Node* hashTable[TABLE_SIZE] = {NULL};

// Função Hash (gerar índice a partir de uma string)
int hashFunction(const char* key) {
    unsigned long hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31 + key[i]) % TABLE_SIZE;
    }
    return hash;
}

// Insere uma chave na tabela hash
void insertKey(const char* key) {
    int index = hashFunction(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        // Insere na lista encadeada em caso de colisão
        Node* current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Busca uma chave na tabela e conta os passos
int searchKey(const char* key) {
    int index = hashFunction(key);
    Node* current = hashTable[index];
    int steps = 0;

    while (current != NULL) {
        steps++;
        if (strcmp(current->key, key) == 0) {
            return steps;
        }
        current = current->next;
    }
    return -1; // Chave nao encontrada
}

// Relatório final
void printReport() {
    int occupied = 0, empty = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            occupied++;
        } else {
            empty++;
        }
    }

    printf("Espacos ocupados na tabela principal: %d\n", occupied);
    printf("Espacos vazios na tabela principal: %d\n", empty);
}

void menu() {
    int option;
    char key[MAX_KEY_LENGTH];

    do {
        printf("\n================================\n");
        printf("        Gerenciador Hash         ");
        printf("\n================================\n");
        printf("1. Inserir chave\n");
        printf("2. Buscar chave\n");
        printf("3. Mostrar relatorio\n");
        printf("4. Sair");
        printf("\n================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                printf("Digite a chave a ser inserida: ");
                fgets(key, MAX_KEY_LENGTH, stdin);
                key[strcspn(key, "\n")] = '\0'; // Remover o caractere de nova linha
                insertKey(key);
                printf("\nChave %s inserida com sucesso\n", key);
                break;

            case 2:
                printf("Digite a chave a ser buscada: ");
                fgets(key, MAX_KEY_LENGTH, stdin);
                key[strcspn(key, "\n")] = '\0'; // Remover o caractere de nova linha
                int steps = searchKey(key);
                if (steps != -1) {
                    printf("\nChave encontrada em %d passos\n", steps);
                } else {
                    printf("\nChave nao encontrada\n");
                }
                break;

            case 3:
                printReport();
                break;

            case 4:
                printf("Encerrando o programa\n");
                break;

            default:
                printf("Opcao invalida, tente novamente\n");
        }
    } while (option != 4);
}

int main() {
    menu();
    return 0;
}