%{
#include <stdio.h>
#include <string.h>
#include <string.h>
FILE *outfile;
%}
digit   [0-9]
alpha       [a-zA-Z]
alphanum    [a-zA-Z0-9]
whitespace  [ \t\n\r]+
%% 
{whitespace}               {/* skip whitespace */ }
"//".*                     {/* skip single-line comments */}
"/*"(.|\n)*"*/"           {/* skip multi-line comments */}
"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"else"|"enum"|"extern"|"for"|"goto"|"if"|"inline"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"while"|"int"|"float"|"char"|"double"|"void" {fprintf(outfile, "Keyword -> %s\n", yytext);}
{alpha}({alphanum}|_)* {fprintf(outfile, "ID -> %s\n", yytext);}
{digit}+ {fprintf(outfile, "Integer -> %s\n", yytext);}
{digit}+"."{digit}+ {fprintf(outfile, "Float -> %s\n", yytext);}
"'"[^'\n]?"'" {fprintf(outfile, "Char -> %s\n", yytext);}
"\""(\\.|[^"\n])*"\"" {fprintf(outfile, "String -> %s\n", yytext);}
"+"|"-"|"*"|"/" {fprintf(outfile, "Arithmetic OPR -> %s\n", yytext);}
"=" {fprintf(outfile, "Assignment OPR -> %s\n", yytext);}
"++"|"--" {fprintf(outfile, "Increment/Decrement OPR -> %s\n", yytext);}
"=="|"!="|"<"|"<="|">"|">=" {fprintf(outfile, "Relational OPR -> %s\n", yytext);}
";"|"{"|"}"|"("|")" {fprintf(outfile, "Special symbol-> %s\n", yytext);}
%%

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.txt> <output.txt>\n", argv[0]);
        return 1;
    }
    FILE *infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");
    yyin = infile;
    yylex();
    fclose(infile);
    fclose(outfile);
    return 0;
}

int yywrap() {
    return 1;
}
