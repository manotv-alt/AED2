#include <stdio.h>
#include <stdlib.h>

// Estrutura para o no da arvore
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Funcao para criar um novo no
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Funcao para inserir um valor na arvore
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// Funcao para buscar um valor na arvore, contar os passos e exibir o caminho
int search(struct Node* root, int key, int* steps) {
    struct Node* current = root;
    *steps = 0;

    printf("Caminho percorrido: ");
    while (current != NULL) {
        (*steps)++;

        // Exibe o valor atual e a direcao que esta seguindo
        if (key == current->data) {
            printf("(%d) <- Encontrado\n", current->data);
            return 1; // Encontrado
        } else if (key < current->data) {
            printf("(%d) -> Esq ", current->data);
            current = current->left;
        } else {
            printf("(%d) -> Dir ", current->data);
            current = current->right;
        }
    }
    printf("Valor nao encontrado.\n");
    return 0; // Nao encontrado
}

// Funcao para exibir um cabecalho
void exibirCabecalho() {
    printf("=====================================\n");
    printf("       Arvore Binaria de Busca       \n");
    printf("=====================================\n");
}

// Funcao para exibir o menu de opcoes
void exibirMenu() {
    printf("\nOpcoes:\n");
    printf("1 - Inserir valores na arvore\n");
    printf("2 - Buscar um valor na arvore\n");
    printf("3 - Sair do programa\n");
    printf("Escolha uma opcao: ");
}

// Funcao principal
int main() {
    struct Node* root = NULL;
    int value, searchValue, steps, opcao;

    exibirCabecalho();

    // Insercao inicial de valores
    printf("Digite valores para inserir na arvore (digite -1 para parar):\n");
    while (1) {
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        root = insert(root, value);
    }

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: 
                printf("\nInsira um valor para adicionar (digite -1 para voltar): ");
                while (1) {
                    scanf("%d", &value);
                    if (value == -1) {
                        break;
                    }
                    root = insert(root, value);
                    printf("Valor %d inserido na arvore.\n", value);
                }
                break;
            case 2:
                printf("\nDigite o valor que deseja buscar (digite -1 para voltar): ");
                scanf("%d", &searchValue);

                if (searchValue == -1) {
                    break;
                }

                printf("\n");
                if (search(root, searchValue, &steps)) {
                    printf("Valor %d encontrado em %d passos.\n\n", searchValue, steps);
                } else {
                    printf("Valor %d nao encontrado na arvore.\n\n", searchValue);
                }
                break;
            case 3:
                printf("Encerrando o programa.\n");
                return 0;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}
