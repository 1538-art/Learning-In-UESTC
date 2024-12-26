%{

#include "stdio.h"
#include "stdlib.h"
#include "Irparser.tab.h"
#include "string.h"

%}

white [\n\t ]
ID [a-zA-Z_][a-zA-Z0-9_]*
FLOAT [1-9][0-9]*\.[0-9]+
INT [1-9][0-9]*

%%
{white} {}
{INT} {yylval.iValue=atoi(yytext);return num_INT;}
[\+-]?0 {yylval.iValue=0;return num_INT;}
{FLOAT} {return num_FLOAT;}
[\+-]?0\.[0-9]+ {return num_FLOAT;}
{ID} {
    if(strcmp(yytext,"int")==0)  {yylval.iValue = Y_INT;return Y_INT;}
    else if(strcmp(yytext,"float")==0) {yylval.iValue = Y_FLOAT;return Y_FLOAT;}
    else if(strcmp(yytext,"const")==0) {yylval.iValue = Y_CONST;return Y_CONST;}
    else if(strcmp(yytext,"void")==0) {yylval.iValue = Y_VOID;return Y_VOID;}
    else if(strcmp(yytext,"if")==0) return Y_IF;
    else if(strcmp(yytext,"else")==0) return Y_ELSE;
    else if(strcmp(yytext,"while")==0) return Y_WHILE;
    else if(strcmp(yytext,"break")==0) return Y_BREAK;
    else if(strcmp(yytext,"continue")==0) return Y_CONTINUE;
    else if(strcmp(yytext,"return")==0) return Y_RETURN;
    else {
        char* name = (char*)malloc(sizeof(yytext));
        strcpy(name,yytext);
        yylval.name = name;
        return Y_ID;
    }
}

"//"+.+\n {}
0x[0-9A-Fa-f]+ {char* endptr=NULL;yylval.iValue = strtol(yytext,&endptr,16);return num_INT;}

"+" {yylval.iValue = Y_ADD;return Y_ADD;}
"-" {yylval.iValue = Y_SUB;return Y_SUB;}
"*" {yylval.iValue = Y_MUL;return Y_MUL;}
"/" {yylval.iValue = Y_DIV;return Y_DIV;}
"%" {yylval.iValue = Y_MODULO;return Y_MODULO;}
"<" {yylval.iValue = Y_LESS;return Y_LESS;}
"<=" {yylval.iValue = Y_LESSEQ;return Y_LESSEQ;}
">" {yylval.iValue = Y_GREAT;return Y_GREAT;}
">=" {yylval.iValue = Y_GREATEQ;return Y_GREATEQ;}
"!=" {yylval.iValue = Y_NOTEQ;return Y_NOTEQ;}
"==" {yylval.iValue = Y_EQ;return Y_EQ;}
"!" {yylval.iValue = Y_NOT;return Y_NOT;}
"&&" {yylval.iValue = Y_AND;return Y_AND;}
"||" {yylval.iValue = Y_OR;return Y_OR;}
"=" {yylval.iValue = Y_ASSIGN;return Y_ASSIGN;}

"(" {return Y_LPAR;}
")" {return Y_RPAR;}
"{" {return Y_LBRACKET;}
"}" {return Y_RBRACKET;}
"[" {return Y_LSQUARE;}
"]" {return Y_RSQUARE;}
";" {return Y_SEMICOLON;}
"," {return Y_COMMA;}

%%

void yyerror(char *str){
    fprintf(stderr,"error:%s\n",str);
}

int yywrap(){
    return 1;
}

