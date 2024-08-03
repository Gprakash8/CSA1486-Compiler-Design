#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 100

void removeRedundantSpaces(char *source, char *destination) {
    int i = 0, j = 0;
    int spaceFound = 0;

    while (source[i] != '\0') {
        if (isspace(source[i])) {
            if (!spaceFound) {
                destination[j++] = ' ';
                spaceFound = 1;
            }
        } else {
            destination[j++] = source[i];
            spaceFound = 0;
        }
        i++;
    }
    destination[j] = '\0';
}

void lexicalAnalyzer(char *input) {
    char token[MAX_IDENTIFIER_LENGTH];
    int i = 0, j = 0;

    while (input[i] != '\0') {
        if (input[i] == '/' && input[i+1] == '/') {
            // Single-line comment
            printf("Comment: //");
            i += 2;
            while (input[i] != '\n' && input[i] != '\0') {
                printf("%c", input[i]);
                i++;
            }
            printf("\n");
        } else if (input[i] == '/' && input[i+1] == '*') {
            // Multi-line comment
            printf("Comment: /*");
            i += 2;
            while (!(input[i] == '*' && input[i+1] == '/') && input[i] != '\0') {
                printf("%c", input[i]);
                i++;
            }
            if (input[i] != '\0') {
                printf("*/\n");
                i += 2;
            }
        } else if (isalpha(input[i])) {
            // Identifier
            while (isalnum(input[i]) || input[i] == '_') {
                if (j < MAX_IDENTIFIER_LENGTH - 1) {
                    token[j++] = input[i];
                }
                i++;
            }
            token[j] = '\0';
            printf("Identifier: %s\n", token);
            j = 0;
        } else if (isdigit(input[i])) {
            // Constant
            while (isdigit(input[i])) {
                token[j++] = input[i];
                i++;
            }
            token[j] = '\0';
            printf("Constant: %s\n", token);
            j = 0;
        } else if (strchr("+-*/=%", input[i])) {
            // Operator
            token[0] = input[i];
            token[1] = '\0';
            printf("Operator: %s\n", token);
            i++;
        } else {
            i++;
        }
    }
}

int main() {
    char sourceCode[] = "int main() { int a = 10; /* multi-line \n comment */ a = a + 2; // single-line comment\n return a; }";
    char cleanedSourceCode[1000];

    removeRedundantSpaces(sourceCode, cleanedSourceCode);

    lexicalAnalyzer(cleanedSourceCode);

    return 0;
}
