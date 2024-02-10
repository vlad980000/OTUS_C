#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define RUSS_CHAR_COUNT 66

struct decode_to_utf8 {
    unsigned char char_to_decode;
    unsigned char utf8_byte_1;
    unsigned char utf8_byte_2;
};

void fill_dict_to_iso88595(struct decode_to_utf8 *dict){
    int i;
    unsigned char iso_start = 0xB0;
    unsigned char utf8_start_byte1 = 0xD0;
    unsigned char utf8_start_byte2 = 0x90;

    for(i = 0; i < 64;  i++){
        dict[i].char_to_decode = iso_start + i;
        unsigned char utf8_combined; 

        utf8_combined = (utf8_start_byte1 << 8) | utf8_start_byte2;

        utf8_combined += i;

        dict[i].utf8_byte_1 = (utf8_combined >> 8) & 0xFF;
        dict[i].utf8_byte_2 = utf8_combined & 0xFF;
        
    }

    dict[65].char_to_decode = 0xA1; dict[65].utf8_byte_1 = 0xD0; dict[65].utf8_byte_2 = 0x81;
    dict[66].char_to_decode = 0xF1; dict[66].utf8_byte_1 = 0xD1; dict[66].utf8_byte_2 = 0x91;

}

void fill_dict(struct decode_to_utf8 *dict, 
                        unsigned char cp1251_start,
                        unsigned char utf8_start_byte1,
                        unsigned char utf8_start_byte2,
                        unsigned char special_char_1,
                        unsigned char special_char_2){
    
    int i;
    
    for (i = 0; i < 48; i++) {
        dict[i].char_to_decode = cp1251_start + i;
        dict[i].utf8_byte_1 = utf8_start_byte1;
        dict[i].utf8_byte_2 = utf8_start_byte2 + i;
    }

    cp1251_start = 0xF0;
    utf8_start_byte1 = 0xD1;
    utf8_start_byte2 = 0x80;
    for(i = 48; i < 64; i++){
        dict[i].char_to_decode = cp1251_start + i - 48;
        dict[i].utf8_byte_1 = utf8_start_byte1;
        dict[i].utf8_byte_2 = utf8_start_byte2 + i - 48;
    }

    dict[64].char_to_decode = special_char_1; dict[64].utf8_byte_1 = 0xD0; dict[64].utf8_byte_2 = 0x01;
    dict[65].char_to_decode = special_char_2; dict[65].utf8_byte_1 = 0xD1; dict[65].utf8_byte_2 = 0x91;
}

void fill_dict_to_KOI8_R(struct decode_to_utf8 *dict ){
    int i;

    dict[0].char_to_decode = 0xC0;  dict[0].utf8_byte_1 = 0xD1; dict[0].utf8_byte_2 = 0x8E;
    dict[1].char_to_decode = 0xC1;  dict[1].utf8_byte_1 = 0xD0; dict[1].utf8_byte_2 = 0xB0;
    dict[2].char_to_decode = 0xC2;  dict[2].utf8_byte_1 = 0xD0; dict[2].utf8_byte_2 = 0xB1;
    dict[3].char_to_decode = 0xC3;  dict[3].utf8_byte_1 = 0xD1; dict[3].utf8_byte_2 = 0x86;
    dict[4].char_to_decode = 0xC4;  dict[4].utf8_byte_1 = 0xD0; dict[4].utf8_byte_2 = 0xB4;
    dict[5].char_to_decode = 0xC5;  dict[5].utf8_byte_1 = 0xD0; dict[5].utf8_byte_2 = 0xB5;
    dict[6].char_to_decode = 0xC6;  dict[6].utf8_byte_1 = 0xD1; dict[6].utf8_byte_2 = 0x84;
    dict[7].char_to_decode = 0xC7;  dict[7].utf8_byte_1 = 0xD0; dict[7].utf8_byte_2 = 0xB3;
    dict[8].char_to_decode = 0xC8;  dict[8].utf8_byte_1 = 0xD1; dict[8].utf8_byte_2 = 0x85;
    dict[9].char_to_decode = 0xC9;  dict[9].utf8_byte_1 = 0xD0; dict[9].utf8_byte_2 = 0xB8;
    dict[10].char_to_decode = 0xCA;  dict[10].utf8_byte_1 = 0xD0; dict[10].utf8_byte_2 = 0xB9;
    dict[11].char_to_decode = 0xCB;  dict[11].utf8_byte_1 = 0xD0; dict[11].utf8_byte_2 = 0xBA;
    dict[12].char_to_decode = 0xCC;  dict[12].utf8_byte_1 = 0xD0; dict[12].utf8_byte_2 = 0xBB;
    dict[13].char_to_decode = 0xCD;  dict[13].utf8_byte_1 = 0xD0; dict[13].utf8_byte_2 = 0xBC;
    dict[14].char_to_decode = 0xCE;  dict[14].utf8_byte_1 = 0xD0; dict[14].utf8_byte_2 = 0xBD;
    dict[15].char_to_decode = 0xCF;  dict[15].utf8_byte_1 = 0xD0; dict[15].utf8_byte_2 = 0xBE;
    dict[16].char_to_decode = 0xD0;  dict[16].utf8_byte_1 = 0xD0; dict[16].utf8_byte_2 = 0xBF;
    dict[17].char_to_decode = 0xD1;  dict[17].utf8_byte_1 = 0xD1; dict[17].utf8_byte_2 = 0x8F;
    dict[18].char_to_decode = 0xD2;  dict[18].utf8_byte_1 = 0xD1; dict[18].utf8_byte_2 = 0x80;
    dict[19].char_to_decode = 0xD3;  dict[19].utf8_byte_1 = 0xD1; dict[19].utf8_byte_2 = 0x81;
    dict[20].char_to_decode = 0xD4;  dict[20].utf8_byte_1 = 0xD1; dict[20].utf8_byte_2 = 0x82;
    dict[21].char_to_decode = 0xD5;  dict[21].utf8_byte_1 = 0xD1; dict[21].utf8_byte_2 = 0x83;
    dict[22].char_to_decode = 0xD6;  dict[22].utf8_byte_1 = 0xD0; dict[22].utf8_byte_2 = 0xB6;
    dict[23].char_to_decode = 0xD7;  dict[23].utf8_byte_1 = 0xD0; dict[23].utf8_byte_2 = 0xB2;
    dict[24].char_to_decode = 0xD8;  dict[24].utf8_byte_1 = 0xD1; dict[24].utf8_byte_2 = 0x8C;
    dict[25].char_to_decode = 0xD9;  dict[25].utf8_byte_1 = 0xD1; dict[25].utf8_byte_2 = 0x8B;
    dict[26].char_to_decode = 0xDA;  dict[26].utf8_byte_1 = 0xD0; dict[26].utf8_byte_2 = 0xB7;
    dict[27].char_to_decode = 0xDB;  dict[27].utf8_byte_1 = 0xD1; dict[27].utf8_byte_2 = 0x88;
    dict[28].char_to_decode = 0xDC;  dict[28].utf8_byte_1 = 0xD1; dict[28].utf8_byte_2 = 0x8D;
    dict[29].char_to_decode = 0xDD;  dict[29].utf8_byte_1 = 0xD1; dict[29].utf8_byte_2 = 0x89;
    dict[30].char_to_decode = 0xDE;  dict[30].utf8_byte_1 = 0xD1; dict[30].utf8_byte_2 = 0x87;
    dict[31].char_to_decode = 0xDF;  dict[31].utf8_byte_1 = 0xD0; dict[31].utf8_byte_2 = 0x81;

    for(i = 32; i < 64; i++){
        dict[i].char_to_decode = dict[i + 32].char_to_decode + 32;
        dict[i].utf8_byte_1 = dict[i - 32].utf8_byte_1 + 32;
        dict[i].utf8_byte_2 = dict[i - 32].utf8_byte_2;
        unsigned char utf8_combined; 

        utf8_combined = (dict[i].utf8_byte_1 << 8) | dict[i].utf8_byte_2;

        utf8_combined -= 0x0020;

        dict[i].utf8_byte_1 = (utf8_combined >> 8) & 0xFF;
        dict[i].utf8_byte_2 = utf8_combined & 0xFF;
    }

    dict[35].char_to_decode = 0xA3;  dict[35].utf8_byte_1 = 0xD1; dict[35].utf8_byte_2 = 0x91;
    dict[36].char_to_decode = 0xB3;  dict[36].utf8_byte_1 = 0xD1; dict[36].utf8_byte_2 = 0x8A;

}


