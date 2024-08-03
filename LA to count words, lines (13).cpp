#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void lexicalAnalyzer(const char *input, int *charCount, int *wordCount, int *lineCount) {
    bool inWord = false;

    while (*input != '\0') {
        (*charCount)++;

        if (*input == '\n') {
            (*lineCount)++;
        }

        if (isspace(*input)) {
            inWord = false;
        } else {
            if (!inWord) {
                (*wordCount)++;
                inWord = true;
            }
        }

        input++;
    }

    // To count the last line if the input does not end with a newline
    if (*input == '\0' && *(input - 1) != '\n') {
        (*lineCount)++;
    }
}

int main() {
    const char *input = 
        "Hello, this is a sample text.\n"
        "It spans multiple lines and words.\n"
        "Let's count the characters, words, and lines in this program.\n";
    
    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;

    lexicalAnalyzer(input, &charCount, &wordCount, &lineCount);

    printf("Number of characters: %d\n", charCount);
    printf("Number of words: %d\n", wordCount);
    printf("Number of lines: %d\n", lineCount);

    return 0;
}
