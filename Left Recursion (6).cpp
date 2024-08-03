#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to eliminate left recursion
void eliminate_left_recursion(const char *non_terminal, const char *prod1, const char *prod2) {
    printf("Original Production Rules:\n");
    printf("%s → %s | %s\n", non_terminal, prod1, prod2);

    // New non-terminal for recursion removal
    printf("Transformed Production Rules:\n");
    printf("%s → %s%s'\n", non_terminal, prod2, non_terminal);
    printf("%s' → %s%s' | ε\n", non_terminal, prod1, non_terminal);
}

int main() {
    char non_terminal[50];
    char prod1[100];
    char prod2[100];

    // Read the input from user
    printf("Enter the non-terminal: ");
    scanf("%s", non_terminal);
    printf("Enter the production with left recursion (e.g., Aα): ");
    scanf("%s", prod1);
    printf("Enter the production without left recursion (e.g., β): ");
    scanf("%s", prod2);

    // Call the function to eliminate left recursion
    eliminate_left_recursion(non_terminal, prod1, prod2);

    return 0;
}