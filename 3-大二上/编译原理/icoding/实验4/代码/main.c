#include "ast.h"
#include "genllvm.h"
#include <stdio.h>

extern int yyparse();
extern FILE *yyin;
past astRoot;
void yyerror(char *s)
{
    printf("%s\n", s);
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("argcs too many!.\n");
        return 0;
    }
    if (argc == 2)
    {
        yyin = fopen(argv[1], "r");
    }
    else
    {
        yyin = fopen("./test.c", "r");
    }

    // printf("before yyparse\n");
    yyparse();
    fclose(yyin);
    // printf("before show  &  after yyparse\n");
    genExpr(astRoot);
    showAst(astRoot, 0);
    // printf("after show\n");

    return 0;
}
