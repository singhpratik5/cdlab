#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>


int main(){
    FILE *file = fopen("input.c",'r');
    if(!file){
        printf("Error opening file\n");
        return 1;
    }

    char word[100];
    char *names[1000]; //store names
    int name_count;

    while(fscanf(file, "%s" ,word)!= EOF){
        if(!is_keyword(word) && isalpha(word[0])){
            names[name_count] = strdup(word);
            name_count++;
        }
    }
/* hello*/
    fclose(file);

    printf("Identifiers in alphabetical order :\n");
    for(int i= 0;i<name_count;i++){
        printf("%s\n",names[i]);
        free(names[i]);
    }
    return 0;
}
