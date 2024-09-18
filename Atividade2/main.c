#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

void hide_message(png_bytep *row_pointers, int width, int height, const char *message) {
    int bit_index = 0;
    int msg_len = strlen(message);

    // Adiciona um marcador de fim à mensagem (um caractere nulo \0)
    char *full_message = malloc(msg_len + 1);
    strcpy(full_message, message);
    full_message[msg_len] = '\0';

    int full_len = strlen(full_message);

    for (int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);

            for (int i = 0; i < 3; i++) {  // Itera sobre R, G, B (ignora A)
                if (bit_index / 8 < full_len) {
                    int bit = (full_message[bit_index / 8] >> (7 - bit_index % 8)) & 1;
                    px[i] = (px[i] & 0xFE) | bit;
                    bit_index++;
                }
            }
        }
    }

    free(full_message);
}

void write_png_file(const char *filename, png_bytep *row_pointers, int width, int height, png_structp png, png_infop info) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) abort();

    png_init_io(png, fp);

    // Write header
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    // Write bytes
    png_write_image(png, row_pointers);

    // End write
    png_write_end(png, NULL);

    fclose(fp);
}

void read_png_file(const char *filename, png_bytep **row_pointers, int *width, int *height, png_structp *png, png_infop *info) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) abort();

    *png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!*png) abort();

    *info = png_create_info_struct(*png);
    if (!*info) abort();

    if (setjmp(png_jmpbuf(*png))) abort();

    png_init_io(*png, fp);
    png_read_info(*png, *info);

    *width = png_get_image_width(*png, *info);
    *height = png_get_image_height(*png, *info);
    png_byte color_type = png_get_color_type(*png, *info);
    png_byte bit_depth = png_get_bit_depth(*png, *info);

    // Read any color_type into 8bit depth, RGBA format.
    if (bit_depth == 16) png_set_strip_16(*png);

    if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(*png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand_gray_1_2_4_to_8(*png);

    if (png_get_valid(*png, *info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(*png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(*png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(*png);

    png_read_update_info(*png, *info);

    *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * (*height));
    for (int y = 0; y < *height; y++) {
        (*row_pointers)[y] = (png_byte *)malloc(png_get_rowbytes(*png, *info));
    }

    png_read_image(*png, *row_pointers);

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <imagem_entrada.png> <imagem_saida.png> <mensagem>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    const char *message = argv[3];

    png_structp png;
    png_infop info;
    png_bytep *row_pointers;
    int width, height;

    read_png_file(input_file, &row_pointers, &width, &height, &png, &info);
    hide_message(row_pointers, width, height, message);
    write_png_file(output_file, row_pointers, width, height, png, info);

    // Liberar memória
    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);

    png_destroy_read_struct(&png, &info, NULL);

    printf("Mensagem escondida com sucesso em %s!\n", output_file);

    return 0;
}
