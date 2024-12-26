#ifndef __AST
#define __AST

#include <stdio.h>

typedef struct _ast ast;
typedef struct _ast *past;
struct _ast{
	int ivalue;
	char* strValue; 
	char* nodeType; 
	past next; 
	past left;
	past right;
};


past newAstNode();
past newNum(int value);
past newExpr(int oper, past left,past right);
past newDoubleExpr(char* logic_oper, past left,past right);
past newBasicNode(char* nodeType, past left, past right, past next);
past newNextNode(char* nodeType, past older, past younger);
past newTypeNode(char* strVal);
past newIDNode(char* strVal);
void showAst(past node, int nest);

#endif
