#include "ast.h"
#include <stdio.h>

extern int yyparse();
extern FILE* yyin;

int main(int argc, char **argv){

    // if(argc > 2 )
	// {
	// 	printf("argcs too many!.\n");
	// 	return 0;
	// }
	// if(argc == 2){
	// 	yyin = fopen(argv[1],"r");
	// }else{
	// 	printf("no file input!\n");
    //     	return 1;
	// }

	//printf("before yyparse\n");	
	yyparse();
	//printf("before show  &  after yyparse\n");
	showAst(node, 0,false);
	//printf("after show\n");
    return 0;
}