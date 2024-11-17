%{
#include <stdio.h>
#include <string.h>

int count = 0;
#define MAX 100
struct symbol_table {
    char name[50];
    char type[50];
} symbol_table[MAX];
void display();
void input_buffer(const char* name, const char* type) {
    for(int i = 0; i < count; i++){
        if (strcmp(symbol_table[i].name, name) == 0) {
            return; 
        }
    }
    strcpy(symbol_table[count].name, name);
    strcpy(symbol_table[count].type, type);

    count++;
}

%}

%%
"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"else"|"enum"|"extern"|"for"|"goto"|"if"|"inline"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"while"|"int"|"float"|"char"|"double"|"void" {printf("keyword");}
[_a-zA-Z][a-zA-Z0-9]* {printf("ID"); input_buffer(yytext, "ID");}
[0-9]+ {printf("int");}
[0-9]*"."[0-9]+ {printf("float");}
[a-zA-z] {printf("char");}
["].*["] {printf("str");}
[-+=*/%<>|&!~^?:]  {printf("opr");}
";"|"{"|"}"|"("|")" {printf("special symbol");}
"//".* {printf("comments");}
"/*"(.|\n)*"*/"  {printf("multi-line comment");}
\n {display();}

%%

void display() {
    printf("\nSymbol Table:\n");
    printf("Name\t\tValue\n");
    for (int i = 0; i < count; i++) {
        printf("%s\t\t%s\n", symbol_table[i].name, symbol_table[i].type);
    }
}

int main() {
    yylex();
    return 0;
}

int yywrap() { return 0; }

int yyerror() { return 0; }
