#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"
#include <png.h>


/**
 * @brief This function will load an image in png format and record its main information, including height and width and the reference to the image itself
 *
 * @param char_const *path to image
 * @param png_bytep reference to image
 * @param int *reference to variable that will store the whidth
 * @param int *reference to variable that will store the height

 * @return void
 */
void LoadPngImage(const char *path, png_bytep **linha_ptr, int *whidth, int *height) {    
    FILE *f = fopen(path, "rb");
    if (!f) {
        return;
    }
    png_structp PngPointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!PngPointer) {
        fclose(f);
        return;
    }

    png_infop InfoPointer = png_create_info_struct(PngPointer);
    
    if (!InfoPointer) {
        fclose(f);
        png_destroy_read_struct(&PngPointer, NULL, NULL);
        return;
    }

    if (setjmp(png_jmpbuf(PngPointer))) {
        fclose(f);
        png_destroy_read_struct(&PngPointer, &InfoPointer, NULL);
        return;
    }
    
    png_init_io(PngPointer, f);
    png_read_info(PngPointer, InfoPointer);
    *whidth = png_get_image_width(PngPointer, InfoPointer);
    *height = png_get_image_height(PngPointer, InfoPointer);
    int cor = png_get_color_type(PngPointer, InfoPointer);
    int BitDepth = png_get_bit_depth(PngPointer, InfoPointer);
    

    switch (cor) {
    case PNG_COLOR_TYPE_GRAY:
        printf("Grayscale image\n");
        break;
    case PNG_COLOR_TYPE_RGB:
        printf("Image in RGB mode (Red, Green, Blue)\n");
        break;
    case PNG_COLOR_TYPE_PALETTE:
        printf("Image using indexed color palette\n");
        break;
    case PNG_COLOR_TYPE_GRAY_ALPHA:
        printf("Grayscale image with alpha channel\n");
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        printf("Image in RGBA mode (Red, Green, Blue, Alpha)\n");
        break;
    default:
        printf("Unsupported image format\n");
    }

    if (BitDepth == 16) {
        png_set_strip_16(PngPointer);
    }

    if (cor == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(PngPointer);
    }
    if (cor == PNG_COLOR_TYPE_GRAY && BitDepth < 8) {
        png_set_expand_gray_1_2_4_to_8(PngPointer);
    }
    if (png_get_valid(PngPointer, InfoPointer, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(PngPointer);
    }
    if (cor == PNG_COLOR_TYPE_RGB || cor == PNG_COLOR_TYPE_GRAY || cor == PNG_COLOR_TYPE_PALETTE) {
        png_set_filler(PngPointer, 0xFF, PNG_FILLER_AFTER);
    }
    if (cor == PNG_COLOR_TYPE_GRAY || cor == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(PngPointer);
    }

    png_read_update_info(PngPointer, InfoPointer);
    *linha_ptr = (png_bytep*)malloc(sizeof(png_bytep) * (*height));
    for (int y = 0; y < *height; y++) {
        (*linha_ptr)[y] = (png_byte*)malloc(png_get_rowbytes(PngPointer, InfoPointer));
    }
    png_read_image(PngPointer, *linha_ptr);
    fclose(f);
    png_destroy_read_struct(&PngPointer, &InfoPointer, NULL);
}

/**
 * @brief This function will save any changes made to the image
 *
 * @param char_const *path to image
 * @param png_bytep reference to image
 * @param int Width
 * @param int Height

 * @return Void
 */
