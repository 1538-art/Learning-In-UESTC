%{

#include "ast.h"
#include <stdio.h>

void yyerror(char *);
int yylex(void);
extern char* yytext;
extern past astRoot;
%}

%union{
	int		number;
	char		strValue[50];
	past		pAst;
};

%token			  IF
%token			  ELSE
%token			  INT
%token			  VOID
%token			  CONST
%token			  WHILE
%token			  BREAK
%token			  RETURN
%token			  CONTINUE
%token			  LESSEQ
%token			  GREATEQ
%token			  NOTEQ
%token			  EQ
%token			  AND
%token			  OR
%token      <strValue>    ID
%token      <number>      NUMBER
%type       <pAst>	  CompUnit CompUnits Decl ConstDecl ConstDef ConstInitVal VarDecl VarDef InitVal FuncDef FuncFParams FuncFParam Block BlockItem Stmt Exp Cond LVal PrimaryExp Number UnaryExp FuncRParams MulExp AddExp RelExp EqExp LAndExp LOrExp ConstExp ConstDeclMul ConstDefMul ConstInitValMul VarDeclMul VarDefMul InitValMul BlockMul LValMul 

%%

CompUnits: CompUnit                      {$$ = newNextNode("CompUnit", $1, NULL); astRoot = $$;}
	| CompUnits CompUnit             {$$ = newNextNode("CompUnit", $1, $2); astRoot = $$;}
	;

CompUnit: Decl                      {$$ = $1;}
      | FuncDef                     {$$ = $1;}
      ;

Decl: ConstDecl               {$$ = newBasicNode("Decl", $1, NULL, NULL);}
      | VarDecl               {$$ = newBasicNode("Decl", $1, NULL, NULL);}
      ;

ConstDeclMul: ConstDef                    {$$ = newNextNode("ConstDecl_list", $1, NULL);}
      | ConstDeclMul ',' ConstDef         {$$ = newNextNode("ConstDecl_list", $1, $3);}
      ;

ConstDecl: CONST INT ConstDeclMul ';'              {$$ = newBasicNode("ConstDecl",newTypeNode("const_int"), $3, NULL);}
      ;

ConstDefMul: '[' ConstExp ']'                   {$$ = newNextNode("ConstDef_list", $2, NULL);}
      | ConstDefMul '[' ConstExp ']'            {$$ = newNextNode("ConstDef_list", $1, $3);}
      ;

ConstDef: ID '=' ConstInitVal                   {$$ = newBasicNode("ConstDef",newIDNode($1),$3,NULL);}
      | ID ConstDefMul '=' ConstInitVal         {$$ = newBasicNode("ConstDef",newNextNode("ConstDef_para", newIDNode($1), $2), $4, NULL);}
      ;

ConstInitValMul: ConstInitVal                   {$$ = newNextNode("ConstInitVal_list", $1, NULL);}
      | ConstInitValMul ',' ConstInitVal        {$$ = newNextNode("ConstInitVal_list", $1, $3);}
      ;

ConstInitVal: ConstExp                   {$$ = $1;}
      | '{' '}'                          {$$ = newBasicNode("ConstInitVal_empty",NULL, NULL, NULL);}
      | '{' ConstInitValMul '}'          {$$ = $2;}
      ;

VarDeclMul: VarDef                       {$$ = newNextNode("VarDecl_list", $1, NULL);}
      | VarDeclMul ',' VarDef            {$$ = newNextNode("VarDecl_list", $1, $3);}
      ;

VarDecl: INT VarDeclMul ';'            {$$ = newBasicNode("VarDecl", newTypeNode("int"), $2, NULL);}
      ;

VarDefMul: '[' ConstExp ']'              {$$ = newNextNode("VarDef_list", $2, NULL);}
      | VarDefMul '[' ConstExp ']'       {$$ = newNextNode("VarDef_list", $1, $3);}
      ;

