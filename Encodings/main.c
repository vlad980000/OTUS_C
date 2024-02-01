#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void convert_CP1251_to_UTF8(const char *input, char *output) {
    char *result = output;
    for (; *input != '\0'; ++input) {
        unsigned char current_char = (unsigned char)(*input);
        if (current_char < 0x80) {
            *output = current_char;
            ++output;
        } else {
            *output = (char)(0xC0 + (current_char >> 6));
            ++output;

            *output = (char)(0x80 + (current_char & 0x3F));
            ++output;
        }
    }
    *output = '\0';
}

int main(void) {
    char filename[512];
    FILE *file;

    printf("Введите путь к файлу: ");
    fgets(filename, sizeof(filename), stdin);
    size_t len = strlen(filename);

    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);
    char *buffer = (char *)malloc(file_size);
    char *utf8String = (char *)malloc(file_size * 2);

    printf("Размер файла %zu\n", file_size);

    if (buffer == NULL || utf8String == NULL) {
        printf("Не удалось выделить память для буфера.\n");
        fclose(file);
        free(buffer);
        free(utf8String);
        return 1;
    }

    size_t buffer_read = fread(buffer, 1, file_size, file);

    for (size_t i = 0; i < buffer_read; ++i) {
        if (buffer[i] == 0x1A) {
            buffer_read = i;
            break;
        }
    }

    convert_CP1251_to_UTF8(buffer, utf8String);
    printf("%s", utf8String);
    free(buffer);
    free(utf8String);
    fclose(file);
    return 0;
}
