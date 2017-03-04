//
// Created by Ben Richards on 3/1/17.
//
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include "types.h"

#define STRING(s) ((String*)s)
#define ENTRY(e) ((entry*)e)
#define MAP(m) ((HashMap*)m)

void *new(TYPE t, int num, ...) {
    void *new_t;
    va_list args;
    va_start(args, num);

    switch (t) {
        case (STRING):
            new_t = (String*)malloc(sizeof(String));
            String *newString = (String*)new_t;

            const char *src = va_arg(args, const char *);
            int len = (int)strlen(src);

            newString->cap = len ? len : 1;
            newString->len = len;
            newString->data = (num == 0) ? (char*)malloc(1) : (char*)malloc((size_t)newString->cap + 1);

            for (int i = 0; i < len; i++)
                newString->data[i] = src[i];
            newString->data[len] = '\0';
            break;
        case (ENTRY):
            assert(num == 2);
            new_t = (entry*)malloc(sizeof(entry));
            entry *newEntry = (entry*)new_t;

            String *key = va_arg(args, String*);
            newEntry->key = new(STRING, 1, key->data);
            newEntry->value = va_arg(args, int);
            newEntry->next = NULL;
            break;
        case (HASHMAP):
            assert(num == 0);
            new_t = (HashMap*)malloc(sizeof(HashMap));
            HashMap *newMap = (HashMap*)new_t;

            newMap->entrySet = (entry**)malloc(sizeof(entry*) * HASH_SIZE);
            newMap->keySet = (String**)malloc(sizeof(String*) * HASH_SIZE);
            for (int i = 0; i < HASH_SIZE; i++) {
                newMap->keySet[i] = NULL;
                newMap->entrySet[i] = NULL;
            }
            break;
        default:
            new_t = NULL;
            break;
    }

    va_end(args);
    return new_t;
}

void delete(TYPE t, void *d) {
    switch(t) {
        case (STRING):
            free(STRING(d)->data);
            free(d);
            return;
        case (ENTRY):
            delete(STRING, ENTRY(d)->key);
            free(d);
            return;
        case (HASHMAP):
            clear(MAP(d));
            free(MAP(d)->entrySet);
            free(MAP(d)->keySet);
            free(d);
        default:
            return;
    }
}
