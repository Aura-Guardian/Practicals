%{
#include "parser.tab.h"
#include <stdio.h>
%}

%option noyywrap

/* Define regular expressions for multi-character operators first */
%%
"int"|"void"|"float"|"double"|"char"    { return DT; }
"if"                                    { return IF; }
"else"                                  { return ELSE; }
"for"                                   { return FOR; }
"while"                                 { return WHILE; }
"return"                                { return RETURN; }

"=="                                    { return EQ; }
"!="                                    { return NEQ; }
"<="                                    { return LEQ; }
">="                                    { return GEQ; }
"&&"                                    { return AND; }
"||"                                    { return OR; }
"++"                                    { return INC; }
"--"                                    { return DEC; }

"+"                                     { return '+'; }
"-"                                     { return '-'; }
"*"                                     { return '*'; }
"/"                                     { return '/'; }
"="                                     { return '='; }
"("                                     { return '('; }
")"                                     { return ')'; }
"{"                                     { return '{'; }
"}"                                     { return '}'; }
";"                                     { return ';'; }
"<"                                     { return '<'; }
">"                                     { return '>'; }
"!"                                     { return '!' ; }

[_a-zA-Z][_a-zA-Z0-9]*                  { return ID; }
[0-9]+\.[0-9]+                           { return FNUM; }
[0-9]+                                   { return NUM; }

[ \t\n]+                                { /* Ignore whitespace */ }

.                                       { fprintf(stderr, "Unknown character: %s\n", yytext); return yytext[0]; }
%%
