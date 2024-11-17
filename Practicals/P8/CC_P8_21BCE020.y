%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int yyerror(char *str);
extern int yylex(void); 

#define MAX_SYMBOLS 100

typedef struct {
    char *name;
    int declared;
} Symbol;

Symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

// Function to add a symbol to the table
int addSymbol(char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return 0;  // Symbol already exists, indicating multiple declaration
        }
    }
    // Add symbol if it doesn't already exist
    symbolTable[symbolCount].name = strdup(name);
    symbolTable[symbolCount].declared = 1;
    symbolCount++;
    return 1;
}

// Function to check if a symbol is declared
int isDeclared(char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return symbolTable[i].declared;
        }
    }
    return 0;  // Symbol not found
}

%}

%union {
    char* str;
}

%token <str> DT ID IF ELSE WHILE NUM FNUM

%%

PROG : DT ID '(' ')' BLK
    {
        // Add the function name to symbol table
        if (!addSymbol($2)) {
            printf("Error: Multiple declaration of '%s'\n", $2);
        }
    }
    ;

BLK : '{' SS '}'
    ;

SS : SS S
   | S
   ;

S : DT ID ';'
    {
        // Check for multiple declaration
        if (!addSymbol($2)) {
            printf("Error: Multiple declaration of '%s'\n", $2);
        }
    }
  | E ';'
  | IFST 
  | WHILEST
  | ';'
  ;

IFST : IF '(' E ')' S 
     | IF '(' E ')' S ELSE S
     ;

WHILEST : WHILE '(' E ')' S
        ;

E : ID '=' E
    {
        // Check for undeclared identifier
        if (!isDeclared($1)) {
            printf("Error: Undeclared identifier '%s'\n", $1);
        }
    }
  | R          
  ;

R : R '>' F     
  | R '<' F
  | F          
  ;

F : F '+' G 
  | F '-' G 
  | G
  ;

G : G '*' H 
  | G '/' H 
  | H
  ;

H : '(' E ')' 
  | ID
    {
        // Check for undeclared identifier
        if (!isDeclared($1)) {
            printf("Error: Undeclared identifier '%s'\n", $1);
        }
    }
  | NUM  
  | FNUM
  ;

%%

int yyerror(char *str)
{
    printf("syntax error\n");
    return 0;
}

int main()
{
    yyparse();
    return 0;
}
