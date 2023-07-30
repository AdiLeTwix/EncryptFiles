#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "encrypt.h"
#include "key.h"

#define usage fprintf(stderr, "Usage: %s [-k key_file] [-m message] [-i input_file] [-o output_file] [-e] [-d] [-g]\n", argv[0]); exit(EXIT_FAILURE);

enum mode{
    ENCRYPT,
    DECRYPT,
    GENERATE_KEY,
    NONE
};

void printhelp(){
    printf("Usage: ./enc [-k key_file] [-m message] [-i input_file] [-o output_file] [-e] [-d] [-g]\n");
    printf("Options:\n");
    printf("  -k key_file: specify the key file\n");
    printf("  -m message: specify the message\n");
    printf("  -i input_file: specify the input file\n");
    printf("  -o output_file: specify the output file\n");
    printf("  -e: encrypt the input file with the key file\n");
    printf("  -d: decrypt the input file with the key file\n");
    printf("  -g: generate a key file\n");
    printf("  -h: print this help\n");
    exit(EXIT_SUCCESS);
}


int main(int argc, char **argv) {

    int opt;
    char *key_file = NULL;
    char *input_file = NULL;
    char *output_file = NULL;
    char *message = NULL;
    enum mode current_mode = NONE;

    while ((opt = getopt(argc, argv, "k:m:i:o:edgh")) != -1) {
        switch (opt) {
            case 'k':
                key_file = optarg;
                break;
            case 'm':
                message = optarg;
                break;
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'e':
                current_mode = ENCRYPT;
                break;
            case 'd':
                current_mode = DECRYPT;
                break;
            case 'g':
                current_mode = GENERATE_KEY;
                break;
            case 'h':
                printhelp();
                break;
            default:
                usage;
        }
    }

    if(current_mode == ENCRYPT){
        if(key_file == NULL || (input_file == NULL && message == NULL) || (input_file != NULL && message != NULL)){
            usage;
        }
        printf("Encrypt message with %s...\n",key_file);
        return encrypt_msg(message, input_file, key_file, output_file);
    }

    if(current_mode == GENERATE_KEY){
        if(key_file == NULL){
            usage;
        }
        printf("Generate key: %s...\n",key_file);
        srand(time(NULL));
        return generate_key(key_file);
    }

    if(current_mode == DECRYPT){
        if(key_file == NULL || input_file == NULL){
            usage;
        }
        printf("Decrypt: %s with %s...\n",input_file,key_file);
        return decrypt(input_file, key_file); //todo output file
    }

    usage;

}

/*
int old_main(int argc, char **argv) {
    if(argc == 4){
        printf("Encrypt: %s with %s in %s...\n",argv[1],argv[2], argv[3]);
        return encrypt(argv[1], argv[2], argv[3]);
    }

    if(argc == 2){
        printf("Generate key: %s...\n",argv[1]);
        srand(time(NULL));
        return generate_key(argv[1]);
    }

    if(argc == 3){
        printf("Decrypt: %s with %s...\n",argv[1],argv[2]);
        return decrypt(argv[1], argv[2]);
    }

    printf("nothing");
    return EXIT_FAILURE;
}
*/