%{
#include "node_type.h"
#include "stdio.h"
#include "string.h"
#include "ast.h"
int single_num=0;
int count=0;
past tmp = NULL;
past tmp_node = NULL;
past trans;
int gather_num=0;
int count_1;
int already=0;
int process=0;

struct _ast *node;
int yylex(void);
void yyerror(char *);
%}

%union{
	int			iValue;
	struct _ast*		pAst;
    float       fValue;
    char*       name;
};

%left <name> Y_ID
%left Y_LPAR 
%token <iValue> Y_INT Y_FLOAT Y_VOID Y_CONST
%token Y_IF Y_ELSE Y_WHILE Y_BREAK Y_CONTINUE Y_RETURN
%token <iValue> Y_ADD Y_SUB Y_MUL Y_DIV Y_MODULO Y_LESS Y_LESSEQ Y_GREAT Y_GREATEQ Y_NOTEQ Y_EQ Y_NOT Y_AND Y_OR Y_ASSIGN
%token Y_RPAR Y_LBRACKET Y_RBRACKET Y_LSQUARE Y_RSQUARE Y_COMMA Y_SEMICOLON
%token <iValue> num_INT
%token <fValue> num_FLOAT
%type <pAst> CompUnit CompUnits Decl ConstDecl ConstDefs ConstDef ConstExps ConstInitVal ConstInitVals VarDecl VarDecls 
%type <pAst> VarDef InitVal InitVals FuncDef FuncParams FuncParam Block BlockItems BlockItem Stmt Exp LVal ArraySubscripts 
%type <pAst> PrimaryExp UnaryExp CallParams MulExp AddExp EqExp LAndExp LOrExp 
%type <pAst> Type RelExp FuncCall


%%
CompUnits:CompUnit      {$$ = newNextNode($1,NULL); node = $$;}
         |CompUnit CompUnits   {$$ = newNextNode($1,$2); node = $$;}
        ;

CompUnit: Decl          {$$ = $1;}
         |FuncDef       {$$ = $1;}
         ;

Decl:ConstDecl          {$$ = $1;}
    |VarDecl            {$$ = $1;}
    ;

ConstDecl:Y_CONST Type ConstDefs Y_SEMICOLON    {past Node = $3;Node->ivalue = 1;$$ = $3;}
        ;

ConstDefs:ConstDef                              {$$ = newNextNode($1,NULL);}
         |ConstDef Y_COMMA ConstDefs            {$$ = newNextNode($1,$3);}
         ;

ConstDef:Y_ID Y_ASSIGN ConstInitVal             {$$ = newVarDef(VAR_DECL,newIDNode($1),$3,0);}
        |Y_ID ConstExps Y_ASSIGN ConstInitVal   {$$ = newVarDef(VAR_DECL,newNextNode(newIDNode($1),$2),$4,0);}
        ;

ConstExps:Y_LSQUARE Exp Y_RSQUARE          {$$ = newNextNode($2,NULL);single_num = $2->ivalue;}
        |Y_LSQUARE Exp Y_RSQUARE ConstExps {$$ = newNextNode($2,$4);}
        ;

//some changes happened here
ConstInitVal:Exp                         {$$ = $1;}
            |Y_LBRACKET Y_RBRACKET              {$$ = newConstInitVal(INIT_LIST_EXPR,NULL);}
            |Y_LBRACKET ConstInitVals Y_RBRACKET {$$ = newConstInitVal(INIT_LIST_EXPR,$2);}
            ;

ConstInitVals:ConstInitVal                      {$$ = newNextNode($1,NULL);}
             |ConstInitVal Y_COMMA ConstInitVals{$$  = newNextNode($1,$3);}
             ;

//some changes happened here
VarDecl:Type VarDecls Y_SEMICOLON         {$$ = $2;}
;
       

VarDecls:VarDef                             {$$ = newNextNode($1,NULL);}
        |VarDef Y_COMMA VarDecls            {$$ = newNextNode($1,$3);}
        ;

