#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

// Structure for each symbol table entry
typedef struct Symbol {
    char name[50];
    int address;
    struct Symbol* next;
} Symbol;

// Hash table array of symbol pointers
Symbol* symbolTable[TABLE_SIZE];

// Hash function to map names to an index
unsigned int hash(char* name) {
    unsigned int hashValue = 0;
    while (*name) {
        hashValue = (hashValue << 5) + *name++;
    }
    return hashValue % TABLE_SIZE;
}

// Insert a new symbol into the symbol table
void insertSymbol(char* name, int address) {
    unsigned int index = hash(name);
    Symbol* newSymbol = (Symbol*)malloc(sizeof(Symbol));
    strcpy(newSymbol->name, name);
    newSymbol->address = address;
    newSymbol->next = symbolTable[index];
    symbolTable[index] = newSymbol;
}

// Search for a symbol in the symbol table
Symbol* searchSymbol(char* name) {
    unsigned int index = hash(name);
    Symbol* current = symbolTable[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Delete a symbol from the symbol table
void deleteSymbol(char* name) {
    unsigned int index = hash(name);
    Symbol* current = symbolTable[index];
    Symbol* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                symbolTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Symbol not found: %s\n", name);
}

// Display the symbol table
void displaySymbolTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol* current = symbolTable[i];
        if (current != NULL) {
            printf("Index %d:\n", i);
            while (current != NULL) {
                printf("  Name: %s, Address: %d\n", current->name, current->address);
                current = current->next;
            }
        }
    }
}

int main() {
    // Initialize the symbol table
    for (int i = 0; i < TABLE_SIZE; i++) {
        symbolTable[i] = NULL;
    }

    // Insert symbols
    insertSymbol("x", 100);
    insertSymbol("y", 200);
    insertSymbol("z", 300);

    // Display the symbol table
    displaySymbolTable();

    // Search for a symbol
    Symbol* symbol = searchSymbol("y");
    if (symbol != NULL) {
        printf("Found symbol: Name: %s, Address: %d\n", symbol->name, symbol->address);
    } else {
        printf("Symbol not found: y\n");
    }

    // Delete a symbol
    deleteSymbol("y");

    // Display the symbol table again
    displaySymbolTable();

    return 0;
}