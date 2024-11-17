%{
#include <stdio.h>
#include "parser.tab.h"

extern int yylex(void);
void yyerror(const char *s);
FILE *yyin;
%}

%token DT ID IF ELSE FOR WHILE RETURN
%token NUM FNUM
%token EQ NEQ LEQ GEQ AND OR INC DEC

%left OR
%left AND
%left EQ NEQ
%left '<' '>' LEQ GEQ
%left '+' '-'
%left '*' '/'

%start PROG

%%

PROG : DECLS FUNC_MAIN ;

DECLS : DECLS DECL
      | /* empty */
      ;

DECL : DT ID ';'
     | DT ID '=' E ';'
     ;

FUNC_MAIN : DT ID '(' ')' BLK
          ;

BLK : '{' SS '}'
     ;

SS : SS S
    | S
    ;

S : E ';'
  | IFST ELSEST
  | ELSEST
  | FORST
  | WHILEST
  | RETURNST
  | BLK
  | DECL
  ;

IFST : IF '(' E ')' S
     ;

ELSEST : ELSE S
       ;

FORST : FOR '(' FOR_INIT ';' E ';' E ')' S
      ;

FOR_INIT : DECL  
         | E    
         | /* empty */ 
         ;


WHILEST : WHILE '(' E ')' S
        ;

RETURNST : RETURN E ';'
         ;

E : E '=' E
  | E EQ E
  | E NEQ E
  | E '<' E
  | E '>' E
  | E LEQ E
  | E GEQ E
  | E AND E
  | E OR E
  | F
  | /* empty */
  ;

F : F '+' F
  | F '-' F
  | F '*' F
  | F '/' F
  | F INC
  | F DEC
  | G
  ;

G : '(' E ')'
  | ID
  | NUM
  | FNUM
  ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }

    printf("Start parsing\n");
    if (yyparse() == 0) {
        printf("Parsing successfully\n");
    } else {
        printf("Parsing failed\n");
    }

    if (argc > 1) {
        fclose(yyin);
    }

    return 0;
}
