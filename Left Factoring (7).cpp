#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to check if the prefix is common
bool has_common_prefix(const char *prod1, const char *prod2, char *prefix) {
    int len1 = strlen(prod1);
    int len2 = strlen(prod2);
    int i = 0;

    // Find common prefix
    while (i < len1 && i < len2 && prod1[i] == prod2[i]) {
        i++;
    }

    if (i > 0) {
        strncpy(prefix, prod1, i);
        prefix[i] = '\0';
        return true;
    }

    return false;
}

// Function to perform left factoring
void left_factoring(const char *non_terminal, const char *prod1, const char *prod2) {
    char prefix[100];
    char rest1[100], rest2[100];

    // Check and extract common prefix
    if (has_common_prefix(prod1, prod2, prefix)) {
        // Extract the rest of the productions
        strcpy(rest1, prod1 + strlen(prefix));
        strcpy(rest2, prod2 + strlen(prefix));

        // Print the refactored grammar
        printf("Original Productions:\n");
        printf("%s ? %s | %s\n", non_terminal, prod1, prod2);

        printf("Refactored Productions:\n");
        printf("%s ? %s%s'\n", non_terminal, prefix, non_terminal);
        printf("%s' ? %s | %s\n", non_terminal, rest1, rest2);
    } else {
        printf("No common prefix found for left factoring.\n");
    }
}

int main() {
    char non_terminal[50];
    char prod1[100];
    char prod2[100];

    // Read input from user
    printf("Enter the non-terminal: ");
    scanf("%s", non_terminal);
    printf("Enter the first production: ");
    scanf("%s", prod1);
    printf("Enter the second production: ");
    scanf("%s", prod2);

    // Perform left factoring
    left_factoring(non_terminal, prod1, prod2);

    return 0;
}