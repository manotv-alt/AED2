#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;

// Prototipação das funções
void compactar();
void descompactar();
void embedData(Mat *image, const char *filePath);
void extractData(Mat *image, const char *outputPath);

int main() {
    int escolha;

    while (1) {
        printf("\n===== Compactador/Descompactador =====\n");
        printf("1. Compactar arquivo em imagem\n");
        printf("2. Descompactar arquivo de imagem\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                compactar();
                break;
            case 2:
                descompactar();
                break;
            case 3:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}

void compactar() {
    char caminhoImagem[256], caminhoArquivo[256], caminhoSaida[256];
    printf("\n=== Compactar Arquivo em Imagem ===\n");
    printf("Caminho da imagem (entrada): ");
    scanf("%s", caminhoImagem);
    printf("Caminho do arquivo a ser compactado: ");
    scanf("%s", caminhoArquivo);
    printf("Caminho da imagem de saída: ");
    scanf("%s", caminhoSaida);

    Mat image = imread(caminhoImagem, IMREAD_COLOR);
    if (image.empty()) {
        printf("Erro ao carregar a imagem.\n");
        return;
    }

    embedData(&image, caminhoArquivo);
    imwrite(caminhoSaida, image);
    printf("Imagem compactada salva em '%s'.\n", caminhoSaida);
}

void descompactar() {
    char caminhoImagem[256], caminhoArquivoSaida[256];
    printf("\n=== Descompactar Arquivo de Imagem ===\n");
    printf("Caminho da imagem compactada: ");
    scanf("%s", caminhoImagem);
    printf("Caminho do arquivo de saída: ");
    scanf("%s", caminhoArquivoSaida);

    Mat image = imread(caminhoImagem, IMREAD_COLOR);
    if (image.empty()) {
        printf("Erro ao carregar a imagem.\n");
        return;
    }

    extractData(&image, caminhoArquivoSaida);
    printf("Arquivo extraído e salvo em '%s'.\n", caminhoArquivoSaida);
}

void embedData(Mat *image, const char *filePath) {
    FILE *file = fopen(filePath, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    unsigned char *data = (unsigned char *)malloc(fileSize);
    fread(data, 1, fileSize, file);
    fclose(file);

    int rows = image->rows;
    int cols = image->cols * image->channels();

    if (fileSize * 8 > rows * cols) {
        printf("Arquivo muito grande para a imagem fornecida.\n");
        free(data);
        return;
    }

    int dataIdx = 0, bitIdx = 0;
    for (int i = 0; i < rows && dataIdx < fileSize; i++) {
        for (int j = 0; j < cols; j++) {
            unsigned char *pixel = &image->data[i * cols + j];
            *pixel = (*pixel & ~1) | ((data[dataIdx] >> (7 - bitIdx)) & 1);
            if (++bitIdx == 8) {
                bitIdx = 0;
                dataIdx++;
            }
        }
    }

    free(data);
}

void extractData(Mat *image, const char *outputPath) {
    FILE *file = fopen(outputPath, "wb");
    if (!file) {
        printf("Erro ao criar o arquivo de saída.\n");
        return;
    }

    int rows = image->rows;
    int cols = image->cols * image->channels();

    unsigned char byte = 0;
    int bitIdx = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            unsigned char pixel = image->data[i * cols + j];
            byte = (byte << 1) | (pixel & 1);

            if (++bitIdx == 8) {
                fwrite(&byte, 1, 1, file);
                bitIdx = 0;
                byte = 0;
            }
        }
    }

    fclose(file);
}
