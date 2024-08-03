

 #include <stdio.h>
#include <stdbool.h>
bool is_arithmetic_operator(char ch);
int main() {
    const char *test_input = "a + b - c * d / e";
    for (size_t i = 0; test_input[i] != '\0'; ++i) {
        char ch = test_input[i];
        if (is_arithmetic_operator(ch)) {
            printf("Operator detected: %c\n", ch);
        }
    }
return 0;
}
bool is_arithmetic_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}