VarDef:Y_ID                         {$$ = newVarDef(VAR_DECL,newIDNode($1),NULL,0);}
      |Y_ID Y_ASSIGN InitVal        {$$ = newVarDef(VAR_DECL,newIDNode($1),$3,0);}
      |Y_ID ConstExps               {$$ = newVarDef(VAR_DECL,newNextNode(newIDNode($1),$2),NULL,0);}
      |Y_ID ConstExps Y_ASSIGN InitVal 
      {
        past tmp = $4;
        past Node = tmp->left;
        while(Node!=NULL){
                if(Node->fvalue != 1){
                        count++;
                        if(count==1){
                                tmp_node=Node;
                        }
                }
                else{
                        already++;
                        if(already==1){
                                tmp->left = Node;
                                trans = Node->next;
                                Node->next = NULL;
                                Node = trans;
                                tmp = tmp->left;
                        }
                        else {
                                tmp->next = Node;
                                 trans = Node->next;
                                Node->next = NULL;
                                Node = trans;
                                tmp = tmp->next;
                        }
                        continue;
                }
                if(count == single_num) {
                        already++;
                        if(already == 1){
                                tmp->left = newInitVal(INIT_LIST_EXPR,tmp_node,1);
                                trans = Node->next;
                                Node->next = NULL;
                                Node = trans;
                                tmp = tmp->left;

                        }
                        else {
                                tmp->next = newInitVal(INIT_LIST_EXPR,tmp_node,1);
                                trans = Node->next;
                                Node->next = NULL;
                                Node = trans;
                                tmp = tmp->next;
                        }
                        count=0;
                        continue;
                }
                Node = Node->next;
        }
        already = 0;
        tmp = NULL;
        count = 0;
        tmp_node = NULL;
        $$ = newVarDef(VAR_DECL,newNextNode(newIDNode($1),$2),$4,0);
      }
      ;

//some changes happened here
InitVal:Exp                         {$$ = $1;}
       |Y_LBRACKET Y_RBRACKET          {$$ = newInitVal(INIT_LIST_EXPR,NULL,1);}
       |Y_LBRACKET InitVals Y_RBRACKET   {$$ = newInitVal(INIT_LIST_EXPR,$2,1);}
       ;

InitVals:InitVal            {$$ = $1;}
        |InitVal Y_COMMA InitVals   {$$ = newNextNode($1,$3);}
        ;

FuncDef:Type Y_ID Y_LPAR Y_RPAR Block   {$$ = newFuncDef(FUNCTION_DECL,newIDNode($2),NULL,$5);}
       |Type Y_ID Y_LPAR FuncParams Y_RPAR Block {$$ = newFuncDef(FUNCTION_DECL,newIDNode($2),$4,$6);}
       ;

FuncParams:FuncParam            {$$ = newNextNode($1,NULL);}
          |FuncParam Y_COMMA FuncParams     {$$ = newNextNode($1,$3);}
          ;

FuncParam:Type Y_ID             {$$ = newFuncParam(PARM_DECL,newIDNode($2),NULL);}
         |Type Y_ID Y_LSQUARE Y_RSQUARE     {$$ = newFuncParam(PARM_DECL,newNextNode(newIDNode($2),newAstNode()),NULL);}
         |Type Y_ID ArraySubscripts     {$$ = newFuncParam(PARM_DECL,newNextNode(newIDNode($2),$3),NULL);}
         |Type Y_ID Y_LSQUARE Y_RSQUARE ArraySubscripts     {$$ = newFuncParam(PARM_DECL,newNextNode(newIDNode($2),newAstNode()),$5);}
         ;

Block:Y_LBRACKET BlockItems Y_RBRACKET  {$$ = newCompoundStmt(COMPOUND_STMT,$2);}
     |Y_LBRACKET Y_RBRACKET     {$$ = newCompoundStmt(COMPOUND_STMT,NULL);}
     ;

BlockItems:BlockItem    {$$ = newNextNode($1,NULL);}
          |BlockItem BlockItems     {$$ = newNextNode($1,$2);}
          ;

BlockItem:Decl      {past Node = $1;if(Node->ivalue == 0) $$ = newDeclStmt(DECL_STMT,$1);else $$ = $1;}
         |Stmt      {$$ = $1;}
         ;

