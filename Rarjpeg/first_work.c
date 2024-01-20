#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZIP_MAGIC_NUMBER 0x504B0304

int main(void)
{
    char filename[512];

    FILE *file;
    int bytes = 0;
    unsigned char jpeg_header[] = {0xFF, 0xD8};
    unsigned char zip_magic_header[] = {0x50, 0x4B};
    unsigned char buffer[2];

    printf("Введите путь к файлу: ");
    fgets(filename, sizeof(filename), stdin);
    size_t len = strlen(filename);

    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }
    file = fopen(filename, "rb");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    fseek(file, -2, SEEK_END);
    long fileSize = ftell(file);

    for (int i = fileSize - 2 ; i >= 0 ; i -= 2){
        fseek(file, i, SEEK_SET);
        if (fread(buffer, 1, sizeof(buffer), file) == sizeof(buffer)){
            if (buffer[0] == zip_magic_header[0] && buffer[1] == zip_magic_header[1]){
                printf("В файле зашифрован ZIP архив\n");
                break;
            }
            else if(buffer[0] == jpeg_header[0] && buffer[1] == jpeg_header[1]){
                printf("В файле не зашифрован ZIP архив\n");
                break;
            }
        }
    }
    fclose(file);

    return 0;
}