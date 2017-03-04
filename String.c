#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"

void doubleSize(String *s) {
    s->data = (char*)realloc(s->data, (size_t)s->cap * 2 + 1);
    s->cap *= 2;
}

void concat(String *s, String *o) {
    while (s->cap < s->len + o->len)
        doubleSize(s);
    for (int i = 0; i < o->len; i++)
        s->data[i + o->len] = o->data[i];
    s->len += o->len;
    s->data[s->len] = '\0';
}

void addChar(String *s, const char c) {
    if (s->len == s->cap)
        doubleSize(s);
    s->data[s->len++] = c;
    s->data[s->len] = '\0';
}

String *toLower(String *s) {
    String* newStr = (String*)new(STRING, 1, s->data);
    for (int i = 0; i < newStr->len; i++)
        if (newStr->data[i] < 'Z' && newStr->data[i] > 'A')
            newStr->data[i] += 0x20;
    return newStr;
}

bool equals(String* s, String* o) {
    if (s->len != o->len) return false;
    for (int i = 0; i < s->len; i++)
        if (s->data[i] != o->data[i])
            return false;
    return true;
}