VarDef: ID                               {$$ = newBasicNode("VarDef", newIDNode(yylval.strValue), NULL,NULL);}
      | ID '=' InitVal                   {$$ = newBasicNode("VarDef", newIDNode($1), $3, NULL);}
      | ID VarDefMul                     {$$ = newBasicNode("VarDef",newNextNode("VarDef_para", newIDNode($1), $2), NULL, NULL);}
      | ID VarDefMul '=' InitVal         {$$ = newBasicNode("VarDef",newNextNode("VarDef_para", newIDNode($1), $2), $4, NULL);}
      ;

InitValMul: InitVal                      {$$ = newNextNode("InitVal_list", $1, NULL);}
      | InitValMul ',' InitVal           {$$ = newNextNode("InitVal_list", $1, $3);}
      ;

InitVal: Exp                             {$$ = $1;}
      | '{' '}'                          {$$ = newBasicNode("InitVal_empty", NULL, NULL, NULL);}
      | '{' InitValMul '}'               {$$ = $2;}
      ;

FuncDef: VOID ID '('  ')' Block                   {$$ = newBasicNode("FuncDef",newNextNode("FuncDef_para", newTypeNode("void"), newIDNode($2)), $5, NULL);}
      | INT ID '('  ')' Block                     {$$ = newBasicNode("FuncDef",newNextNode("FuncDef_para", newTypeNode("int"), newIDNode($2)), $5, NULL);}
      | VOID ID '(' FuncFParams ')' Block         {past id = newIDNode($2); id -> left = $4;
                                                   $$ = newBasicNode("FuncDef",newNextNode("FuncDef_para", newTypeNode("void"), id), $6, NULL);}
      | INT ID '(' FuncFParams ')' Block          {past id = newIDNode($2); id -> left = $4;
                                                   $$ = newBasicNode("FuncDef",newNextNode("FuncDef_para", newTypeNode("int"), id), $6, NULL);}
      ;

FuncFParams: FuncFParam                         {$$ = newNextNode("FuncFParams_list", $1, NULL);}
      |  FuncFParams ',' FuncFParam             {$$ = newNextNode("FuncFParams_list", $1, $3);}
      ;

FuncFParam: INT ID                      {$$ = newBasicNode("FuncFParam",newNextNode("FuncFParam_para", newTypeNode("int"), newIDNode($2)), NULL, NULL);}
      | INT ID '[' ']'                  {$$ = newBasicNode("FuncFParam",newNextNode("FuncFParam_para", newTypeNode("int"), newIDNode($2)), NULL, NULL);}
      | INT ID '[' ']' LValMul          {$$ = newBasicNode("FuncFParam",newNextNode("FuncFParam_para", newTypeNode("int"), newIDNode($2)), $5, NULL);}
      ;

BlockMul: BlockItem                 {$$ = newNextNode("Block_list", $1, NULL);}
      | BlockMul BlockItem          {$$ = newNextNode("Block_list", $1, $2);}
      ;

Block:  '{' '}'                     {$$ = newBasicNode("Block_empty", NULL, NULL, NULL);}
      | '{' BlockMul '}'            {$$ = $2;}
      ; 

BlockItem: Decl         {$$ = $1;}
      | Stmt            {$$ = $1;}
      ;

Stmt: LVal '=' Exp ';'                          {$$ = newBasicNode("Assign_Stmt", $1, $3, NULL);}
      | Exp ';'                                 {$$ = $1;}
      | ';'                                     {$$ = newBasicNode("Stmt_empty", NULL, NULL, NULL);}
      | Block                                   {$$ = $1;}
      | IF '(' Cond ')' Stmt                     {$$ = newBasicNode("If_Stmt", $3, $5, NULL);}
      | IF '(' Cond ')' Stmt ELSE Stmt           {$$ = newBasicNode("IfElse_Stmt", $3, newNextNode("If_Else", $5, $7), NULL);}
      | WHILE '(' Cond ')' Stmt                 {$$ = newBasicNode("While_Stmt", $3, $5, NULL);}
      | BREAK ';'                               {$$ = newBasicNode("Break_Stmt",NULL,NULL,NULL);}
      | CONTINUE ';'                            {$$ = newBasicNode("Continue_Stmt",NULL,NULL,NULL);}
      | RETURN Exp ';'                          {$$ = newBasicNode("Return_Stmt",$2,NULL,NULL);}
      | RETURN ';'                              {$$ = newBasicNode("Return_Stmt",NULL,NULL,NULL);}
      ;

