#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZIP_MAGIC_NUMBER 0x504B0304
#pragma pack(1)
struct CentralDirectory{
    unsigned int signature;
    unsigned short version;
    unsigned short versionNeeded;
    unsigned short flags;
    unsigned short compression;
    unsigned short modtime;
    unsigned short MmodDate;
    unsigned int crc32;
    unsigned int compressedSize;
    unsigned int uncompressedSize;
    unsigned short fileNameLength;
    unsigned short extraFieldLength;
    unsigned short fileCommLength;
    unsigned short diskStart;
    unsigned short internalFileAttributes;
    unsigned int externalFileAttributes;
    unsigned int offsetOfLocalHeader;
};

int main(void)
{
    char filename[512];

    FILE *file;
    int bytes = 0;
    unsigned char jpeg_header[] = {0xFF, 0xD8};
    unsigned char zip_magic_header[] = {0x50, 0x4B ,0x03, 0x04};
    unsigned char zip_magic_header_empty[] = {0x50, 0x4B ,0x05, 0x06};
    unsigned char zip_central_header[] = {0x50, 0x4B ,0x01, 0x02};
    unsigned char buffer[4];
    unsigned int isZip = 0;

    char** fileNames = NULL;
    size_t fileNamesCount = 0;

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
            if(buffer[0] == zip_magic_header_empty[0] && buffer[1] == zip_magic_header_empty[1] && buffer[2] == zip_magic_header_empty[2] && buffer[3] == zip_magic_header_empty[3]){
                isZip = 1;
            }
            if (buffer[0] == zip_central_header[0] && buffer[1] == zip_central_header[1] && buffer[2] == zip_central_header[2] && buffer[3] == zip_central_header[3]) {
                fseek(file, i, SEEK_SET);
                struct CentralDirectory cdRecord;
                fread(&cdRecord, sizeof( cdRecord), 1, file);
                char *fileName = (char *)malloc(cdRecord.fileNameLength + 1);
                fread(fileName, 1, cdRecord.fileNameLength, file);
                fileName[cdRecord.fileNameLength] = '\0';
                fileNamesCount++;
                fileNames = realloc(fileNames, fileNamesCount * sizeof(char*));
                fileNames[fileNamesCount - 1] = fileName;
            }
        }
    }

    if (fileNamesCount == 0 && isZip == 0){
        printf("Зашифрованных файлов нет, это не ZIP архив");

        free(fileNames);
        fclose(file);

        return 0;
    }

    printf("Это точно ZIP архив, если он не пустой то ниже появятся имена файлов:\n");
    for (size_t i = 0; i < fileNamesCount; i++) {
        printf("%s\n", fileNames[i]);
    }

    for (size_t i = 0; i < fileNamesCount; i++) {
        free(fileNames[i]);
    }
    free(fileNames);
    fclose(file);

    return 0;
}