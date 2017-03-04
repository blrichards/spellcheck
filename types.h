//
// Created by Ben Richards on 3/2/17.
//

#include <stdbool.h>

#ifndef SPELLCHECK_STRING_H
#define SPELLCHECK_STRING_H

#define HASH_SIZE 1000000

typedef enum {
    STRING,
    ENTRY,
    HASHMAP,
} TYPE;

typedef struct {
    char *data;
    int   len;
    int   cap;
} String;

/* @struct: entry
 * @brief: node for linked list to store collided entries
 */
typedef struct entry {
    struct entry *next;
    String *key;
    bool value;
} entry;

/* @struct: Dict
 * @brief: Essentially a set that uses a hash table to quickly check
 *         if words exist in the "dictionary"
 */
typedef struct {
    entry **entrySet;
    String **keySet;
    int size;
} HashMap;

void *new(TYPE, int, ...);
void  delete(TYPE, void*);

/** String functions **/
void concat(String*, String*);
void addChar(String*, const char);
String *toLower(String*);
bool    equals(String*,String*);

/** HashMap functions **/
void put(HashMap *map, String *key, bool value);
bool contains(HashMap *dict, String *key);
bool at(HashMap *dict, String *key);
void clear(HashMap *dict);

#endif //SPELLCHECK_STRING_H
