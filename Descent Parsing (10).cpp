#include <stdio.h>
#include <ctype.h>

char *input;
char token;

// Function prototypes
void E();
void T();
void F();
void advance();
void error(const char *message);

void advance() {
    token = *input++;
}

void error(const char *message) {
    printf("Error: %s\n", message);
    exit(1);
}

// E -> T | E + T
void E() {
    T();
    while (token == '+') {
        advance();
        T();
    }
}

// T -> F | T * F
void T() {
    F();
    while (token == '*') {
        advance();
        F();
    }
}

// F -> ( E ) | number
void F() {
    if (token == '(') {
        advance();
        E();
        if (token == ')') {
            advance();
        } else {
            error("Missing closing parenthesis");
        }
    } else if (isdigit(token)) {
        while (isdigit(token)) {
            advance();
        }
    } else {
        error("Unexpected character");
    }
}
int main() {
    // Example input expression
    char expression[] = "3+5*(2+8)";
    input = expression;
    advance();

    E();

    if (token == '\0') {
        printf("Parsing successful!\n");
    } else {
        error("Unexpected input after parsing");
    }
    return 0;
}
