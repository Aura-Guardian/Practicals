%{

#include<stdio.h>

#include "y.tab.h"

extern int yylval;

%}

%%

"for" {return fortoken;}

"while" {return whiletoken;}

"int" {return datatype;}

"=" {return assignment;}

";" {return semicolon;}

" " {return space;}

[0-9]+ {yylval=atoi(yytext); return digit;}

"++"|"--" {return unary;}

"(" {return openingbracket;}

")" {return closingbracket;}

[a-zA-Z][a-zA-Z0-9]* { return identifier;}

">"|"<"|"=="|"<="|">=" {return condition;}

"{" {return curlyopening;}

"}" {return curlyclosing;}

.  {return codelogic;}

%%

int yywrap()

{

return 1;

}