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
            /*for (int j = 0; j < sizeof(buffer); ++j) {
                printf("%02X", buffer[j]);
            }*/
            //printf("\n");
            if (buffer[0] == zip_central_header[0] && buffer[1] == zip_central_header[1] && buffer[2] == zip_central_header[2] && buffer[3] == zip_central_header[3]) {
                printf("В файле зашифрован ZIP архив файлы внутри\n"); 
                struct CentralDirectory cdRecord;
                fread(&cdRecord,sizeof(struct CentralDirectory), 1, file );
                fseek(file, i + sizeof(struct CentralDirectory), SEEK_SET);
                char *fileName = (char *)malloc(cdRecord.fileNameLength + 1);
                fread(fileName, 1, cdRecord.fileNameLength, file);
                fileName[cdRecord.fileNameLength] = '\0';
                printf("Signature: %08X\n", cdRecord.signature);
                printf("Version: %hu\n", cdRecord.version);
                printf("Version Needed: %hu\n", cdRecord.versionNeeded);
                printf("Flags: %hu\n", cdRecord.flags);
                printf("Compression: %hu\n", cdRecord.compression);
                printf("Modtime: %hu\n", cdRecord.modtime);
                printf("MmodDate: %hu\n", cdRecord.MmodDate);
                printf("CRC32: %08X\n", cdRecord.crc32);
                printf("Compressed Size: %u\n", cdRecord.compressedSize);
                printf("Uncompressed Size: %u\n", cdRecord.uncompressedSize);
                printf("File Name Length: %hu\n", cdRecord.fileNameLength);
                printf("Extra Field Length: %hu\n", cdRecord.extraFieldLength);
                printf("File Comment Length: %hu\n", cdRecord.fileCommLength);
                printf("Disk Start: %hu\n", cdRecord.diskStart);
                printf("Internal File Attributes: %hu\n", cdRecord.internalFileAttributes);
                printf("External File Attributes: %08X\n", cdRecord.externalFileAttributes);
                printf("Offset of Local Header: %08X\n", cdRecord.offsetOfLocalHeader);
                free(fileName);
            }
            //printf("\n");
        }
    }
    fclose(file);

    return 0;
}