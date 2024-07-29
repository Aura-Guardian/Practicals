%{
#include <stdio.h>
#include <string.h>
int c = 0;
%}
%%
[0-9]+  {printf(" NUM ");}
[0-9]*"."[0-9]+ {printf(" FLOAT ");}
[_a-zA-Z][_a-zA-Z0-9]* {printf("ID%d ", ++c);}
[-+=*/] {printf(" OPR ");}
[!@#$%^&*()_+\-=\[\]{};':"\\|,.<>\/?`~] {printf(" SC ");}
([^a-zA-Z0-9])*(this|return|register|long|auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|short|signed|sizeof|static|struct|swtich|typedef|union|unsigned|void|volatile|while)([^a-zA-Z0-9]) {printf(" KEYW ");}
\"[^\"]*\" {printf(" STR ");}
"//".* {printf(" SINC ");}
"/*".*"*/"; {printf(" MULC ");}
%%

int main(){yylex();}
int yywrap(){return -2;}
int yyerror(){return 0;}