#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

const char *input;
int pos;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool parseDigit() {
    if (isDigit(input[pos])) {
        pos++;
        return true;
    }
    return false;
}

bool parseNumber() {
    int startPos = pos;
    if (parseDigit()) {
        while (parseDigit());
        return true;
    }
    pos = startPos;
    return false;
}

bool parseExpression(); // Forward declaration

bool parseFactor() {
    int startPos = pos;
    if (parseNumber()) {
        return true;
    }
    pos = startPos;
    if (input[pos] == '(') {
        pos++;
        if (parseExpression()) {
            if (input[pos] == ')') {
                pos++;
                return true;
            }
        }
    }
    pos = startPos;
    return false;
}

bool parseTerm() {
    if (!parseFactor()) {
        return false;
    }
    while (input[pos] == '*' || input[pos] == '/') {
        pos++;
        if (!parseFactor()) {
            return false;
        }
    }
    return true;
}

bool parseExpression() {
    if (!parseTerm()) {
        return false;
    }
    while (input[pos] == '+' || input[pos] == '-') {
        pos++;
        if (!parseTerm()) {
            return false;
        }
    }
    return true;
}

bool checkGrammar(const char *str) {
    input = str;
    pos = 0;
    if (parseExpression() && input[pos] == '\0') {
        return true;
    }
    return false;
}

int main() {
    const char *test1 = "3 + 5 * (2 - 8)";
    const char *test2 = "3 + * 5";
    const char *test3 = "3 + (5 * 2";
    const char *test4 = "42";
    
    printf("Checking '%s': %s\n", test1, checkGrammar(test1) ? "Valid" : "Invalid");
    printf("Checking '%s': %s\n", test2, checkGrammar(test2) ? "Valid" : "Invalid");
    printf("Checking '%s': %s\n", test3, checkGrammar(test3) ? "Valid" : "Invalid");
    printf("Checking '%s': %s\n", test4, checkGrammar(test4) ? "Valid" : "Invalid");
    
    return 0;
}


