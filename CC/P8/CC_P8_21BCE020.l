%{
#include "parser.tab.h"
#include <string.h>
%}

%%
"int"|"void"|"float"        { return DT; }
"if"                        { return IF; }
"else"                      { return ELSE; }
"while"                     { return WHILE; }
[_a-zA-Z][a-zA-Z0-9]*       { yylval.str = strdup(yytext); return ID; }
[0-9]+                      { return NUM; }
[0-9]*"."[0-9]+             { return FNUM; }
"=="                        { return EQ; }
"!="                        { return NEQ; }
"<"                         { return LT; }
">"                         { return GT; }
"<="                        { return LEQ; }
">="                        { return GEQ; }
[-+*/=(){}:;]               { return yytext[0]; }
[ \t\n]+                    { }
%%

int yywrap() { return 1; }
