#include <stdio.h>
#include <math.h>

int main() {
    // Example expression: 3 + 6 * (5 + 3) - 4 / 2 ^ 2
    // The expression contains: Parentheses, Exponentiation, Multiplication, Division, Addition, Subtraction

    // Breaking down the expression step by step
    int a = 3;
    int b = 6;
    int c = 5;
    int d = 3;
    int e = 4;
    int f = 2;

    // 1. Evaluate Parentheses
    int parentheses_result = c + d; // (5 + 3) = 8

    // 2. Evaluate Exponentiation
    int exponentiation_result = pow(f, 2); // 2 ^ 2 = 4

    // 3. Evaluate Multiplication and Division from left to right
    int multiplication_result = b * parentheses_result; // 6 * 8 = 48
    int division_result = e / exponentiation_result; // 4 / 4 = 1

    // 4. Evaluate Addition and Subtraction from left to right
    int addition_result = a + multiplication_result; // 3 + 48 = 51
    int final_result = addition_result - division_result; // 51 - 1 = 50

    printf("Result of the expression 3 + 6 * (5 + 3) - 4 / 2 ^ 2 is: %d\n", final_result);

    return 0;
}
