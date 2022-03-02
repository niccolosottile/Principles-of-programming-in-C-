#include <stdio.h>
#include <stdlib.h>



void redact_words(const char *text_filename, const char *redact_words_filename){

    FILE *text, *redact, *redacted_text; // Declaring file names to be used for r/w
    char buf_text[1024]; // Stores bytes to be read from text file
    char buf_redact[1024]; // Stores bytes to be read from redact file
    
    int nread;

    // Opening text and redacted text files for r
    text = fopen(text_filename, "r");
    redacted_text = fopen(redact_words_filename, "r");

    // Keep redacting text until no more is left (nread is 0)
    do {
        nread = fread(buf_text, 1, 1024, text);
        nread = fread(buf_redact, 1, 1024, redact);
        
    } while (nread > 0);

    fclose(text);
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