Stmt:LVal Y_ASSIGN Exp Y_SEMICOLON      {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
    |Y_SEMICOLON                        {$$ = NULL;}
    |Exp Y_SEMICOLON                    {$$ = $1;}
    |Block                              {$$ = $1;}
    |Y_WHILE Y_LPAR LOrExp Y_RPAR Stmt  {$$ = newWhileStmt(WHILE_STMT,$3,$5);}
    |Y_IF Y_LPAR LOrExp Y_RPAR Stmt     {$$ = newIfStmt(IF_STMT,$3,$5,NULL);}
    |Y_IF Y_LPAR LOrExp Y_RPAR Stmt Y_ELSE Stmt     {$$ = newIfStmt(IF_STMT,$3,$5,$7);}
    |Y_BREAK Y_SEMICOLON            {$$ = newBreakStmt(BREAK_STMT);}
    |Y_CONTINUE Y_SEMICOLON         {$$ = newContinueStmt(CONTINUE_STMT);}
    |Y_RETURN Exp Y_SEMICOLON       {$$ = newReturnStmt(RETURN_STMT,$2);}
    |Y_RETURN Y_SEMICOLON           {$$ = newReturnStmt(RETURN_STMT,NULL);}
    ;

Exp:AddExp
;

LVal:Y_ID           {$$ = newDeclRefExp(DECL_REF_EXPR,newIDNode($1));}
    |Y_ID ArraySubscripts   {$$ = newDeclRefExp(DECL_REF_EXPR,newIDNode($1));past Node = $2;if(Node->left!=NULL) {Node->left->left = $$;$$=$2;}else{$2->left = $$,$$ = $2;}}
    ;

ArraySubscripts:Y_LSQUARE Exp Y_RSQUARE     {past Node = newAstNode();Node->right = $2;Node->nodeType = ARRAY_SUBSCRIPT_EXPR;$$ = Node;}
               |Y_LSQUARE Exp Y_RSQUARE ArraySubscripts     {$$ = newArrSubExp(ARRAY_SUBSCRIPT_EXPR,$2,$4);}
               ;

PrimaryExp:Y_LPAR Exp Y_RPAR        {$$ = newParenExp(PAREN_EXPR,$2);}         
          |LVal                     {$$ = $1;}
          |num_INT                  {$$ = newInt($1);}
          |num_FLOAT                {$$ = newFloat($1);}
          ;

          

UnaryExp:PrimaryExp         {$$ = $1;}
        |FuncCall           {$$ = $1;}
        |Y_ADD UnaryExp     {$$ = newUnaryExp(UNARY_OPERATOR,$1,$2);}
        |Y_SUB UnaryExp     {$$ = newUnaryExp(UNARY_OPERATOR,$1,$2);}
        |Y_NOT UnaryExp     {$$ = newUnaryExp(UNARY_OPERATOR,$1,$2);}
        ;

FuncCall:Y_ID Y_LPAR Y_RPAR {$$ = newCallExp(CALL_EXPR,newDeclRefExp(DECL_REF_EXPR,newIDNode($1)),NULL);}
        |Y_ID Y_LPAR CallParams Y_RPAR {$$ = newCallExp(CALL_EXPR,newDeclRefExp(DECL_REF_EXPR,newIDNode($1)),$3);}
        ;

CallParams:Exp              {$$ = newNextNode($1,NULL);}
          |Exp Y_COMMA CallParams       {$$ = newNextNode($1,$3);}
          ;

MulExp:UnaryExp             {$$ = $1;}
      |MulExp Y_MUL UnaryExp    {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      |MulExp Y_DIV UnaryExp    {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      |MulExp Y_MODULO UnaryExp {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      ;

AddExp:MulExp               {$$ = $1;}
      |AddExp Y_ADD MulExp  {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      |AddExp Y_SUB MulExp  {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      ;

RelExp:Exp               {$$ = $1;}
      |Exp Y_LESS Exp {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      |Exp Y_GREAT Exp    {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      |Exp Y_LESSEQ Exp   {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      |Exp Y_GREATEQ Exp  {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      ;

EqExp:RelExp    {$$ = $1;}
     |RelExp Y_EQ EqExp {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
     |RelExp Y_NOTEQ EqExp  {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
     ;

LAndExp:EqExp       {$$ = $1;}
       |EqExp Y_AND LAndExp {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
       ;

LOrExp:LAndExp      {$$ = $1;}
      |LAndExp Y_OR LOrExp  {$$ = newBinaryOpre(BINARY_OPERATOR,$2,$1,$3);}
      ;

Type:Y_INT  {$$ = NULL;}
    |Y_FLOAT {$$ = NULL;}
    |Y_VOID {$$ = NULL;}
%%
