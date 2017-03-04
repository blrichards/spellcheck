#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <printf.h>
#include "types.h"

#define A 54059
#define B 76963
#define C 86969
#define START 37

/* @func: hashStr
 * @brief: used to hash Strings for "HashMap" struct
 * @input: String
 * @output: 32 bit unsigned hash value
 * @summary: generic hash function used for hashing Strings
 */
uint32_t hashStr(String *s) {
    uint32_t h = START;

    for (int i = 0; i < s->len; i++)
        h = (h * A) ^ (s->data[i] * B);

    return (h * C) % HASH_SIZE; // return number modded by the largest prime
}

/*
 * @func: value
 * @brief: find hash value in HashMap associated with a key
 * @input: HashMap pointer & key
 * @output: true if key was found, false otherwise
 * @summary: find open hash value or matching key by using a loop and the
 *           nextHash function. return the final hash value
 */
entry* find(HashMap *dict, String *key) {
    uint32_t h = hashStr(key);

    entry *current = dict->entrySet[h];

    while (current != NULL) {
        if (equals(current->key, key))
            return current;
        current = current->next;
    }

    return current;
}

/* @func: put
 * @brief: sets the key value pair in the specified HashMap instance
 * @input: HashMap pointer, key, & desired key value
 * @summary: checks if the key exists in the dictionary, add it if it doesn't,
 *           and assigns the desired value in the _values array
 */
void put(HashMap *dict, String *key, bool value) {
    int h = hashStr(key);

    if (dict->entrySet[h] == NULL) {
        dict->entrySet[h] = (entry*)new(ENTRY, 2, key, value);
        return;
    }

    entry *current = dict->entrySet[h];

    while (current->next != NULL)
        current = current->next;

    current->next = (entry*)new(ENTRY, 2, key, value);
}

/* @func: contains
 * @brief: check if word is in dictionary
 * @input: HashMap pointer & key
 * @output: true if word is in dict, false otherwise
 */
bool contains(HashMap *dict, String *key) {
    entry *a_word = find(dict, key);
    return a_word != NULL;
}

bool at(HashMap *dict, String *key) {
    entry *e = find(dict, key);
    assert(e != NULL);
    return (e)->value;
}

void clear(HashMap *dict) {
    entry *current;
    entry *next;

    for (uint32_t i = 0; i < HASH_SIZE; i++) {
        current = dict->entrySet[i];

        while (current != NULL) {
            next = current->next;
            delete(ENTRY, current);
            current = next;
        }
    }
    dict->size = 0;
}
