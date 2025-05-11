#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const char keywords[36][10] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", 
    "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", 
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", 
    "void", "volatile", "while"
};
#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

int is_keyword(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int cmpstr(const void *a, const void *b) {
    return (strcmp(*(const char **)a, *(const char **)b));
}

int main() {
    FILE *file = fopen("input.c","r");

    char word[100];
    int name_count = 0;
    char *names[1000];

    int in_comment = 0;
    int in_string = 0;

    while(fscanf(file,"%s",word)!= EOF){
        if(strstr(word,"//")){
            while(fgetc(file)!='\n' && !feof(file)){
                
            }
            continue;
        }

        if(strstr(word,"*/")){
            in_comment = 1;
        }

        if(in_comment){
            if(strstr(word,"/*")){
                in_comment = 0;
            }
        }

        if(strchr(word,'"')){
            in_string = !in_string;
            continue;
        }
        if(in_string){
            continue;
        }

        if(!is_keyword(word) && isalpha(word[0])){
            names[name_count] = strdup(word);
            name_count++;
        }
    }

    for(int i =0;i<sizeof(names);i++){
        printf("%s\n",names[i]);
    }

}
