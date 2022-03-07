#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void redact_words(const char *text_filename, const char *redact_words_filename){

    FILE *text, *redact_text, *redacted_text; // Declaring file names to be used for r/w

    // Opening text, redact and redacted text files for r/w
    text = fopen(text_filename, "r");
    redact_text = fopen(redact_words_filename, "r");
    redacted_text = fopen("result.txt", "w");

    // Process redact to obtain an array containing the words to be redacted
    char redact[1024];
    fgets(redact, 1024, redact_text);

    char redact_words[1024][25]; // Stores all words to be redacted

    // Separate each word to be redacted
    char *ptr = strtok(redact, ", ");

    int i = 0;

    while (ptr != NULL) {

        strcpy(redact_words[i], ptr); // Add word to array of words
        ptr = strtok(NULL, ", \n"); // Get next word using strtok with delimiter
        i++;

    }

    // Use malloc to allocate memory for text_str
    char *text_str = (char *) malloc(1024);
    char *compare_word_ptr;

    // Read text file line by line and process each line
    while (fgets(text_str, 1024, text)) {
            
            // Separate each word from text
            char *word_ptr = strtok(text_str, " \n");
            compare_word_ptr = (char *) malloc((strlen(word_ptr) + 1) * sizeof(char));
            char *temp_word_ptr;

            i = 0;

            while (word_ptr != NULL) {

                strcpy(compare_word_ptr, word_ptr);

                // Remove any non-alphabetic character for comparison
                for (int j = 0; compare_word_ptr[j] != '\0'; j++) {

                    if(!isalpha((unsigned char) compare_word_ptr[j])) {
                        
                        // Shift all letters to remove current one
                        int q = j;
    
                        while (compare_word_ptr[q] != '\0') {

                            compare_word_ptr[q] = compare_word_ptr[q + 1];
                            q++;
                        }

                    }

                }

                // Compare word with redacted words
                int j = 0;
                bool found = false;

                while (redact_words[j][0] != '\0') {

                    // strcasecmp returns 0 if they are the same, 1 otherwise. It isn't case sensitive.
                    if (strcasecmp(compare_word_ptr, redact_words[j]) == 0) {
                        found = true;
                        break;
                    }

                    j++;
                }

                // Write word into result file
                if (found) {

                    // Substitute word with stars *
                    for (int q = 0; q < strlen(word_ptr); q++) {
                        
                        if (isalpha(word_ptr[q])) {
                            word_ptr[q] = '*';
                        }

                    }
                    
                }
                
                // Get next word and save it in temp location
                temp_word_ptr = strtok(NULL, " \n");

                // Check if next word will be NULL or not (space or not)
                if (temp_word_ptr != NULL) {
                    fprintf(redacted_text, "%s ", word_ptr);
                }
                else {
                    fprintf(redacted_text, "%s\n", word_ptr);
                }

                // Assign temp word to current word
                word_ptr = temp_word_ptr;
                i++;

            }

        }
    
    // Freeing dynamic memory for text string
    free(text_str);
    free(compare_word_ptr);
    text_str = NULL;

    // Closing all the files after use for r/w
    fclose(text);
    fclose(redact_text);
    fclose(redacted_text);

}

int main () {

    const char *input_file = "check_in.txt";
    const char *redact_file = "check_redact.txt";

    redact_words(input_file, redact_file);

    char line[1024];
    FILE* file = fopen("result.txt", "r");

    if(!file){
        printf("Unable to open result.txt\n");
    }
    else{
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }

    return 0;
}