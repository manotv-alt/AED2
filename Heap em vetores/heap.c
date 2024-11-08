#include <stdio.h>
#include <math.h>

#define CAPACITY 100 // Capacidade maxima do heap

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

// Função para remover o elemento maximo (raiz) do heap
int removeMax(MaxHeap *heap) {
    if (heap->size == 0) {
        printf("Heap esta vazio!\n");
        return -1;
    }

    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return max;
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

// Função para imprimir o heap em formato de arvore com alinhamento melhorado
void printTree(MaxHeap *heap) {
    printf("\n--- Diagrama do Heap ---\n");

    int level = 0;
    int count = 0;
    int nodesInLevel = 1;

    while (count < heap->size) {
        int maxSpacing = (int)pow(2, log2(heap->size) - level + 1) - 1;
        int edgeSpacing = (int)pow(2, log2(heap->size) - level);

        // Imprime a linha de conectores entre os nós
        if (level > 0) {
            for (int i = 0; i < nodesInLevel; i++) {
                printf("%*s", edgeSpacing - 1, ""); // Alinhamento antes do conector

                if (i % 2 == 0) {
                    printf("/"); // Conector esquerdo
                } else {
                    printf("\\"); // Conector direito
                }

                printf("%*s", edgeSpacing - 1, ""); // Alinhamento após o conector
            }
            printf("\n");
        }

        // Imprime o nivel atual de nós
        for (int i = 0; i < nodesInLevel && count < heap->size; i++) {
            printf("%*d%*s", maxSpacing, heap->data[count++], maxSpacing, "");
        }
        printf("\n");

        // Próximo nível
        level++;
        nodesInLevel *= 2;
    }
}

// Função principal do menu
void menu() {
    printf("\n=== Gerenciador de Heap Maximo ===\n");
    printf("1. Inserir um elemento\n");
    printf("2. Remover o maximo\n");
    printf("3. Consultar elemento\n");
    printf("0. Sair\n");
    printf("==============================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    MaxHeap heap;
    heap.size = 0;

    int opcao, valor;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite um valor para inserir: ");
                scanf("%d", &valor);
                insert(&heap, valor);
                printTree(&heap);
                break;
            case 2:
                valor = removeMax(&heap);
                if (valor != -1) {
                    printf("Valor removido: %d\n", valor);
                    printTree(&heap);
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
