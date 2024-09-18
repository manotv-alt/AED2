#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libbmp.h"

void hide_message(BMP *image, const char *message) {
    size_t msg_len = strlen(message);
    size_t total_pixels = image->width * image->height;

    if (msg_len * 8 > total_pixels) {
        fprintf(stderr, "Mensagem muito longa para a imagem!\n");
        return;
    }

    for (size_t i = 0; i < msg_len; i++) {
        for (int j = 0; j < 8; j++) {
            // Obtém o pixel na posição i * 8 + j
            size_t pixel_index = i * 8 + j;
            RGB pixel = image->pixels[pixel_index];

            // Modifica o LSB do componente vermelho para esconder o bit da mensagem
            pixel.red = (pixel.red & ~1) | ((message[i] >> (7 - j)) & 1);
            image->pixels[pixel_index] = pixel;
        }
    }

    // Adiciona o caractere nulo para indicar o fim da mensagem
    for (int j = 0; j < 8; j++) {
        size_t pixel_index = msg_len * 8 + j;
        RGB pixel = image->pixels[pixel_index];
        pixel.red = (pixel.red & ~1) | ((0 >> (7 - j)) & 1);
        image->pixels[pixel_index] = pixel;
    }
}

void reveal_message(BMP *image, char *message, size_t message_size) {
    for (size_t i = 0; i < message_size; i++) {
        message[i] = 0;
        for (int j = 0; j < 8; j++) {
            size_t pixel_index = i * 8 + j;
            RGB pixel = image->pixels[pixel_index];
            message[i] |= ((pixel.red & 1) << (7 - j));
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <imagem.bmp> <mensagem> <imagem_saida.bmp>\n", argv[0]);
        return 1;
    }

    const char *input_image = argv[1];
    const char *message = argv[2];
    const char *output_image = argv[3];

    BMP *bmp_image = bmp_create(input_image);
    if (!bmp_image) {
        fprintf(stderr, "Erro ao abrir a imagem.\n");
        return 1;
    }

    hide_message(bmp_image, message);
    bmp_save(bmp_image, output_image);
    bmp_destroy(bmp_image);

    printf("Mensagem escondida com sucesso!\n");

    // Para revelar a mensagem
    bmp_image = bmp_create(output_image);
    if (!bmp_image) {
        fprintf(stderr, "Erro ao abrir a imagem de saída.\n");
        return 1;
    }

    char revealed_message[256] = {0};
    reveal_message(bmp_image, revealed_message, sizeof(revealed_message) - 1);
    bmp_destroy(bmp_image);

    printf("Mensagem revelada: %s\n", revealed_message);

    return 0;
}
