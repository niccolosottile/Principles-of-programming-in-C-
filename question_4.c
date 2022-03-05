#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* 
 *  A function which takes in a filename and returns the contents as a string, 
 *  with all non-alphanumeric (i.e., not A-Z, a-z, or 0-9) removed and characters
 *  converted to uppercase.
 */
char *read_string (const char *filename) {

    FILE *text; // Declaring file name to read message from

    text = fopen(filename, "r");

    char *clean_text = (char *) malloc(1024); // Allocating memory to store message as string

    fgets(clean_text, 1024, text); // Reading message from file
    clean_text = strtok(clean_text, "\n"); // Getting rid of empty line

    // Iterating over each character
    int i, j;

    for (i = 0; clean_text[i] != '\0'; i++) {

        // If character is not any of this cases, remove it
        if (! ((clean_text[i] >= 'A' && clean_text[i] <= 'Z') || (clean_text[i] >= 'a' && clean_text[i] <= 'z') || (clean_text[i] >= 0 && clean_text[i] <= 9) || clean_text[i] == '\0')) {

            // Shift all characters to overwrite the one to be removed
            for (j = i; clean_text[j] != '\0'; j++) {
                clean_text[j] = clean_text[j + 1];
            }

            clean_text[j] = '\0'; // Mark new end of string

        }

        // Convert each valid character to uppercase
        clean_text[i] = toupper(clean_text[i]);
        
    }

    return clean_text;

}

/*
 * A function used to swap two columns in the cipher table by column number
 * a buffer is passed as a parameter, along with the indexes of the columns
 * to be swapped, the function doesn't return anything as the buffer is modified
 */
void swap_columns (char **result, int first_column, int second_column) {

    

}

/* 
 *  A function which takes in a filename and encrypts the contents using the
 *  key string which is obtained from the "key_filename" file. The encrypted 
 *  message should be returned using the "result" buffer, which you should 
 *  assume has not been initialised or any memory allocated to it.
 */
void encrypt_columnar (const char *message_filename, const char *key_filename, char **result) {

    char * key_ptr = read_string(key_filename); // Saving pointer to string
    int key_length = strlen(key_ptr); // Length of string

    char * message_ptr = read_string(message_filename);
    int message_length = strlen(message_ptr);

    // Calculating height of cipher
    int y = 1;

    if (message_length % key_length == 0) {
        y += message_length / key_length;
    }
    else {
        y += (message_length / key_length) + 1;
    }

    result = (char **) malloc(y * sizeof(char *)); // Allocating height y of cipher
     for(int i = 0; i < y; i++) {
         result[i] = (char*) malloc((key_length + 1) * sizeof(char)); // Allocating width key_length + 1 (for '\0' character)
    }

    // Writing key and message into result buffer
    strcpy(result[0], key_ptr);

    int q = 0;

    // Iterate over each row in height y
    for (int i = 1; i < y; i++) {
        
        // Iterate over each column
        for (int j = 0; j < (key_length + 1); j++) {

            // Adding null terminator to buffer
            if (j == key_length) {
                result[i][j] = '\0';
                continue;
            }

            // If end of message hasn't been reached copy it, else fill with X
            if (message_ptr[q] != '\0') {
                
                result[i][j] = message_ptr[q];
                q++;
            }
            else {
                result[i][j] = 'X';
            }

        }

    }

    // Sorting columns such that letters in keyword are alphabetically ordered
    j = 0;
    
    // Move sorted side of key (starting at 0) until key is all sorted
    while (result[0][j] != '\0') {

        // Find preceding column in unsorted side of key
        int preceding_column = 0;

        for (q = 0; result[0][q] != '\0'; q++) {

            if (result[0][preceding_column] > result[0][q]) {
                preceding_column = q;
            }

        }

        // Swap preceding column with first character in unsorted side of key
        swap_columns(result, j, preceding_column);

        j++;

    }

    for (int i = 0; i < y; i++) {
        printf("%s\n", result[i]);
    }

}

/* 
 *  A function which takes in a string and decrypts the contents using the
 *  key string which is obtained from the "key_filename" file. The decrypted 
 *  message should be returned using the "result" buffer, which you should 
 *  assume has not been initialised or any memory allocated to it. The function 
 *  should return true if decryption was successful, false if not.
 */
int decrypt_columnar (const char *message_filename, const char *key_filename, char **result) {
    return 1;   
}

int main () {

    const char *message_file = "message.txt";
    const char *key_file = "keyword.txt";
    char **result;

    encrypt_columnar(message_file, key_file, result);

    return 0;
}