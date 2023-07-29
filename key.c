#include "key.h"
#include <stdlib.h>
#include <stdio.h>

int generate_key(char *name){
    //generate a string of random characters with length 26 and every char is used only once
    char key[26];
    for(int i = 0; i < 26; i++){
        key[i] = 'a' + i;
    }
    
    for(int i = 0; i < 26; i++){
        int j = rand() % 26;
        char temp = key[i];
        key[i] = key[j];
        key[j] = temp;
    }


    FILE *fp;
    fp = fopen(name,"w");
    if(fp == NULL){
        return 1;
    }
    fprintf(fp, "%s", key);
    fclose(fp);
    return 0;
}