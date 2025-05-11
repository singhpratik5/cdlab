#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char keywords[32][10] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

#define size (sizeof(keywords)/sizeof(keywords[0]))

int is_keyword(char *word){
    for(int i = 0;i < size;i++){
        if(strcmp(word,keywords[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int compare(const void*a,const void*b){
    return (strcmp(*(const char **)a,*(const char **)b));
}

int main() {
    FILE *file = fopen("input.c", "r");
    if (!file) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    char word[100];
    char *names[1000];  
    int name_count = 0;
    int in_comment = 0;
    int in_string = 0;

    while (fscanf(file, "%s", word) != EOF) {
        if (strstr(word, "//")) {
            while (fgetc(file) != '\n' && !feof(file)) {
                // Keep reading characters until the end of the line
            }
            continue;
        }

        if (strstr(word, "/*")) {
            in_comment = 1;  
        }
        if (in_comment) {
            if (strstr(word, "*/")) {
                in_comment = 0;  
            }
            continue;
        }

        if (strchr(word, '"')) {
            in_string = !in_string;  
            continue;
        }
        if (in_string) {
            continue;  // Skip words inside string literals
        }

        if (!is_keyword(word) && isalpha(word[0])) {
            // Copy valid names to the names array
            names[name_count] = strdup(word);
            name_count++;
        }
    }

    fclose(file);

    qsort(names,name_count,sizeof(char *),compare);

    for(int i = 0;i < name_count;i++){
        printf("%s\n",names[i]);
    }

    return 0;
}