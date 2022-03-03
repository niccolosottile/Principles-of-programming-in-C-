#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void redact_words(const char *text_filename, const char *redact_words_filename){

    FILE *text, *redact_text, *redacted_text; // Declaring file names to be used for r/w

    // Opening text, redact and redacted text files for r/w
    text = fopen(text_filename, "r");
    redact_text = fopen(redact_words_filename, "r");
    redacted_text = fopen("result.txt", "w");

    // Process redact to obtain an array containing the words to be redacted
    char redact[1024];
    fread(redact, 1, 1024, redact_text);

    char delimiter[] = ", "; // Use spaces and commas as delimiters
    char redact_words[1024][25]; // Stores all words to be redacted

    // Separate each word to be redacted
    char *ptr = strtok(redact, delimiter);

    int i = 0;

    while (ptr != NULL) {

        strcpy(redact_words[i], ptr); // Add word to array of words
        ptr = strtok(NULL, delimiter); // Get next word using strtok with delimiter
        i++;

    }

    // Use malloc to allocate memory for text_str
    char *text_str = (char *) malloc(1024);

    // Read text file line by line and process each line
    while (fgets(text_str, 1024, text)) {
            
            printf("%s", text_str);

            // Store line in string 

            // Split string by words


        }
    
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

// Redact a file given a set of redactable words (separated by commas) 
// Replace a redacted letter with a star and output it to a file called "result.txt"
// Read from input file and extract a set of words (using spaces)
// Read from redacted words file and extract redacted words (using commas)
// If any word matches with a redacted word, substitute with stars, copy into "result.txt"
