#include "encrypt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 100


int read_msg(char *path, char **message){
    FILE *fp;
    fp = fopen(path,"r");
    if(fp == NULL){
        printf("Error: cannot open message file\n");
        return 1;
    }
    char buffer[MAX];
    size_t content_size = 0; //todo: optimize this
    
    while(fgets(buffer, MAX, fp) != NULL){
        size_t len = strlen(buffer);
        *message = realloc(*message, content_size + len + 1);
        if(*message == NULL){
            printf("Error: cannot allocate memory\n");
            return 1;
        }
        strcpy(*message + content_size, buffer);
        content_size += len;
    }

    fclose(fp);
    return 0;
}

int encode(char *message, char *path_key){
    FILE *fp;
    fp = fopen(path_key,"r");
    if(fp == NULL){
        return 1;
    }
    char key[26];
    fscanf(fp, "%s", key);
    fclose(fp);
    for(int i = 0; message[i] != '\0'; i++){
        if(message[i] >= 'a' && message[i] <= 'z'){
            message[i] = key[message[i] - 'a'];
        }
    }
    return 0;
}


int encrypt_msg(char *message, char *in_path, char *path_key, char *out_path){
    
    if(message == NULL){
        if(read_msg(in_path, &message) != 0){
            printf("Error: cannot read message\n");
            return 1;
        }
    }
    
    if(encode(message, path_key) != 0){
        printf("Error: cannot encode message\n");
        return 1;
    }


    if(out_path != NULL){
    FILE *fp;
    fp = fopen(out_path,"w");

    if(fp == NULL){
        printf("Error: cannot open file\n");
        return 1;
    }

    fprintf(fp, "%s", message);
    fclose(fp);
    }
        
    printf("Encoded message : %s\n", message);
    
    return 0;
}

int decrypt(char *path_message, char *path_key){
    char* message = NULL;

    if(read_msg(path_message, &message) != 0){
        printf("Error: cannot read message\n");
        return 1;
    }

    FILE *fp;
    fp = fopen(path_key,"r");
    if(fp == NULL){
        printf("Error: cannot open key file\n");
        return 1;
    }
    char key[26];
    fscanf(fp, "%s", key);
    fclose(fp);

    size_t content_size = strlen(message);
    for(size_t i = 0; i < content_size; i++){
        if(message[i] >= 'a' && message[i] <= 'z'){
            for(int j = 0; j < 26; j++){
                if(key[j] == message[i]){
                    message[i] = 'a' + j;
                    break;
                }
            }
        }
    }
    printf("%s\n", message);
    return 0;
}