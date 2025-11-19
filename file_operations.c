/*------------------------------------------------------
* Filename: [file_operations.c]
* Description: [This program]
* Author: [Oron Bar Hillel]
-------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_LINE 100


void check_null(FILE *fp){
    if(fp == NULL){
        printf("The file was not found!\n");
        return;
    }
}

void print_file(char file_name[]){
    FILE *fp = NULL;
    char line[MAX_SIZE_LINE];

    fp = fopen(file_name, "r");
    check_null(fp);

    printf("The file content is:\n");
    // Scanning and printing each line until reaching EOF
    while(fgets(line, sizeof(line), fp) != NULL){
        printf("%s\n", line);
    }  
    fclose(fp); 
}

void input_to_output(char file1[], char file2[]){
    char character = '\0';
    FILE * fp_in = NULL;
    FILE * fp_out = NULL;

    //Opening the files and making sure they are opened correctly
    fp_in = fopen(file1, "r");
    check_null(fp_in);

    fp_out = fopen(file2, "w");
    check_null(fp_out);

    //Taking each charecter from the input file until EOF and putting each one in the output file.
    while((character = fgetc(fp_in)) != EOF){
        fputc(character, fp_out);
    }
    //closing the files after usage
    fclose(fp_in);
    fclose(fp_out);
}

void num_lines_words_chars(char file_name[]){
    FILE *fp = NULL;
    char line[MAX_SIZE_LINE] = {'\0'};
    char space = ' ';

    int line_count = 0;
    int word_count = 0;
    int char_count = 0;

    fp = fopen(file_name, "r");
    check_null(fp);

    while(fgets(line, sizeof(line), fp) != NULL){
        ++line_count;
        char_count += strlen(line);

        //words count!!
        for(int i = 0; i < strlen(line); ++i){
            if(line[i + 1] == space && line[i] != space){
                ++word_count;
            }
        }
        ++word_count; //always one more word then spaces between

        //if by mistake the line is ended by a space, it is reduced!
        if(line[strlen(line) - 2] == space){
            --word_count;;
        }

    } 
    printf("The number of lines in the file is:%d \n", line_count);
    printf("The number of words in the file is: %d \n", word_count);
    printf("The number of characters in the file is: %d\n", char_count);
    fclose(fp);

}

void file_delete_line(char file[], int number_line){
    // Setting and defining vriables for the function
    FILE * fp = NULL;
    FILE * fp_temp = NULL; //A temp file we add so we can make changes in the file whitout changing the original file

    char temp[] = "temp file.txt";
    fp = fopen(file, "r+");
    check_null(fp);

    fp_temp = fopen(temp, "w");
    check_null(fp_temp);

    char line[100] = {'\0'};
    int counter_lines = 0;
    
    while(fgets(line, sizeof(line), fp) != NULL){
        ++counter_lines;
        if(counter_lines != number_line){
            fputs(line, fp_temp);
        }
    }
    //Closing the files first so they can be reopened in the input_to_output function
    fclose(fp_temp);
    fclose(fp);
    input_to_output(temp, file);
}

void num_string_in_file(char file_name[], char string[]){
    FILE *fp = NULL;
    char line[MAX_SIZE_LINE] = {'\0'};

    int counter = 0;
    int flag = 0;

    fp = fopen(file_name, "r");
    check_null(fp);

    while(fgets(line, sizeof(line), fp) != NULL){
        //check at each line!
        for(int i = 0; i < strlen(line); ++i){
            //loking for the first char in the string to be in the file
            flag = 0;
            if(line[i] == string[0]){
                for(int j = 0; j < strlen(string); ++j){
                    if(line[i + j] = string[j]){
                        flag = 1;
                    }else{
                        flag = 0;
                    }
                }
            }
            if(flag == 1){
                ++counter;
            }
        }

    }
    printf("The number of %s in the file is:%d", string, counter); 
}


int main() {
    //Setting the variables
    char file_name[] = "hello world.txt";
    char string[] = "world";

    print_file(file_name);

    num_lines_words_chars(file_name);

    //file_delete_line(file_name, 2);

    num_string_in_file(file_name, string);

    return 0;
}