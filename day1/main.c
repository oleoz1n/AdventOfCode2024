#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/dict.h"

// Declaração das funções
char **strsplit(const char *src, const char *delim);
void strsplitfree(char **strlist);

// Função para dividir strings
char **strsplit(const char *src, const char *delim) {
    char *pbuf = NULL;
    char *ptok = NULL;
    int count = 0;
    char **pparr = NULL;

    size_t srclen = strlen(src);

    pbuf = (char *)malloc((srclen + 1) * sizeof(char));
    if (!pbuf) return NULL;

    strcpy(pbuf, src);

    ptok = strtok(pbuf, delim);
    while (ptok) {
        char **temp = (char **)realloc(pparr, (size_t)(count + 1) * sizeof(char *));
        if (!temp) {
            strsplitfree(pparr);
            free(pbuf);
            return NULL;
        }
        pparr = temp;

        *(pparr + count) = strdup(ptok);
        if (!*(pparr + count)) {
            strsplitfree(pparr);
            free(pbuf);
            return NULL;
        }

        count++;
        ptok = strtok(NULL, delim);
    }

    char **temp = (char **)realloc(pparr, (size_t)(count + 1) * sizeof(char *));
    if (!temp) {
        strsplitfree(pparr);
        free(pbuf);
        return NULL;
    }
    pparr = temp;
    *(pparr + count) = NULL;

    free(pbuf);
    return pparr;
}

// Função para liberar a memória da lista de strings
void strsplitfree(char **strlist) {
    if (!strlist) return;

    int i = 0;
    while (strlist[i]) {
        free(strlist[i++]);
    }
    free(strlist);
}

int sort(int* list, int size) {
    int i, j, temp;

    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (list[i] > list[j]) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    return 0;
}

int sumcalcdiffabs(int* list, int* list2, int size) {
    int i, sum = 0;

    for (i = 0; i < size; i++) {
        sum += abs(list[i] - list2[i]);
    }
    return sum;
}

// Para cada valor da lista ver quantas vezes ele se repete
Dictionary calcQtd(int *list, int size) {
    Dictionary dict;
    initDictionary(&dict);

    int i, j, qtd;

    for (i = 0; i < size; i++) {
        // Converte o valor de list[i] para string
        char keyStr[10];
        snprintf(keyStr, sizeof(keyStr), "%d", list[i]);

        // Verifica se a chave já foi processada
        const char *value = getValue(&dict, keyStr);
        if (value == NULL) {
            // Conta as ocorrências do número
            addKeyValue(&dict, keyStr, "1");
        }
            
        else {
            // Incrementa a quantidade de ocorrências
            qtd = atoi(value);
            qtd++;
            char qtdStr[10];
            snprintf(qtdStr, sizeof(qtdStr), "%d", qtd);
            updateKeyValue(&dict, keyStr, qtdStr);
        }
        
    }

    return dict;
}

int sumtotalmultiplefreq(Dictionary dict, int *list, int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        // Converter a chave (int) para uma string para buscar no dicionário
        char key[32]; // Buffer para armazenar a chave como string
        snprintf(key, sizeof(key), "%d", list[i]); // Formatar o inteiro como string

        // Obter o valor associado à chave
        char *value = getValue(&dict, key);
        if (value != NULL) {
            // Converter o valor retornado para inteiro e multiplicar
            sum += list[i] * atoi(value);
        }
    }

    return sum;
}

// Função principal
int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char buffer[1024];
    char **vec = NULL;

    int *listLeft = NULL;  // Array dinâmico para armazenar os valores da esquerda
    int *listRight = NULL; // Array dinâmico para armazenar os valores da direita
    int size = 0;          // Tamanho dos arrays

    // Processa cada linha do arquivo
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove o caractere de nova linha
        vec = strsplit(buffer, " ");
        if (!vec || !vec[0] || !vec[1]) {
            strsplitfree(vec);
            continue;
        }

        // Redimensiona os arrays dinâmicos
        int *tempLeft = (int *)realloc(listLeft, (size + 1) * sizeof(int));
        int *tempRight = (int *)realloc(listRight, (size + 1) * sizeof(int));

        if (!tempLeft || !tempRight) {
            perror("Erro ao alocar memória");
            free(listLeft);
            free(listRight);
            strsplitfree(vec);
            fclose(file);
            return 1;
        }

        listLeft = tempLeft;
        listRight = tempRight;

        // Converte as strings para inteiros e armazena
        listLeft[size] = atoi(vec[0]);
        listRight[size] = atoi(vec[1]);
        size++;

        strsplitfree(vec); // Libera a memória da linha processada
    }

    fclose(file);

    // Parte 2
    Dictionary dict = calcQtd(listRight, size);

    int total = sumtotalmultiplefreq(dict, listLeft, size);
    
    printf("Total: %d\n", total);

    // Libera a memória das listas dinâmicas
    free(listLeft);
    free(listRight);

    // Libera a memória do dicionário
    freeDictionary(&dict);

    return 0;
}