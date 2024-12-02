#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void strsplitfree(char **strlist) {
    if (!strlist) return;

    int i = 0;
    while (strlist[i]) {
        free(strlist[i++]);
    }
    free(strlist);
}

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