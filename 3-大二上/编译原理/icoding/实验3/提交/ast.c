#include "node_type.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "ast.h"
#include "Irparser.tab.h"
int node_num;
//  void showAst(past node, int nest, bool use_blank){
// 	if(node == NULL)
// 		return;
// 	if(use_blank) {
// 		for (int i = 0; i < nest; i++)
// 			printf("    ");
// 	}else{
// 		printf("%d", nest);
// 	}
// 	switch (node->nodeType){
// 		case INTEGER_LITERAL:
// 			printf("%d%s %d\n", node_num++,"INTEGER_LITERAL", node->ivalue);
// 			break;
// 		case BINARY_OPERATOR:
// 			printf("%d%s ", node_num++,"BINARY_OPERATOR");
// 			showToken(node->ivalue);
// 			printf("\n");
// 			break;
// 		case UNARY_OPERATOR:
// 			printf("%d%s ", node_num++,"UNARY_OPERATOR");
// 			showToken(node->ivalue);
// 			printf("\n");
// 			break;
// 		case FUNCTION_DECL:
// 			printf("%d%s '%s'\n", node_num++,"FUNCTION_DECL", node->svalue);
// 			break;
// 		case CALL_EXPR:
// 			printf("%d%s\n", node_num++,"CALL_EXPR");
// 			break;
// 		case COMPOUND_STMT:
// 			printf("%d%s\n", node_num++,"COMPOUND_STMT");
// 			break;
// 		case DECL_STMT:
// 			printf("%d%s\n", node_num++,"DECL_STMT");
// 			break;
// 		case VARIABLE_REF:
// 			printf("%d%s\n", node_num++,"VARIABLE_REF");
// 			break;
// 		case PARM_DECL:
// 			printf("%d%s '%s'\n", node_num++,"PARM_DECL", node->svalue);
// 			break;
// 		case VAR_DECL:
// 			printf("%d%s: '%s'\n",node_num++,"VAR_DECL", node->svalue);
// 			break;
// 		case DECL_REF_EXPR:
// 			printf("%d%s: '%s'\n", node_num++,"DECL_REF_EXPR", node->svalue);
// 			break;
// 		case RETURN_STMT:
// 			printf("%d%s\n", node_num++,"RETURN_STMT");
// 			break;
// 		case WHILE_STMT:
// 			printf("%d%s\n", node_num++,"WHILE_STMT");
// 			break;
// 		case BREAK_STMT:
// 			printf("%d%s\n", node_num++,"BREAK_STMT");
// 			break;
// 		case CONTINUE_STMT:
// 			printf("%d%s\n", node_num++,"CONTINUE_STMT");
// 			break;
// 		case IF_STMT:
// 			printf("%d%s\n", node_num++,"IF_STMT");
// 			showAst(node->if_cond, nest+1, use_blank);
// 			break;
// 		case INIT_LIST_EXPR:
// 			printf("%d%s\n", node_num++,"INIT_LIST_EXPR");
// 			break;
// 		case ARRAY_SUBSCRIPT_EXPR:
// 			printf("%d%s\n", node_num++,"ARRAY_SUBSCRIPT_EXPR");
// 			break;
// 		case PAREN_EXPR:
// 			printf("%d%s\n", node_num++,"PAREN_EXPR");
// 			break;
// 		default:
// 			printf("%d%s\n", node_num++,"NOT IMPlemented");
// 			break;
// 	}
// 	showAst(node->left, nest+1, use_blank);
// 	showAst(node->right, nest+1, use_blank);
// 	showAst(node->next, nest, use_blank);
// }

void showAst(past node, int nest, bool use_blank){
	if(node == NULL){
		return;
	}
	if(use_blank) {
		for (int i = 0; i < nest; i++)
			printf("    ");
	}else{
		printf("%d", nest);
	}
	switch (node->nodeType){
		case INTEGER_LITERAL:
			printf("%s %d\n", "INTEGER_LITERAL", node->ivalue);
			break;
		case BINARY_OPERATOR:
			printf("%s ", "BINARY_OPERATOR");
			showToken(node->ivalue);
			printf("\n");
			break;
		case UNARY_OPERATOR:
			printf("%s ", "UNARY_OPERATOR");
			showToken(node->ivalue);
			printf("\n");
			break;
		case FUNCTION_DECL:
			printf("%s '%s'\n", "FUNCTION_DECL", node->svalue);
			break;
		case CALL_EXPR:
			printf("%s\n", "CALL_EXPR");
			break;
		case COMPOUND_STMT:
			printf("%s\n", "COMPOUND_STMT");
			break;
		case DECL_STMT:
			printf("%s\n", "DECL_STMT");
			break;
		case VARIABLE_REF:
			printf("%s\n", "VARIABLE_REF");
			break;
		case PARM_DECL:
			printf("%s '%s'\n", "PARM_DECL", node->svalue);
			break;
		case VAR_DECL:
			printf("%s: '%s'\n", "VAR_DECL", node->svalue);
			break;
		case DECL_REF_EXPR:
			printf("%s: '%s'\n", "DECL_REF_EXPR", node->svalue);
			break;
		case RETURN_STMT:
			printf("%s\n", "RETURN_STMT");
			break;
		case WHILE_STMT:
			printf("%s\n", "WHILE_STMT");
			break;
		case BREAK_STMT:
			printf("%s\n", "BREAK_STMT");
			break;
		case CONTINUE_STMT:
			printf("%s\n", "CONTINUE_STMT");
			break;
		case IF_STMT:
			printf("%s\n", "IF_STMT");
			showAst(node->if_cond, nest+1, use_blank);
			break;
		case INIT_LIST_EXPR:
			printf("%s\n", "INIT_LIST_EXPR");
			break;
		case ARRAY_SUBSCRIPT_EXPR:
			printf("%s\n", "ARRAY_SUBSCRIPT_EXPR");
			break;
		case PAREN_EXPR:
			printf("%s\n", "PAREN_EXPR");
			break;
		default:
			printf("%s\n", "NOT IMPlemented");
			break;
	}
	showAst(node->left, nest+1, use_blank);
	showAst(node->right, nest+1, use_blank);
	showAst(node->next, nest, use_blank);
}

