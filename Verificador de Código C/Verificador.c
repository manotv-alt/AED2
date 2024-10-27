#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE 1024

// Estrutura do nó da Árvore Rubro-Negra
typedef enum { RED, BLACK } Color;

typedef struct Node {
    char *key;
    struct Node *left, *right, *parent;
    Color color;
} Node;

typedef struct {
    Node *root;
    Node *nil;  // Sentinela para folhas nulas
} RedBlackTree;

// Estrutura da Pilha para verificar símbolos balanceados
typedef struct {
    char elementos[MAX_LINE];
    int topo;
} Pilha;

// Funções da Árvore Rubro-Negra
RedBlackTree* criarArvore();
Node* criarNo(RedBlackTree *tree, char *key);
void inserir(RedBlackTree *tree, char *key);
void balancearInsercao(RedBlackTree *tree, Node *z);
Node* buscar(RedBlackTree *tree, Node *x, const char *key);

// Funções para pilha
void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
void empilhar(Pilha *p, char c);
int desempilhar(Pilha *p, char *c);

// Funções de verificação
int verificarLinha(const char *linha, RedBlackTree *tree, Pilha *pilha);
int validarRegex(const char *linha, const char *padrao);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo.c>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Inicializa árvore e pilha
    RedBlackTree *tree = criarArvore();
    Pilha pilha;
    inicializarPilha(&pilha);

    // Insere tokens válidos na árvore
    inserir(tree, "int");
    inserir(tree, "main");
    inserir(tree, "if");
    inserir(tree, "else");
    inserir(tree, "for");
    inserir(tree, "while");
    inserir(tree, "printf");
    inserir(tree, "scanf");

    char linha[MAX_LINE];
    int erro = 0;

    // Lê o arquivo linha a linha
    while (fgets(linha, MAX_LINE, arquivo) != NULL) {
        if (!verificarLinha(linha, tree, &pilha)) {
            erro++;
        }
    }

    if (!pilhaVazia(&pilha)) {
        printf("Erro: Símbolos não balanceados.\n");
        erro++;
    }

    fclose(arquivo);

    if (erro == 0) {
        printf("Nenhum erro encontrado.\n");
    }

    return 0;
}

// Funções da Árvore Rubro-Negra

RedBlackTree* criarArvore() {
    RedBlackTree *tree = malloc(sizeof(RedBlackTree));
    tree->nil = malloc(sizeof(Node));
    tree->nil->color = BLACK;
    tree->root = tree->nil;
    return tree;
}

Node* criarNo(RedBlackTree *tree, char *key) {
    Node *node = malloc(sizeof(Node));
    node->key = strdup(key);
    node->left = node->right = node->parent = tree->nil;
    node->color = RED;
    return node;
}

void inserir(RedBlackTree *tree, char *key) {
    Node *z = criarNo(tree, key);
    Node *y = tree->nil;
    Node *x = tree->root;

    while (x != tree->nil) {
        y = x;
        if (strcmp(z->key, x->key) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == tree->nil) {
        tree->root = z;
    } else if (strcmp(z->key, y->key) < 0) {
        y->left = z;
    } else {
        y->right = z;
    }

    balancearInsercao(tree, z);
}

void balancearInsercao(RedBlackTree *tree, Node *z) {
    // Implementação simplificada para manter a árvore balanceada.
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    // Rotação à esquerda
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                // Rotação à direita
            }
        } else {
            // Caso simétrico
        }
    }
    tree->root->color = BLACK;
}

Node* buscar(RedBlackTree *tree, Node *x, const char *key) {
    if (x == tree->nil || strcmp(key, x->key) == 0) {
        return x;
    }
    if (strcmp(key, x->key) < 0) {
        return buscar(tree, x->left, key);
    } else {
        return buscar(tree, x->right, key);
    }
}

// Funções da Pilha

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, char c) {
    p->elementos[++p->topo] = c;
}

int desempilhar(Pilha *p, char *c) {
    if (!pilhaVazia(p)) {
        *c = p->elementos[p->topo--];
        return 1;
    }
    return 0;
}

// Verificação de linha usando regex e árvore

int verificarLinha(const char *linha, RedBlackTree *tree, Pilha *pilha) {
    if (validarRegex(linha, "printf\\(.*\\);") || validarRegex(linha, "scanf\\(.*\\);")) {
        return 1;
    }
    if (strstr(linha, "{")) {
        empilhar(pilha, '{');
    }
    if (strstr(linha, "}")) {
        char c;
        if (!desempilhar(pilha, &c)) {
            printf("Erro: Símbolo '}' sem correspondente.\n");
            return 0;
        }
    }
    return 1;
}

int validarRegex(const char *linha, const char *padrao) {
    regex_t regex;
    regcomp(&regex, padrao, REG_EXTENDED);
    int status = regexec(&regex, linha, 0, NULL, 0);
    regfree(&regex);
    return status == 0;
}