/* 定义段：包含C代码、头文件引入和全局变量定义 */
%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    /* 用于strtol函数的指针，指向数字字符串转换后的第一个非数字字符 */
    char* endptr;

    /* 词法单元（Token）的枚举定义
     * 258-259: 数值类型token
     * 260: 标识符token
     * 261-269: 关键字token
     * 270-284: 运算符token
     * 285-292: 界符token
     * 293: 浮点类型token
     */
    enum yytokentype {
        num_INT = 258,    /* 整数字面量 */
        num_FLOAT = 259,  /* 浮点数字面量 */

        Y_ID = 260,       /* 标识符 */

        /* 关键字 */
        Y_INT = 261,      /* int关键字 */
        Y_VOID = 262,     /* void关键字 */
        Y_CONST = 263,    /* const关键字 */
        Y_IF = 264,       /* if关键字 */
        Y_ELSE = 265,     /* else关键字 */
        Y_WHILE = 266,    /* while关键字 */
        Y_BREAK = 267,    /* break关键字 */
        Y_CONTINUE = 268, /* continue关键字 */
        Y_RETURN = 269,   /* return关键字 */

        /* 运算符 */
        Y_ADD = 270,      /* + */
        Y_SUB = 271,      /* - */
        Y_MUL = 272,      /* * */
        Y_DIV = 273,      /* / */
        Y_MODULO = 274,   /* % */
        Y_LESS = 275,     /* < */
        Y_LESSEQ = 276,   /* <= */
        Y_GREAT = 277,    /* > */
        Y_GREATEQ = 278,  /* >= */
        Y_NOTEQ = 279,    /* != */
        Y_EQ = 280,       /* == */
        Y_NOT = 281,      /* ! */
        Y_AND = 282,      /* && */
        Y_OR = 283,       /* || */
        Y_ASSIGN = 284,   /* = */

        /* 界符 */
        Y_LPAR = 285,     /* ( */
        Y_RPAR = 286,     /* ) */
        Y_LBRACKET = 287, /* { */
        Y_RBRACKET = 288, /* } */
        Y_LSQUARE = 289,  /* [ */
        Y_RSQUARE = 290,  /* ] */
        Y_COMMA = 291,    /* , */
        Y_SEMICOLON = 292,/* ; */

        Y_FLOAT = 293     /* 浮点数类型 */
    };
    /* 全局变量：存储识别出的整数和浮点数值 */
    int a1;    /* 存储整数值 */
    float a2;  /* 存储浮点数值 */
%}

/* 正则定义段：定义正则表达式的命名模式 */
DIGIT [0-9]           /* 定义单个数字 */
WORD  [a-zA-Z]+      /* 定义连续的字母 */
HEXDIGIT [0-9a-fA-F] /* 定义十六进制数字 */
SIGN [+-]            /* 定义正负号 */

/* 规则段：定义词法规则和对应的动作 */
%%
{SIGN}?{DIGIT}+       {a1 = strtol(yytext, &endptr, 10); return num_INT;}    /* 匹配带符号的整数 */
{SIGN}?{DIGIT}+"."{DIGIT}+  {a2 = atof(yytext); return num_FLOAT;}          /* 匹配带符号的浮点数 */
0[xX]{HEXDIGIT}+     {a1 = strtol(yytext, &endptr, 16); return num_INT;}    /* 匹配十六进制整数 */
"//"(.*)   {yywrap();}   /* 匹配单行注释 */
"\n"        {}           /* 忽略换行符 */
" "         {}           /* 忽略空格 */

/* 关键字匹配规则 */
"int"       {return Y_INT;}
"void"      {return Y_VOID;}
"const"     {return Y_CONST;}
"if"        {return Y_IF;}
"else"      {return Y_ELSE;}
"while"     {return Y_WHILE;}
"break"     {return Y_BREAK;}
"continue"  {return Y_CONTINUE;}
"return"    {return Y_RETURN;}

/* 标识符匹配规则：以字母或下划线开头，后跟字母、数字或下划线 */
[a-zA-Z_][a-zA-Z0-9_]*    {return Y_ID;}

/* 运算符匹配规则 */
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

/* 界符匹配规则 */
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

/* 用户代码段：包含主函数和其他C函数定义 */

/* 主函数：循环读取输入并进行词法分析 */
void main()
{
    int tok;

    while(tok = yylex()) 
    {   
        /* 根据不同的token类型打印相应的信息 */
        if(tok == Y_ID)
            printf("<260, %s>\n", yytext);              /* 打印标识符 */
        else if(tok == num_INT)
            printf("<258, %d>\n", a1);                  /* 打印整数值 */
        else if(tok == num_FLOAT)
            printf("<259, %f>\n", a2);                  /* 打印浮点数值 */
        else if(tok == Y_INT || tok == Y_VOID || tok == Y_CONST || tok == Y_IF || tok == Y_ELSE || tok == Y_WHILE || tok == Y_BREAK ||  tok == Y_CONTINUE ||  tok == Y_RETURN)
            printf("<%d, %s>\n", tok, "KEYWORD");       /* 打印关键字 */
        else if(tok == Y_ADD || tok == Y_SUB || tok == Y_MUL || tok == Y_DIV || tok == Y_MODULO || tok == Y_LESS || tok == Y_LESSEQ ||  tok == Y_GREAT ||  tok == Y_GREATEQ || tok == Y_NOTEQ || tok == Y_EQ || tok == Y_NOT || tok == Y_AND || tok == Y_OR || tok == Y_ASSIGN)
            printf("<%d, %s>\n", tok, "OPERATOR");      /* 打印运算符 */
        else if(tok == Y_LPAR || tok == Y_RPAR || tok == Y_LBRACKET || tok == Y_RBRACKET || tok == Y_LSQUARE || tok == Y_RSQUARE || tok == Y_COMMA ||  tok == Y_SEMICOLON || tok == Y_FLOAT)
            printf("<%d, %s>\n", tok, "SYMBOL");        /* 打印界符 */
    }
}

/* yywrap函数：在输入结束时被调用 */
int yywrap(){   
    return 1;  /* 返回1表示输入结束 */
}