%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char* endptr;
enum yytokentype {
    num_INT = 258,
    num_FLOAT = 259,

    Y_ID = 260,

    Y_INT = 261,
    Y_VOID = 262,
    Y_CONST = 263,
    Y_IF = 264,
    Y_ELSE = 265,
    Y_WHILE = 266,
    Y_BREAK = 267,
    Y_CONTINUE = 268,
    Y_RETURN = 269,

    Y_ADD = 270,
    Y_SUB = 271,
    Y_MUL = 272,
    Y_DIV = 273,
    Y_MODULO = 274,
    Y_LESS = 275,
    Y_LESSEQ = 276,
    Y_GREAT = 277,
    Y_GREATEQ = 278,
    Y_NOTEQ = 279,
    Y_EQ = 280,
    Y_NOT = 281,
    Y_AND = 282,
    Y_OR = 283,
    Y_ASSIGN = 284,

    Y_LPAR = 285,
    Y_RPAR = 286,
    Y_LBRACKET = 287,
    Y_RBRACKET = 288,
    Y_LSQUARE = 289,
    Y_RSQUARE = 290,
    Y_COMMA = 291,
    Y_SEMICOLON = 292,

    Y_FLOAT = 293
};
int a1;
float a2;
%}

DIGIT [0-9]
WORD  [a-zA-Z]+
HEXDIGIT [0-9a-fA-F]
SIGN [+-]

%%
{SIGN}?{DIGIT}+       {a1 = strtol(yytext, &endptr, 10); return num_INT;}
{SIGN}?{DIGIT}+"."{DIGIT}+  {a2 = atof(yytext); return num_FLOAT;}
0[xX]{HEXDIGIT}+     {a1 = strtol(yytext, &endptr, 16); return num_INT;}
"//"(.*)   {yywrap();}
"\n"        {}
" "         {}
"int"       {return Y_INT;}
"void"      {return Y_VOID;}
"const"     {return Y_CONST;}
"if"        {return Y_IF;}
"else"      {return Y_ELSE;}
"while"     {return Y_WHILE;}
"break"     {return Y_BREAK;}
"continue"  {return Y_CONTINUE;}
"return"    {return Y_RETURN;}
[a-zA-Z_][a-zA-Z0-9_]*    {return Y_ID;}
"+"         {return Y_ADD; }
"-"         {return Y_SUB; }
"*"         {return Y_MUL; }
"/"         {return Y_DIV; }
"%"         {return Y_MODULO; }
"<"         {return Y_LESS; }
"<="        {return Y_LESSEQ; }
">"         {return Y_GREAT; }
">="        {return Y_GREATEQ; }
"!="        {return Y_NOTEQ;}
"=="        {return Y_EQ; }
"!"         {return Y_NOT;}
"&&"        {return Y_AND;}
"||"        {return Y_OR;}
"="         {return Y_ASSIGN;}
"("         {return Y_LPAR;}
")"         {return Y_RPAR; }
"{"         {return Y_LBRACKET;}
"}"         {return Y_RBRACKET;}
"["         {return Y_LSQUARE;}
"]"         {return Y_RSQUARE;}
","         {return Y_COMMA;}
";"         {return Y_SEMICOLON;}
"."         {return Y_FLOAT;}
%%

void main()
{
    int tok;

    while(tok = yylex()) 
    {   
        if(tok == Y_ID)
            printf("<260, %s>\n", yytext);
        else if(tok == num_INT)
            printf("<258, %d>\n", a1);
        else if(tok == num_FLOAT)
            printf("<259, %f>\n", a2);
        else if(tok == Y_INT || tok == Y_VOID || tok == Y_CONST || tok == Y_IF || tok == Y_ELSE || tok == Y_WHILE || tok == Y_BREAK ||  tok == Y_CONTINUE ||  tok == Y_RETURN)
            printf("<%d, %s>\n", tok, "KEYWORD");
        else if(tok == Y_ADD || tok == Y_SUB || tok == Y_MUL || tok == Y_DIV || tok == Y_MODULO || tok == Y_LESS || tok == Y_LESSEQ ||  tok == Y_GREAT ||  tok == Y_GREATEQ || tok == Y_NOTEQ || tok == Y_EQ || tok == Y_NOT || tok == Y_AND || tok == Y_OR || tok == Y_ASSIGN)
            printf("<%d, %s>\n", tok, "OPERATOR");
        else if(tok == Y_LPAR || tok == Y_RPAR || tok == Y_LBRACKET || tok == Y_RBRACKET || tok == Y_LSQUARE || tok == Y_RSQUARE || tok == Y_COMMA ||  tok == Y_SEMICOLON || tok == Y_FLOAT)
            printf("<%d, %s>\n", tok, "SYMBOL");
    }
}

int yywrap(){   
    return 1;  
}