#ifndef DICT_H
#define DICT_H

typedef struct {
    char *key;
    char *value;
} KeyValuePair;

typedef struct {
    KeyValuePair *pairs;
    int size;
    int capacity;
} Dictionary;

void initDictionary(Dictionary *dict);
void addKeyValue(Dictionary *dict, const char *key, const char *value);
char *getValue(Dictionary *dict, const char *key);
void freeDictionary(Dictionary *dict);

#endif // DICT_H
