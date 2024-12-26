#ifndef __AST_H
#define __AST_H

#include "stdbool.h"
#include "node_type.h"
typedef struct _ast ast;
typedef struct _ast *past;

struct _ast{
   int ivalue;
   float fvalue;
   char* svalue;
   node_type nodeType;
   past left;
   past right;
   past if_cond;
   past next;
};

extern int single_num;
extern int count;
extern int gather_num;
extern int count_1;
extern int already;
extern past tmp;
extern past node;
extern past tmp_node;
extern past trans;

extern void showAst(past node, int nest, bool use_blank);
extern void showToken(int Token);
past newAstNode();// 创建一个结点
past newID(char* value); //创建一个结点，并将结点中的 svalue 设置为 value
past newInt(int value); //创建一个结点，并将结点中的 ivalue 设置为 value
past newIDNode(char *value);
past newNextNode(past younger,past older);
past newDeclStmt(int nodetype,past specified);
past newConstInitVal(int nodetype,past specified);
past newVarDef(int nodetype,past id,past val,int FLAG);
past newInitVal(int nodetype,past specified,float FLAG);
past newFuncDef(int nodetype,past id,past params,past body);
past newFuncDecl(int nodetype,past id);
past newFuncParam(int nodetype,past id,past behind);
past newCompoundStmt(int nodetype,past body);
past newWhileStmt(int nodetype,past left, past right);
past newIfStmt(int nodetype,past if_cond,past left,past right);
past newBreakStmt(int nodetype);
past newContinueStmt(int nodetype);
past newReturnStmt(int nodetype,past body);
past newDeclRefExp(int nodetype,past id);
past newArrSubExp(int nodetype,past left,past next);
past newParenExp(int nodetype,past body);
past newInt(int value);
past newFloat(float value);
past newCallExp(int nodetype,past id,past body);
past newUnaryExp(int nodetype,int opre,past body);
past newBinaryOpre(int nodetype,int opre,past name,past right);

#endif
