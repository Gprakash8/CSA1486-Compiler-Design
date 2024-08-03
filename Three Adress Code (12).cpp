#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Enum for different types of nodes in the AST
typedef enum {
    NODE_NUMBER,
    NODE_ADD,
    NODE_SUBTRACT,
    NODE_MULTIPLY,
    NODE_DIVIDE
} NodeType;

// AST Node structure
typedef struct Node {
    NodeType type;
    int value; // Only used if the node is a number
    struct Node *left;
    struct Node *right;
} Node;

// Function prototypes
Node* parseExpression(const char **input);
Node* parseTerm(const char **input);
Node* parseFactor(const char **input);
Node* parseNumber(const char **input);
void generateTAC(Node *node);
void freeAST(Node *node);

// Global counter for temporary variables
int tempVarCounter = 0;

// Parse a number and create a number node
Node* parseNumber(const char **input) {
    while (isspace(**input)) (*input)++;
    int value = 0;
    while (isdigit(**input)) {
        value = value * 10 + (**input - '0');
        (*input)++;
    }
    Node *node = (Node*)malloc(sizeof(Node));
    node->type = NODE_NUMBER;
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// Parse a factor: number or (expression)
Node* parseFactor(const char **input) {
    while (isspace(**input)) (*input)++;
    if (**input == '(') {
        (*input)++;
        Node *node = parseExpression(input);
        while (isspace(**input)) (*input)++;
        if (**input == ')') {
            (*input)++;
        }
        return node;
    }
    return parseNumber(input);
}

// Parse a term: factor { (*|/) factor }
Node* parseTerm(const char **input) {
    Node *node = parseFactor(input);
    while (true) {
        while (isspace(**input)) (*input)++;
        if (**input == '*') {
            (*input)++;
            Node *right = parseFactor(input);
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->type = NODE_MULTIPLY;
            newNode->left = node;
            newNode->right = right;
            node = newNode;
        } else if (**input == '/') {
            (*input)++;
            Node *right = parseFactor(input);
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->type = NODE_DIVIDE;
            newNode->left = node;
            newNode->right = right;
            node = newNode;
        } else {
            break;
        }
    }
    return node;
}

// Parse an expression: term { (+|-) term }
Node* parseExpression(const char **input) {
    Node *node = parseTerm(input);
    while (true) {
        while (isspace(**input)) (*input)++;
        if (**input == '+') {
            (*input)++;
            Node *right = parseTerm(input);
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->type = NODE_ADD;
            newNode->left = node;
            newNode->right = right;
            node = newNode;
        } else if (**input == '-') {
            (*input)++;
            Node *right = parseTerm(input);
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->type = NODE_SUBTRACT;
            newNode->left = node;
            newNode->right = right;
            node = newNode;
        } else {
            break;
        }
    }
    return node;
}

// Generate three-address code from the AST
int generateTAC(Node *node) {
    if (!node) return -1;

    if (node->type == NODE_NUMBER) {
        int tempVar = tempVarCounter++;
        printf("t%d = %d\n", tempVar, node->value);
        return tempVar;
    }

    int leftTemp = generateTAC(node->left);
    int rightTemp = generateTAC(node->right);
    int tempVar = tempVarCounter++;

    switch (node->type) {
        case NODE_ADD:
            printf("t%d = t%d + t%d\n", tempVar, leftTemp, rightTemp);
            break;
        case NODE_SUBTRACT:
            printf("t%d = t%d - t%d\n", tempVar, leftTemp, rightTemp);
            break;
        case NODE_MULTIPLY:
            printf("t%d = t%d * t%d\n", tempVar, leftTemp, rightTemp);
            break;
        case NODE_DIVIDE:
            printf("t%d = t%d / t%d\n", tempVar, leftTemp, rightTemp);
            break;
        default:
            break;
    }

    return tempVar;
}

// Free the AST
void freeAST(Node *node) {
    if (!node) return;
    freeAST(node->left);
    freeAST(node->right);
    free(node);
}

int main() {
    const char *input = "3 + 5 * (2 - 8) / 4";
    printf("Input Expression: %s\n", input);
    
    Node *ast = parseExpression(&input);
    printf("Generated Three-Address Code:\n");
    generateTAC(ast);

    freeAST(ast);
    return 0;
}
