#include <stdio.h>
#include <stdlib.h>

int main() {
    // Hardcoded input as a string
    const char *input = "int main() {\n"
                        "    int a = 5; // Variable a\n"
                        "    /* This is\n"
                        "       a multi-line\n"
                        "       comment */\n"
                        "    printf(\"Hello, World!\\n\");\n"
                        "    return 0;\n"
                        "}";

    int whitespaceCount = 0;
    int newlineCount = 0;

    // Iterate through each character in the input string
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ' || input[i] == '\t') {
            whitespaceCount++;
        }
        if (input[i] == '\n') {
            newlineCount++;
        }
    }
    printf("Number of whitespaces: %d\n", whitespaceCount);
    printf("Number of newlines: %d\n", newlineCount);

    return 0;
}
