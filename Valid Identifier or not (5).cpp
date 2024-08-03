#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_ID_LEN 31 // Restricting the length of identifiers

// Function prototypes
int isValidIdentifier(const char *identifier);

int main() {
    // Sample identifiers to test
    const char *testIdentifiers[] = {
        "validIdentifier1",
        "_validIdentifier",
        "1InvalidIdentifier",
        "anotherValidIdentifier",
        "aVeryLongIdentifierThatExceedsTheMaximumLength",
        "valid_Identifier",
        "invalid-identifier",
        NULL
    };

    for (int i = 0; testIdentifiers[i] != NULL; i++) {
        printf("Identifier: %s\n", testIdentifiers[i]);
        if (isValidIdentifier(testIdentifiers[i])) {
            printf("Status: Valid\n");
        } else {
            printf("Status: Invalid\n");
        }
        printf("\n");
    }

    return 0;
}

int isValidIdentifier(const char *identifier) {
    // Check if the identifier is empty or too long
    if (strlen(identifier) == 0 || strlen(identifier) > MAX_ID_LEN) {
        return 0; // Invalid
    }

    // Check if the first character is a letter or underscore
    if (!(isalpha(identifier[0]) || identifier[0] == '_')) {
        return 0; // Invalid
    }

    // Check the remaining characters
    for (int i = 1; identifier[i] != '\0'; i++) {
        if (!(isalnum(identifier[i]) || identifier[i] == '_')) {
            return 0; // Invalid
        }
    }

    return 1; // Valid
}