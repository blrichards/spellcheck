#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "spellcheck.h"

int main(int argc, char *argv[]) {
    FILE* article;
    FILE* dictionary;
    switch (argc) {
        case 2:
            article = fopen(argv[1], "r");
            dictionary = fopen("words.txt", "r");
            break;
        case 3:
            article = fopen(argv[1], "r");
            dictionary = fopen(argv[2], "r");
            break;
        default:
            printf("Invalid argument set\n\nUsage:\tspellcheck <file to spell check> <optional: dictionary file>\n\n");
            return 0;
    }

    spellCheck(article, dictionary);
    fclose(article);
    fclose(dictionary);
}