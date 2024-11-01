#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

// Estrutura do nó da árvore de Huffman
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// Estrutura de uma fila de prioridade (min-heap)
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Criação de um novo nó
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Criação de uma min-heap de capacidade especificada
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Funções auxiliares para manter a min-heap
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    minHeap->size++;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void generateCodes(struct MinHeapNode* root, int arr[], int top, char codes[][MAX_TREE_HT], char chars[]) {
    if (root->left) {
        arr[top] = 0;
        generateCodes(root->left, arr, top + 1, codes, chars);
    }

    if (root->right) {
        arr[top] = 1;
        generateCodes(root->right, arr, top + 1, codes, chars);
    }

    if (!root->left && !root->right) {
        chars[root->data] = 1;
        for (int i = 0; i < top; i++)
            codes[root->data][i] = arr[i] + '0';
        codes[root->data][top] = '\0';
    }
}

void compress(char* inputFile, char* outputFile) {
    FILE *input = fopen(inputFile, "r");
    if (!input) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return;
    }

    int freq[256] = {0};
    char ch;
    while ((ch = fgetc(input)) != EOF)
        freq[(unsigned char)ch]++;

    int size = 0;
    char data[256];
    int frequencies[256];
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            frequencies[size] = freq[i];
            size++;
        }
    }

    struct MinHeapNode* root = buildHuffmanTree(data, frequencies, size);
    char codes[256][MAX_TREE_HT] = {{0}};
    char chars[256] = {0};
    int arr[MAX_TREE_HT];
    generateCodes(root, arr, 0, codes, chars);

    rewind(input);
    FILE *output = fopen(outputFile, "wb");
    fwrite(freq, sizeof(freq), 1, output);

    int bitCount = 0;
    unsigned char byte = 0;
    while ((ch = fgetc(input)) != EOF) {
        char *code = codes[(unsigned char)ch];
        for (int i = 0; code[i] != '\0'; i++) {
            byte |= (code[i] - '0') << (7 - bitCount);
            bitCount++;
            if (bitCount == 8) {
                fputc(byte, output);
                bitCount = 0;
                byte = 0;
            }
        }
    }

    if (bitCount > 0)
        fputc(byte, output);

    fclose(input);
    fclose(output);
}

void decompress(char* inputFile, char* outputFile) {
    FILE *input = fopen(inputFile, "rb");
    if (!input) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return;
    }

    int freq[256];
    fread(freq, sizeof(freq), 1, input);

    int size = 0;
    char data[256];
    int frequencies[256];
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            data[size] = (char)i;
            frequencies[size] = freq[i];
            size++;
        }
    }

    struct MinHeapNode* root = buildHuffmanTree(data, frequencies, size);

    FILE *output = fopen(outputFile, "w");
    struct MinHeapNode* current = root;
    unsigned char byte;
    while (fread(&byte, 1, 1, input) > 0) {
        for (int i = 7; i >= 0; i--) {
            if ((byte & (1 << i)) == 0)
                current = current->left;
            else
                current = current->right;

            if (!current->left && !current->right) {
                fputc(current->data, output);
                current = root;
            }
        }
    }

    fclose(input);
    fclose(output);
}

int main() {
    char inputFile[] = "input.txt";
    char compressedFile[] = "compressed_output.bin";
    char decompressedFile[] = "decompressed_output.txt";

    printf("\nCompactando o arquivo...\n");
    compress(inputFile, compressedFile);

    printf("Descompactando o arquivo...\n");
    decompress(compressedFile, decompressedFile);

    printf("Processo concluido.\n");

    FILE *input = fopen("input.txt", "rb");
    FILE *output_comp = fopen("compressed_output.bin", "rb");
    FILE *output_decomp = fopen("decompressed_output.txt", "rb");

    if (!input || !output_comp || !output_decomp) {
        printf("Erro ao abrir o arquivos.\n");
        return 1;
    }

    fseek(input, 0, SEEK_END);
    long inputSize = ftell(input);
    fclose(input);

    fseek(output_comp, 0, SEEK_END);
    long outCompSize = ftell(output_comp);
    fclose(output_comp);

    fseek(output_decomp, 0, SEEK_END);
    long outDecompSize = ftell(output_decomp);
    fclose(output_decomp);

    printf("\nO tamanho do arquivo original era: %ld KB\n", (inputSize/1024));
    printf("\nO tamanho do arquivo comprimido: %ld KB\n", (outCompSize/1024));
    printf("\nO tamanho do arquivo descomprimido: %ld KB\n\n", (outDecompSize/1024));

    return 0;
}