void Save(const char *path, png_bytep *RowPointer, int Width, int Height) {
    FILE *f = fopen(path, "wb");
    if (!f) return;
    png_structp PngPointer = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    if (!PngPointer) {
        fclose(f);
        return;
    }

    png_infop InfoPointer = png_create_info_struct(PngPointer);
    if (!InfoPointer) {
        fclose(f);
        png_destroy_write_struct(&PngPointer, NULL);
        return;
    }

    if (setjmp(png_jmpbuf(PngPointer))) {
        fclose(f);
        png_destroy_write_struct(&PngPointer, &InfoPointer);
        return;
    }

    png_init_io(PngPointer, f);
    png_set_IHDR(PngPointer, InfoPointer, Width, Height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(PngPointer, InfoPointer);
    png_write_image(PngPointer, RowPointer);
    png_write_end(PngPointer, NULL);

    fclose(f);
    png_destroy_write_struct(&PngPointer, &InfoPointer);
    
    FILE *t = fopen(path, "rb");
    if (t) {
        printf("Success open the image.\n");
        fclose(t);
    } else {    
        printf("Error load image.\n");
    }
}

/**
 * @brief recovers the message that was hidden in the image
 *
 * @param png_bytep reference to image
 * @param int Width
 * @param int Height
 * @param char string in binary
 * 
 * @return char*
 */
char *RecoverMessage(png_bytep *RowPointer, int widht, int height, char stringbin[]) {
    int i_msg = 0;
    char *HiddenMessage = (char*) calloc(strlen(stringbin), sizeof(char));

    for (int c = 0; c < height; c++) {
        for (int o = 0; o < widht; o++) {
            int ip = o * 4; // Índice do pixel
            if (i_msg < strlen(stringbin)-1) {
                //extract the least significant binary
                HiddenMessage[i_msg] = (RowPointer[c][ip] & 1) + '0'; // R
                i_msg++;
                
                ip += 4;
            } else {
                break;
            }
        }
    }
    //add the terminator character of string
    HiddenMessage[i_msg] = '\0';
    printf("message in binary form\n");
    for (int i = 0; i < strlen(HiddenMessage); i++) {
        printf("%c", HiddenMessage[i]);
    }
    printf("\n");

    return HiddenMessage;
}

/**
 * @brief Verifica se o nome de usuário já existe no sistema
 *
 * @param png_bytep reference to image
 * @param int Width
 * @param int Height
 * @param char string in binary
 * 
 * @return void
 */
void code (png_bytep *Rptr, int width, int height, char *bin) {
    int i_msg = 0;
    for (int c = 0; c < width; c++) {
        for (int o = 0; o < width; o++) {
            int ip = o*4;
            if (i_msg < strlen(bin)) {
                char bit = bin[i_msg++];

                Rptr[c][ip] = (Rptr[c][ip] & 0xFE) | (bit - '0');
                Rptr[c][ip + 1] = (Rptr[c][ip + 1] & 0xFE) | (bit - '0');
                Rptr[c][ip + 2] = (Rptr[c][ip + 2] & 0xFE) | (bit - '0');

                ip += 4;
            } else {
                break;
            }
        }
    }
}

/**
 * @brief frees up the memory that was allocated to the image
 *
  *@param png_bytep reference to image
 * @param int Height
 * 
 * @return void
 */
void FreePngImage(png_bytep *RowPointer, int height) {
    if (RowPointer == NULL) {
        return;
    }
    for (int y = 0; y < height; y++) {
        free(RowPointer[y]);
    }
    free(RowPointer);
}

/**
 * @brief transforms the character into its binary form
 *
 * @param char_const character
 * @param char []vector that will be saved the binary version
 * 
 * @return void
 */
void CharToBin(char charactere, char bin[]) {
    for (int i = 7; i >= 0; i--) {
        if (charactere & (1 << i)) {
            bin[7-i] = '1';
        } else {
            bin[7-i] = '0';
        }
    }
}

/**
 * @brief binary to character transformation
 *
 * @param char_const* bin representation
 * 
 * @return char
 */
char BinToChar(const char* binario) {
    unsigned long num = strtoul(binario, NULL, 2);
    return (char)num;
}

/**
 * @brief prints the word present in a binary sequence
 *
 * @param char_const* bin
 * @param int size the word
 * 
 * @return void
 */
void PrintSequenceBin(char *bin, int size) {
    char *decode = (char*) calloc(size, sizeof(char));
    for (int i = 0; i < size; i++) {
        char RpsBin[9];
        RpsBin[8] = '\0';
        strncpy(RpsBin, &bin[8 * i], 8);
        decode[i] = BinToChar(RpsBin);
    }
    printf("message present in the binary sequence = %s", decode);
}

/* 
    Comentario que não estara presente na versão do github//
    para fazer o teste do programa eu vou esconder três mensagens diferentes em três imagens diferentes
    e irei imprimiar na tela sua representação binaria e a sua tradução

    passar 
    ler a imagem
    esconder a mensangem
    recuperar a imagem
    e printar  a imagem

    o programa foi estruturado para seguir estes passos as imagens estão na pasta img
    
    os resultados gerados pelo programa estão no arquivo de texto saida.txt
*/

int main() {
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    const char* fileName = "./img/chaves.png";
    png_bytep *RowPointer;
    int width, height;
    
    char bin[strlen(chaves)*8];
    for (int i = 0; i < strlen(chaves); i++) {
        CharToBin(chaves[i], &bin[i*8]);
    }

    LoadPngImage(fileName, &RowPointer, &width, &height);
    printf("uploaded image: %dx%d pixels\n", width, height);
    code(RowPointer, width, height, bin);
    Save(fileName, RowPointer, width, height);
    LoadPngImage(fileName, &RowPointer, &width, &height);
    PrintSequenceBin(RecoverMessage(RowPointer, width, height, bin), strlen(chaves));
    FreePngImage(RowPointer, height);
    printf("--------------------------------------------------------------------------------------------------------------------\n\n");
    
    return 0;
}