void convert_CP1251_to_UTF8(const char *input, char *output, struct decode_to_utf8 dict[], int dict_size) {
    for (; *input != '\0'; ++input) {
        unsigned char current_char = (unsigned char)(*input);
        if (current_char >= 0xC0 && current_char <= 0xFF) {
            for(int i = 0; i < dict_size; i++){
                if(current_char == dict[i].char_to_decode){
                    *output = (char)dict[i].utf8_byte_1;
                    ++output;
                    *output = (char)dict[i].utf8_byte_2;
                    ++output;
                }
            }
        } else {
            *output = current_char; 
            ++output;
        }
    }
    *output = '\0'; 
}

int main(void) {    
    char filename[512];
    char code_name[256];
    FILE *file;
    FILE *output_file;
    int valid_input = 0;
    int switch_flag = 0;
    while (!valid_input) { 
        printf("Введите кодировку (одна из CP-1251, KOI8-R, ISO-8859-5): ");
        fgets(code_name, sizeof(code_name), stdin);

        code_name[strcspn(code_name, "\n")] = 0;

        if (strcmp(code_name, "CP-1251") == 0){
            valid_input = 1; 
            switch_flag = 1;
        }
        else if (strcmp(code_name, "KOI8-R") == 0){
            valid_input = 1; 
            switch_flag = 2;
        }
        else if (strcmp(code_name, "ISO-8859-5") == 0){
            valid_input = 1; 
            switch_flag = 3;
        } 
        else {
            printf("Неверный ввод. Пожалуйста, введите одну из указанных кодировок.\n");
            switch_flag = 0;
        }
    }
    
    while (1) {
        fgets(filename, sizeof(filename), stdin);
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Ошибка открытия файла");
            printf("Попробуйте снова.\n");
        } else {
            break; 
        }
    }

    output_file = fopen("output_file.txt", "w");

    if (file == NULL) {
        perror("Ошибка создания файла");
        return 1;
    }
    fprintf(stdout, "Выходной файл создан по следующему пути: output_file.txt\n");

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
    struct decode_to_utf8 dict[RUSS_CHAR_COUNT];

    switch (switch_flag)
    {
    case 1:
        fill_dict(dict, 0xC0, 0xD0, 0x90, 0xA8, 0xB8);
        break;
    case 2:
        fill_dict_to_KOI8_R(dict);
        break;
    case 3:
        fill_dict(dict, 0xB0, 0xD0, 0x90, 0xA1, 0xF1);
        break;
    default:
        break;
    }

    convert_CP1251_to_UTF8(buffer, utf8String, dict ,RUSS_CHAR_COUNT);
    printf(utf8String);
    fprintf(output_file, utf8String);
    free(buffer);
    free(utf8String);
    fclose(file);
    fclose(output_file);
    return 0;
}
