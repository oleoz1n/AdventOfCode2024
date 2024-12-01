#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

// Inicializa o dicionário
void initDictionary(Dictionary *dict) {
    dict->size = 0;
    dict->capacity = 5;
    dict->pairs = (KeyValuePair *)malloc(dict->capacity * sizeof(KeyValuePair));
}

// Adiciona um par chave-valor
void addKeyValue(Dictionary *dict, const char *key, const char *value) {
    if (dict->size >= dict->capacity) {
        dict->capacity *= 2;
        dict->pairs = (KeyValuePair *)realloc(dict->pairs, dict->capacity * sizeof(KeyValuePair));
    }
    dict->pairs[dict->size].key = strdup(key);
    dict->pairs[dict->size].value = strdup(value);
    dict->size++;
}

// Busca um valor por chave
char *getValue(Dictionary *dict, const char *key) {
    for (int i = 0; i < dict->size; i++) {
        if (strcmp(dict->pairs[i].key, key) == 0) {
            return dict->pairs[i].value;
        }
    }
    return NULL;
}

// Libera a memória do dicionário
void freeDictionary(Dictionary *dict) {
    for (int i = 0; i < dict->size; i++) {
        free(dict->pairs[i].key);
        free(dict->pairs[i].value);
    }
    free(dict->pairs);
}