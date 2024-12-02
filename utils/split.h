#ifndef SPLIT_H
#define SPLIT_H

char **strsplit(const char *src, const char *delim);
void strsplitfree(char **strlist);

#endif // DICT_H