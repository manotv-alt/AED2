#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_HEIGHT 1000
#define MAX_NODES 100
#define CAPACITY 100

int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
int gap = 3;
int print_next = 0;

typedef struct asciinode {
    struct asciinode * esquerda, * direita;
    int edge_length;  // comprimento da aresta
    int height;       // altura do nó
    int lablen;       // comprimento do label
    int parent_dir;   // -1 = esquerda, 1 = direita, 0 = raiz
    char label[11];   // valor do nó convertido em string
} asciinode;

typedef struct Arvore {
    int valor;
    struct Arvore *esquerda;
    struct Arvore *direita;
} Arvore;

void print_level(asciinode *nodo, int x, int nivel) {
    int i, ehEsquerda;
    if (nodo == NULL) return;
    ehEsquerda = (nodo->parent_dir == -1);
    if (nivel == 0) {
        for (i = 0; i < (x - print_next - ((nodo->lablen - ehEsquerda) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", nodo->label);
        print_next += nodo->lablen;
    } else if (nodo->edge_length >= nivel) {
        if (nodo->esquerda != NULL) {
            for (i = 0; i < (x - print_next - nivel); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (nodo->direita != NULL) {
            for (i = 0; i < (x - print_next + nivel); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    } else {
        print_level(nodo->esquerda, x - nodo->edge_length - 1, nivel - nodo->edge_length - 1);
        print_level(nodo->direita, x + nodo->edge_length + 1, nivel - nodo->edge_length - 1);
    }
}

void compute_lprofile(asciinode *nodo, int x, int y) {
    int i, ehEsquerda;
    if (nodo == NULL) return;
    ehEsquerda = (nodo->parent_dir == -1);
    lprofile[y] = fmin(lprofile[y], x - ((nodo->lablen - ehEsquerda) / 2));
    if (nodo->esquerda != NULL) {
        for (i = 1; i <= nodo->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = fmin(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(nodo->esquerda, x - nodo->edge_length - 1, y + nodo->edge_length + 1);
    compute_lprofile(nodo->direita, x + nodo->edge_length + 1, y + nodo->edge_length + 1);
}

void compute_rprofile(asciinode *nodo, int x, int y) {
    int i, naoEhEsquerda;
    if (nodo == NULL) return;
    naoEhEsquerda = (nodo->parent_dir != -1);
    rprofile[y] = fmax(rprofile[y], x + ((nodo->lablen - naoEhEsquerda) / 2));
    if (nodo->direita != NULL) {
        for (i = 1; i <= nodo->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = fmax(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(nodo->esquerda, x - nodo->edge_length - 1, y + nodo->edge_length + 1);
    compute_rprofile(nodo->direita, x + nodo->edge_length + 1, y + nodo->edge_length + 1);
}

void compute_edge_lengths(asciinode *nodo) {
    int h, hmin, i, delta;
    if (nodo == NULL) return;
    compute_edge_lengths(nodo->esquerda);
    compute_edge_lengths(nodo->direita);

    if (nodo->direita == NULL && nodo->esquerda == NULL) {
        nodo->edge_length = 0;
    } else {
        if (nodo->esquerda != NULL) {
            for (i = 0; i < nodo->esquerda->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -(1<<20);
            }
            compute_rprofile(nodo->esquerda, 0, 0);
            hmin = nodo->esquerda->height;
        } else {
            hmin = 0;
        }
        if (nodo->direita != NULL) {
            for (i = 0; i < nodo->direita->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = (1<<20);
            }
            compute_lprofile(nodo->direita, 0, 0);
            hmin = fmin(nodo->direita->height, hmin);
        } else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = fmax(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        if (((nodo->esquerda != NULL && nodo->esquerda->height == 1) ||
             (nodo->direita != NULL && nodo->direita->height == 1)) && delta > 4) {
            delta--;
        }

        nodo->edge_length = ((delta + 1) / 2) - 1;
    }

    h = 1;
    if (nodo->esquerda != NULL) {
        h = fmax(nodo->esquerda->height + nodo->edge_length + 1, h);
    }
    if (nodo->direita != NULL) {
        h = fmax(nodo->direita->height + nodo->edge_length + 1, h);
    }
    nodo->height = h;
}

asciinode * build_ascii_tree_recursive(Arvore * t) {
    asciinode * nodo;

    if (t == NULL) return NULL;

    nodo = malloc(sizeof(asciinode));
    nodo->esquerda = build_ascii_tree_recursive(t->esquerda);
    nodo->direita = build_ascii_tree_recursive(t->direita);

    if (nodo->esquerda != NULL) {
        nodo->esquerda->parent_dir = -1;
    }

    if (nodo->direita != NULL) {
        nodo->direita->parent_dir = 1;
    }

    sprintf(nodo->label, "%d", t->valor);
    nodo->lablen = strlen(nodo->label);

    return nodo;
}

asciinode * build_ascii_tree(Arvore * t) {
    asciinode *nodo;
    if (t == NULL) return NULL;
    nodo = build_ascii_tree_recursive(t);
    nodo->parent_dir = 0;
    return nodo;
}

void free_ascii_tree(asciinode *nodo) {
    if (nodo == NULL) return;
    free_ascii_tree(nodo->esquerda);
    free_ascii_tree(nodo->direita);
    free(nodo);
}

void liberarArvore(Arvore* raiz) {
    if (raiz == NULL) {
        return;  // Passo base: Se o nó for NULL, retorna
    }

    // Libera os nós filhos
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);

    // Libera o nó atual
    free(raiz);
}

// Função para criar um novo nó da árvore
Arvore* criarNo(int valor) {
    Arvore* novoNo = (Arvore*)malloc(sizeof(Arvore));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para construir a árvore binária a partir de um array representando um heap
Arvore* construirArvoreHeap(int *heap, int index, int tamanho) {
    if (index >= tamanho || heap[index] == -1) {
        return NULL;
    }

    Arvore* raiz = criarNo(heap[index]);
    raiz->esquerda = construirArvoreHeap(heap, 2 * index + 1, tamanho); // Filho esquerdo
    raiz->direita = construirArvoreHeap(heap, 2 * index + 2, tamanho);  // Filho direito

    return raiz;
}

typedef struct {
    int data[CAPACITY];
    int size;
} MaxHeap;

// Função auxiliar para trocar dois elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para retornar o indice do pai de um no
int parent(int i) {
    return (i - 1) / 2;
}

// Função para retornar o indice do filho esquerdo
int leftChild(int i) {
    return 2 * i + 1;
}

// Função para retornar o indice do filho direito
int rightChild(int i) {
    return 2 * i + 2;
}

// Função para ajustar o heap para cima ao inserir um novo elemento
void heapifyUp(MaxHeap *heap, int i) {
    while (i > 0 && heap->data[parent(i)] < heap->data[i]) {
        swap(&heap->data[parent(i)], &heap->data[i]);
        i = parent(i);
    }
}

// Função para ajustar o heap para baixo ao remover o elemento maximo
void heapifyDown(MaxHeap *heap, int i) {
    int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        heapifyDown(heap, largest);
    }
}

// Função para inserir um elemento no heap
void insert(MaxHeap *heap, int value) {
    if (heap->size == CAPACITY) {
        printf("Heap esta cheio!\n");
        return;
    }

    heap->data[heap->size] = value;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

// Função para remover o elemento do heap
int removeElement(MaxHeap *heap, int valor) {
    if (heap->size == 0) {
        printf("Heap está vazio!\n");
        return -1;
    }

    // Encontrar o índice do valor a ser removido
    int index = -1;
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] == valor) {
            index = i;
            break;
        }
    }

    // Se o valor não for encontrado, retornar erro
    if (index == -1) {
        printf("Valor %d não encontrado no heap!\n", valor);
        return -1;
    }

    // Salvar o valor do nó para retornar após a remoção
    int elementoRemovido = heap->data[index];

    // Substituir o elemento a ser removido pelo último elemento do heap
    heap->data[index] = heap->data[heap->size - 1];
    heap->size--;

    // Reorganizar o heap a partir do índice onde ocorreu a remoção
    heapifyDown(heap, index);

    return elementoRemovido;
}

// Função para consultar um elemento no heap
void searchElement(MaxHeap *heap, int value) {
    int found = -1;
    for (int i = 0; i < heap->size; i++) {
        if (heap->data[i] == value) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Elemento %d nao encontrado no heap.\n", value);
    } else {
        printf("Elemento %d encontrado no indice %d.\n", value, found);

        int parentIdx = parent(found);
        int leftIdx = leftChild(found);
        int rightIdx = rightChild(found);

        // Exibe o nó pai
        if (found > 0) {
            printf("Pai: %d\n", heap->data[parentIdx]);
        } else {
            printf("Nao possui pai (e a raiz).\n");
        }

        // Exibe o nó filho esquerdo
        if (leftIdx < heap->size) {
            printf("Filho esquerdo: %d\n", heap->data[leftIdx]);
        } else {
            printf("Nao possui filho esquerdo.\n");
        }

        // Exibe o nó filho direito
        if (rightIdx < heap->size) {
            printf("Filho direito: %d\n", heap->data[rightIdx]);
        } else {
            printf("Nao possui filho direito.\n");
        }
    }
}

// Função para imprimir a árvore em ordem de nível
void imprimirArvore(int * heap, int tamanho) {
    Arvore* root = construirArvoreHeap(heap, 0, tamanho);
    asciinode* proot = build_ascii_tree(root);
    int i, xmin, max_level;
    if (proot == NULL) return;
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = (1<<20);
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = fmin(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(Tree is taller than %d, will be truncated)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
    liberarArvore(root);
}

// Função principal do menu
void menu() {
    printf("\n================================\n");
    printf("   Gerenciador de Heap Maximo");
    printf("\n================================\n");
    printf("1. Inserir um elemento\n");
    printf("2. Remover um elemento\n");
    printf("3. Consultar elemento\n");
    printf("0. Sair");
    printf("\n================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    MaxHeap heap;
    heap.size = 0;

    int opcao, valor, value;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um valor para inserir: ");
                scanf("%d", &valor);
                insert(&heap, valor);
                imprimirArvore(heap.data, heap.size);
                break;
            case 2:
                printf("Digite um valor para remover: ");
                scanf("%d", &value);
                valor = removeElement(&heap, value);
                if (valor != -1) {
                    printf("Valor removido: %d\n", valor);
                    imprimirArvore(heap.data, heap.size);
                }
                break;
            case 3:
                printf("Digite um valor para consultar: ");
                scanf("%d", &valor);
                printf("\n");
                searchElement(&heap, valor);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
