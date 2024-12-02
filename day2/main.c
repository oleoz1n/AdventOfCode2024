#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/split.h"
#include <stdbool.h>

bool isValid(int *vec, int len) {
    for(int i = 0; i < len; i++){
        if (i == 1) {
            if(abs(vec[i] - vec[i-1])  <= 3 && abs(vec[i] - vec[i-1]) >= 1){
                continue;
            } else return false;
        } else if (i > 1)
        {
            if(vec[0] > vec[1]){
                if(vec[i-1] - vec[i] <= 3 && vec[i-1] - vec[i] >= 1){
                    continue;
                } else return false;
            }
            if (vec[0] < vec[1]){
                if(vec[i] - vec[i-1] <= 3 && vec[i] - vec[i-1] >= 1){
                    continue;
                } else return false;
            }
        }
    }
    return true;
}

bool isValidWithoutOne(int *vec, int len){
    for(int i=0; i < len; i++){
    int tempVec[len-1], index = 0;

        for(int j=0; j< len; j++){
            if (j != i) {
                tempVec[index++] = vec[j];
            }
        }

        if(isValid(tempVec, len-1)) return true;
    
    }
    return false;
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char buffer[1024];
    char **vec = NULL;

    int valid = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char **vec = strsplit(buffer, " ");
        if (vec == NULL) {
            perror("Erro ao dividir a string");
            fclose(file);
            return 1;
        }

        int len = 0;

        for( int i = 0; vec[i] != NULL; i++) len++;

        int vec_int[len];

        for (int i = 0; i < len; i++) {
            vec_int[i] = atoi(vec[i]);
        }

        if (isValid(vec_int, len))
        { valid++; } else {
            if(isValidWithoutOne(vec_int, len)){
                valid++;
            }
        }
        
        strsplitfree(vec);
    }

    fclose(file);

    printf("Total: %d\n", valid);
    return 0;   
}