Exp: AddExp             {$$ = $1;}
      ;

Cond: LOrExp             {$$ = $1;}
      ;

LValMul: '[' Exp ']'                {$$ = newNextNode("Exp_list", $2, NULL);}
      |  LValMul '[' Exp ']'        {$$ = newNextNode("Exp_list", $1, $3);}
      ;

LVal: ID                {$$ = newIDNode(yylval.strValue);}
      | ID LValMul      {$$ = newBasicNode("LVal_SEG", newIDNode($1), $2, NULL);}
      ;

PrimaryExp: '(' Exp ')'       {$$ = $2;}
            | LVal            {$$ = $1;}
            | Number          {$$ = $1;}
            ;

Number: NUMBER                {$$ = newNum(yylval.number);}
      ;

UnaryExp: PrimaryExp                {$$ = $1;}
      | ID '(' ')'                  {$$ = newBasicNode("UnaryExp", newIDNode($1), NULL, NULL);}
      | ID '(' FuncRParams ')'      {$$ = newBasicNode("UnaryExp", newIDNode($1), $3, NULL);}
      | '+' UnaryExp                {$$ = newBasicNode("UnaryExp", newExpr('+', NULL, $2), NULL, NULL);}
      | '-' UnaryExp                {$$ = newBasicNode("UnaryExp", newExpr('-', NULL, $2), NULL, NULL);}
      | '!' UnaryExp                {$$ = newBasicNode("UnaryExp", newExpr('!', NULL, $2), NULL, NULL);}
      ;

FuncRParams: Exp                          {$$ = newNextNode("FuncRParams_list", $1, NULL);}
            | FuncRParams ',' Exp         {$$ = newNextNode("FuncRParams_list", $1, $3);}
            ;

MulExp: UnaryExp                          {$$ = $1;}
      | MulExp '*' UnaryExp               {$$ = newExpr('*', $1, $3);}
      | MulExp '/' UnaryExp               {$$ = newExpr('/', $1, $3);}
      | MulExp '%' UnaryExp               {$$ = newExpr('%', $1, $3);}
      ;

AddExp: MulExp                           {$$ = $1;}
      | AddExp '+'  MulExp               {$$ = newExpr('+', $1, $3);}
      | AddExp '-'  MulExp               {$$ = newExpr('-', $1, $3);}
      ;

RelExp: AddExp                            {$$ = $1;}
      | RelExp '<' AddExp                 {$$ = newExpr('<', $1, $3);}
      | RelExp LESSEQ AddExp              {$$ = newDoubleExpr("<=", $1, $3);}
      | RelExp GREATEQ AddExp             {$$ = newDoubleExpr(">=", $1, $3);}
      | RelExp '>' AddExp                 {$$ = newExpr('>', $1, $3);}
      ;

EqExp: RelExp                       {$$ = $1;}
      | EqExp EQ RelExp             {$$ = newDoubleExpr("==", $1, $3);}
      | EqExp NOTEQ RelExp          {$$ = newDoubleExpr("!=", $1, $3);} 
      ;

LAndExp: EqExp                           {$$ = $1;}
         | LAndExp AND EqExp             {$$ = newDoubleExpr("&&", $1, $3);}
         ;

LOrExp: LAndExp                         {$$ = $1;}
        | LOrExp OR LAndExp             {$$ = newDoubleExpr("||", $1, $3);}
        ;

ConstExp: AddExp              {$$ = $1;}
      ;

%%
