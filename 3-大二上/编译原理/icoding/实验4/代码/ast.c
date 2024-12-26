#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

past newAstNode()
{
	past node = malloc(sizeof(ast));
	if(node == NULL)
	{
		printf("run out of memory.\n");
		exit(0);
	}
	memset(node, 0, sizeof(ast));
	return node;
}

past newNum(int value)
{
	past var = newAstNode();
	var->nodeType = "intValue";
	var->ivalue = value;
	return var;
}

past newExpr(int oper, past left,past right)
{
	past var = newAstNode();
	var->nodeType = "expr";
	var->ivalue = oper;
	var->left = left;
	var->right = right;
	var -> strValue = "@";
	return var;
}

past newDoubleExpr(char* logic_oper, past left,past right)
{
	past var = newAstNode();
	var->nodeType = "expr";
	char *strVal = malloc(sizeof(logic_oper));
	strcpy(strVal,logic_oper);
	var -> strValue = strVal;
	var->left = left;
	var->right = right;
	return var;
}

past newBasicNode(char* nodeType, past left, past right, past next)
{
	past root = newAstNode();
	char *node_type = malloc(sizeof(nodeType));
	strcpy(node_type,nodeType);
	root->nodeType = node_type;
	root->left = left;
	root->right = right;
	root->next = next;
	return root;
}

past newNextNode(char* nodeType, past older, past younger)
{
	past root = NULL;
	//还没有根节点
	if(strcmp(nodeType, older->nodeType) != 0){
		root = newAstNode();
		char *node_type = malloc(sizeof(nodeType));
		strcpy(node_type,nodeType);
		root->nodeType = node_type;
		root->left = older; root->left->next = younger;
		root->ivalue = 1;
	}
	//已经有根节点
	else{
		root = older;
		older = older->left;
		while(older->next != NULL) older = older->next;
		older->next = younger;
		root->ivalue++;
	}
	return root;
}

past newTypeNode(char* strVal)
{
	past root = newAstNode();
	root->nodeType = "type";
	char *buf = malloc(sizeof(strVal));
	strcpy(buf,strVal);
	root->strValue = buf;
	return root;
}

past newIDNode(char* strVal)
{
	past root = newAstNode();
	root->nodeType = "parameter";
	char *buf = malloc(sizeof(strVal));
	strcpy(buf,strVal);
	root->strValue = buf;
	return root;
}

void showAst(past node, int nest)
{
	if(node == NULL) {
		//printf("node transfer error\n");		
		return;
	}
	int i = 0;
	for(i = 0; i < nest; i ++)
		printf("  ");
	if(strcmp(node->nodeType, "expr") == 0){
		if(strcmp(node->strValue, "@") == 0) 
			printf("%s '%c'\n", node->nodeType, (char)node->ivalue);
		else
			printf("%s %s\n", node->nodeType, node->strValue);
	}
	else if(strcmp(node->nodeType, "intValue")==0){
		printf("%s . %d\n", node->nodeType, node->ivalue);
	}
	else{
		if(!node->strValue){
			if(node->ivalue) printf("%s . %d\n", node->nodeType, node->ivalue);
			else printf("%s .\n", node->nodeType);
		}
		else if(node->ivalue) printf("%s %s %d\n", node->nodeType, node->strValue, node->ivalue);
		else printf("%s %s .\n", node->nodeType, node->strValue);
	}
	showAst(node->left, nest+1);
	showAst(node->right, nest+1);
	showAst(node->next,nest);
}
