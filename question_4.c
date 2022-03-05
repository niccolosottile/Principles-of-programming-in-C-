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
 * a buffer is passed as a parameter, along with its height and the indexes 
 * of the columns to be swapped, the function doesn't return anything as the 
 * buffer is modified.
 */
void swap_columns (char **table, int height, int first_column, int second_column) {

    // Storing copy of first column
    char *temp_column = (char *) malloc(height * sizeof(char));

    for (int i = 0; i < height; i++) {
        temp_column[i] = table[i][first_column];
    }

    // Copying second column into first column
    for (int i = 0; i < height; i++) {
        table[i][first_column] = table[i][second_column];
    }

    // Copying first column with temp into second column
    for (int i = 0; i < height; i++) {
        table[i][second_column] = temp_column[i];
    }

    free(temp_column);

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

    char **table = (char **) malloc(y * sizeof(char *)); // Allocating height y of cipher
     for(int i = 0; i < y; i++) {
         table[i] = (char*) malloc((key_length + 1) * sizeof(char)); // Allocating width key_length + 1 (for '\0' character)
    }

    // Writing key and message into result buffer
    strcpy(table[0], key_ptr);

    int q = 0;

    // Iterate over each row in height y
    for (int i = 1; i < y; i++) {
        
        // Iterate over each column
        for (int j = 0; j < (key_length + 1); j++) {

            // Adding null terminator to buffer
            if (j == key_length) {
                table[i][j] = '\0';
                continue;
            }

            // If end of message hasn't been reached copy it, else fill with X
            if (message_ptr[q] != '\0') {
                
                table[i][j] = message_ptr[q];
                q++;
            }
            else {
                table[i][j] = 'X';
            }

        }

    }

    // Sorting columns such that letters in keyword are alphabetically ordered
    int j = 0;
    
    // Move sorted side of key (starting at 0) until key is all sorted
    while (table[0][j] != '\0') {

        // Find preceding column in unsorted side of key
        int preceding_column = j;

        for (q = j + 1; table[0][q] != '\0'; q++) {

            if (table[0][preceding_column] > table[0][q]) {
                preceding_column = q;
            }

        }

        // Swap preceding column with first character in unsorted side of key
        swap_columns(table, y, j, preceding_column);

        j++;

    }

    // Initializing and allocating memory to result string
    *result = (char *) malloc((((y - 1) * key_length) + 1) * sizeof(char));

    

    // Read the ciphertext from table into result string
    q = 0;

    for (int i = 1; i < y; i++) {

        for(j = 0; table[i][j] != '\0'; j++) {      

            // Add letter to result string
            (*result)[q] = table[i][j];
            q++;

        }

    }

    (*result)[q + 1] = '\0'; // Adding null pointer to string

    free(message_ptr);
    free(key_ptr);
    free(table);

}

/* 
 *  A function which takes in a string and decrypts the contents using the
 *  key string which is obtained from the "key_filename" file. The decrypted 
 *  message should be returned using the "result" buffer, which you should 
 *  assume has not been initialised or any memory allocated to it. The function 
 *  should return true if decryption was successful, false if not.
 */
int decrypt_columnar (const char *message_filename, const char *key_filename, char **result) {

    char * key_ptr = read_string(key_filename); // Saving pointer to string
    int key_length = strlen(key_ptr); // Length of string

    char * message_ptr = read_string(message_filename);
    int message_length = strlen(message_ptr);

    // Condition where fail occurs (assuming X in encrypted message):

        // - given a key with set number of letters
        // - number of letters in message not divisible by key length

    if (message_length % key_length != 0) {

        free(message_ptr);
        free(key_ptr);

        return 0;
    }

    // Calculating height of cipher
    int y = 1 + message_length / key_length;

    char **table = (char **) malloc(y * sizeof(char *)); // Allocating height y of cipher
     for(int i = 0; i < y; i++) {
         table[i] = (char*) malloc((key_length + 1) * sizeof(char)); // Allocating width key_length + 1 (for '\0' character)
    }

    // Order the key in alphabetical order
    char *ordered_key_ptr = (char *) malloc((key_length + 1) * sizeof(char)); 
    strcpy(ordered_key_ptr, key_ptr);

    int i = 0;
    
    // Move sorted side of key (starting at 0) until key is all sorted
    while (ordered_key_ptr[i] != '\0') {

        // Find preceding letter in unsorted side of key
        int preceding_letter = i;

        for (int q = i + 1; ordered_key_ptr[q] != '\0'; q++) {

            if (ordered_key_ptr[preceding_letter] > ordered_key_ptr[q]) {
                preceding_letter = q;
            }

        }

        // Swap preceding letter with first character in unsorted side of key
        char temp_letter = ordered_key_ptr[i];
        ordered_key_ptr[i] = ordered_key_ptr[preceding_letter];
        ordered_key_ptr[preceding_letter] = temp_letter;

        i++;

    }

    // Insert key and encrypted message into table
    strcpy(table[0], ordered_key_ptr);
    
    int q = 0;

    // Iterate over each row in height y
    for (int i = 1; i < y; i++) {
        
        // Iterate over each column
        for (int j = 0; j < (key_length + 1); j++) {

            // Adding null terminator to buffer
            if (j == key_length) {
                table[i][j] = '\0';
                continue;
            }

            table[i][j] = message_ptr[q];
            q++;

        }

    }

    // Reorder table columns to form key

        // - Look at each letter in key to see which column it is in

        // - Swap each column to be in its correct position

    // Iterate over each column at keyword level
    for (int j = 0; table[0][j] != '\0'; j++) {

        // Iterate over each letter in original keyword
        for (q = 0; key_ptr[q] != '\0'; q++) {

            if (table[0][j] == key_ptr[q]) {
                swap_columns(table, y, j, q);
                break;
            }

        }

    }

    // Initializing and allocating memory to result string
    *result = (char *) malloc((message_length + 1) * sizeof(char));

    // Read decrypted message from table into result string
    q = 0;

    for (int i = 1; i < y; i++) {

        for(int j = 0; table[i][j] != '\0'; j++) {     

            // Add letter to result string
            (*result)[q] = table[i][j];
            q++;

        }

    }

    (*result)[q + 1] = '\0'; // Adding null pointer to string

    free(message_ptr);
    free(key_ptr);
    free(table);
    free(ordered_key_ptr);

    return 1;

}

int main () {

    const char *message_file = "message.txt";
    const char *key_file = "keyword.txt";
    char *result;

    decrypt_columnar(message_file, key_file, &result);

    printf("%s\n", result);

    return 0;
}