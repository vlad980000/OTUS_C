#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_IN_WORD 150
#define INIT_ITEMS_COUNT 100

typedef struct {
    unsigned int count;
    char value[MAX_CHARS_IN_WORD];
} Hash_item;

typedef struct {
    int curr_count;
    Hash_item* table;
} Table;

void add_item(int hash, Table *table, char* word) {
    strcpy(table->table[hash].value, word);
    table->table[hash].count += 1;
}

int check_collusion(int hash, Table *table){
    if(strcmp(table->table[hash].value, "") == 0){
        return 0;
    }
    else{
        return 1;
    }
}

void print_table(Table *table) {
    for (int i = 0; i < table->curr_count; i++) {
        if(strcmp(table->table[i].value, "") != 0){
            printf("Индекс %d:\n", i);
            printf("Слово: %s\n", table->table[i].value);
            printf("Количество: %u\n", table->table[i].count);
            printf("-------------\n");
        }
    }
}

void rehash_fuction(int hash, Table *table){
    printf("%d\n", hash);
    Hash_item* new_table = malloc(hash * sizeof(Hash_item));
    for(int i = 0; i < table->curr_count; i++) {
        new_table[i].count = table->table[i].count;
        strncpy(new_table[i].value, table->table[i].value, sizeof(new_table[i].value) - 1);
        new_table[i].value[sizeof(new_table[i].value) - 1] = '\0';
        printf("%s \n", new_table[i].value);
        printf("%u \n", new_table[i].count);
    }
    free(table->table);
    table->curr_count = hash;
    table->table = new_table;
}

int check_item(int hash, Table *table, char* word){
    if(strcmp(table->table[hash].value, word) == 0){
        table->table[hash].count += 1;
        return 1;
    }
    else{
        return 0;
    }
}

void hash_function(const char* word, Table* table){
    unsigned int hash = 0;
    char* ptr = word; 
    int flag = 0;
    
    while(*ptr != '\0'){
        hash += *ptr;
        ptr++;
    }
    hash %= table->curr_count;
    while(flag == 0){
        if(hash > table->curr_count){
            rehash_fuction(hash, table);
        }
        if(check_item(hash, table, word) == 1){
            flag = 1;
        }
        if(check_collusion(hash, table) == 0){
            add_item(hash, table, word);
            flag = 1;
        }
        else{
            hash++;
        }
    }
    free(word);
    flag = 0;
}

int main() {
    char filename[512];
    printf("Введите путь к файлу: ");
    fgets(filename, sizeof(filename), stdin);
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }
    
    Table table;
    table.curr_count = INIT_ITEMS_COUNT;
    table.table = malloc(INIT_ITEMS_COUNT * sizeof(Hash_item));
    if (table.table == NULL) {
        perror("Ошибка выделения памяти");
        fclose(file);
        return 1;
    }
    char line[MAX_CHARS_IN_WORD];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, " ,.!;");
        while (token != NULL) {
            hash_function(strdup(token), &table);
            token = strtok(NULL, " ,.!;");
        }
    }
    print_table(&table);
    fclose(file);
    free(table.table);

    return 0;
}
