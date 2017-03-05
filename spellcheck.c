/*
 * SpellCheck
 *
 * @author: Ben Richards
 */

#include <stdio.h>
#include <stdbool.h>
#include "types.h"

HashMap *dict;

/* @func: loadDict
 * @brief: load cDict with dictionary words specified in spellCheck
 * @input: long String of words separated by '\n'
 * @summary: iterates through dictionary String and adds each word to the
 *           static hash table, cDict
 */
void loadDict(FILE *dictionary) {
    char c = (char)fgetc(dictionary);
    while (c != EOF) {
        String *newWord = new(STRING, 1, "");

        while (c != '\n' && c != EOF) {
            addChar(newWord, c);
            c = (char) fgetc(dictionary);
        }
        put(dict, newWord, true);

        delete(STRING, newWord);
        c = (char) fgetc(dictionary);
    }
}

/* @func: spellCheck
 * @brief: basic spell checker
 * @input: article String, dictionary String of words separated by '\n'
 * @output (to console): prints any word that is misspelled
 */
void spellCheck(FILE *article, FILE *dictionary) {
    dict = new(HASHMAP, 0);
    loadDict(dictionary);

    bool nextCapital = true;
    bool reCapitalize = true;

    // iterate through article by word checking to see if each one is in the
    // dictionary
    char c = (char)fgetc(article);
    while (c != EOF) {
        String *word = new(STRING, 1, "");

        while (c != ' ' && c != '\n' && c != EOF) {
            if (c == '.' || c == '?' || c == '!') {
                nextCapital = true;
                break;
            } else if (nextCapital && (c < 'Z' && c > 'A')) {
                c += 0x20;
                nextCapital = false;
                reCapitalize = true;
            }

            addChar(word, c);
            c = (char) fgetc(article);
        }

        bool correct = contains(dict, word);

        if (reCapitalize) {
            capitalize(word);
            reCapitalize = false;
        }

        // print the word in bold if it's misspelled
        if (correct)
            printf("%s", word->data);
        else {
            toUpper(word);
            printf("%s", word->data);
        }



        putchar(c);

        delete(STRING, word);
        c = (char) fgetc(article);
    }

    delete(HASHMAP, dict);
}