void showToken(int Token){
	switch (Token)	{
	case Y_INT:
		printf("%s", "INTEGER");
		break;
	case Y_FLOAT:
		printf("%s", "FLOAT");
		break;
	case Y_CONST:
		printf("%s", "CONST");
		break;
	case Y_ADD:
	case '+':
		printf("'%c'", '+');
		break;
	case Y_SUB:
	case '-':
		printf("'%c'", '-');
		break;
	case Y_MUL:
	case '*':
		printf("'%c'", '*');
		break;
	case Y_DIV:
		printf("'%c'", '/');
		break;
	case Y_MODULO:
	case '%':
		printf("'%c'", '%');
		break;
	case Y_LESS:
	case '<':
		printf("'%c'", '<');
		break;
	case Y_LESSEQ:
		printf("'%s'", "<=");
		break;
	case Y_GREAT:
	case '>':
		printf("'%c'", '>');
		break;
	case Y_GREATEQ:
		printf("'%s'", ">=");
		break;
	case Y_NOTEQ:
		printf("'%s'", "!=");
		break;
	case Y_EQ:
		printf("'%s'", "==");
		break;
	case Y_NOT:
	case '!':
		printf("'%c'", '!');
		break;
	case Y_AND:
		printf("'%s'", "&&");
		break;
	case Y_OR:
		printf("'%s'", "||");
		break;
	case Y_ASSIGN:
	case '=':
		printf("'%c'", '=');
		break;
	default:
		break;
	}
}

//数据结构声明

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

past newIDNode(char* value){
	past node = newAstNode();
	node->nodeType = 72;
	node->svalue = value;
	return node;
}

past newInt(int value){
	past node = newAstNode();
	node->nodeType = INTEGER_LITERAL;
	node->ivalue = value;
	return node;
}

past newNextNode(past younger,past older){
	past root = younger;
	past last = younger;
	while(last!=NULL&&last->next!=NULL){
		last=last->next;
	}
	last->next = older;
	return root;
}

past newDeclStmt(int nodetype,past specified){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = specified;
	return node;
}

past newConstInitVal(int nodetype,past specified){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = specified;
	return node;
}

past newVarDef(int nodetype,past id,past val,int FLAG){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->right = val;
	node->ivalue = FLAG;
	node->svalue = id->svalue;
	return node;
}

past newInitVal(int nodetype,past specified,float FLAG){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = specified;
	node->fvalue = FLAG;
	return node;
}

past newFuncDef(int nodetype,past id,past params,past body){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = params;
	node->right = body;
	node->svalue = id->svalue;
	return node;
}

past newFuncDecl(int nodetype,past id){
	past node = newAstNode();
	node->svalue = id->svalue;
	node->nodeType = nodetype;
	return node;
}

past newFuncParam(int nodetype,past id,past behind){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->svalue = id->svalue;
	node->left = behind;
	return node;
}

past newCompoundStmt(int nodetype,past body){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = body;
	return node;
}

past newWhileStmt(int nodetype,past left, past right){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = left;
	node->right = right;
	return node;
}

past newIfStmt(int nodetype,past if_cond,past left,past right){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->if_cond = if_cond;
	node->left = left;
	node->right = right;
	return node;
}

past newBreakStmt(int nodetype){
	past node = newAstNode();
	node->nodeType = nodetype;
	return node;
}

past newContinueStmt(int nodetype){
	past node = newAstNode();
	node->nodeType = nodetype;
	return node;
}

past newReturnStmt(int nodetype,past body){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = body;
	return node;
}

past newDeclRefExp(int nodetype,past id){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->svalue = id->svalue;
	return node;
}

past newArrSubExp(int nodetype,past exp,past next){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = next;
	if(next != NULL) {
		node->right = next->right;
		next->right  = exp;
	}
	return node;
}

past newParenExp(int nodetype,past body){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = body;
	return node;
}

past newFloat(float value){
	past node = newAstNode();
	node->fvalue = value;
	return node;
}

past newCallExp(int nodetype,past id,past body){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = id;
	node->right = body;
	return node;
}

past newUnaryExp(int nodetype,int opre,past body){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->ivalue = opre;
	node->left = body;
	return node;
}

past newBinaryOpre(int nodetype,int opre,past name,past right){
	past node = newAstNode();
	node->nodeType = nodetype;
	node->left = name;
	node->right = right;
	node->ivalue = opre;
	return node;
}