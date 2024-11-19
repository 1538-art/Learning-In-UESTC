    1 CompUnit: Decl CompUnit
    2         | FuncDef CompUnit
    3         | Decl
    4         | FuncDef

    5 Decl: ConstDecl
    6     | VarDecl

    7 ConstDecl: Y_CONST Type ConstDef Y_SEMICOLON
    8          | Y_CONST Type ConstDefs Y_SEMICOLON

    9 ConstDefs: ConstDef Y_COMMA ConstDef
   10          | ConstDefs Y_COMMA ConstDef

   11 ConstDef: Y_ID Y_ASSIGN ConstInitVal
   12         | Y_ID ConstExps Y_ASSIGN ConstInitVal

   13 ConstExps: Y_LSQUARE ConstExp Y_RSQUARE
   14          | Y_LSQUARE ConstExp Y_RSQUARE ConstExps

   15 ConstInitVal: ConstExp
   16             | Y_LBRACKET Y_RBRACKET
   17             | Y_LBRACKET ConstInitVal Y_RBRACKET
   18             | Y_LBRACKET ConstInitVal ConstInitVals Y_RBRACKET

   19 ConstInitVals: Y_COMMA ConstInitVal
   20              | Y_COMMA ConstInitVal ConstInitVals

   21 VarDecl: Type VarDef Y_SEMICOLON
   22        | Type VarDef VarDecls Y_SEMICOLON

   23 VarDecls: Y_COMMA VarDef
   24         | Y_COMMA VarDef VarDecls

   25 VarDef: Y_ID
   26       | Y_ID Y_ASSIGN InitVal
   27       | Y_ID ConstExps
   28       | Y_ID ConstExps Y_ASSIGN InitVal

   29 InitVal: Exp
   30        | Y_LBRACKET Y_RBRACKET
   31        | Y_LBRACKET InitVal Y_RBRACKET
   32        | Y_LBRACKET InitVal InitVals Y_RBRACKET

   33 InitVals: Y_COMMA InitVal
   34         | Y_COMMA InitVal InitVals

   35 FuncDef: Type Y_ID Y_LPAR Y_RPAR Block
   36        | Type Y_ID Y_LPAR FuncParams Y_RPAR Block

   37 FuncParams: FuncParam
   38           | FuncParams Y_COMMA FuncParam

   39 FuncParam: Type Y_ID
   40          | Type Y_ID Y_LSQUARE Y_RSQUARE
   41          | Type Y_ID ArraySubscripts
   42          | Type Y_ID Y_LSQUARE Y_RSQUARE ArraySubscripts

   43 Block: Y_LBRACKET BlockItems Y_RBRACKET
   44      | Y_LBRACKET Y_RBRACKET

   45 BlockItems: BlockItem
   46           | BlockItem BlockItems

   47 BlockItem: Decl
   48          | Stmt

   49 Stmt: LVal Y_ASSIGN Exp Y_SEMICOLON
   50     | Y_SEMICOLON
   51     | Exp Y_SEMICOLON
   52     | Block
   53     | Y_WHILE Y_LPAR LOrExp Y_RPAR Stmt
   54     | Y_IF Y_LPAR LOrExp Y_RPAR Stmt
   55     | Y_IF Y_LPAR LOrExp Y_RPAR Stmt Y_ELSE Stmt
   56     | Y_BREAK Y_SEMICOLON
   57     | Y_CONTINUE Y_SEMICOLON
   58     | Y_RETURN Exp Y_SEMICOLON
   59     | Y_RETURN Y_SEMICOLON

   60 Exp: AddExp

   61 LVal: Y_ID
   62     | Y_ID ArraySubscripts

   63 ArraySubscripts: Y_LSQUARE Exp Y_RSQUARE
   64                | Y_LSQUARE Exp Y_RSQUARE ArraySubscripts

   65 PrimaryExp: Y_LPAR Exp Y_RPAR
   66           | LVal
   67           | num_INT
   68           | num_FLOAT

   69 UnaryExp: PrimaryExp
   70         | Y_ID Y_LPAR Y_RPAR
   71         | Y_ID Y_LPAR CallParams Y_RPAR
   72         | Y_ADD UnaryExp
   73         | Y_SUB UnaryExp
   74         | Y_NOT UnaryExp

   75 CallParams: Exp
   76           | Exp Y_COMMA CallParams

   77 MulExp: UnaryExp
   78       | MulExp Y_MUL UnaryExp
   79       | MulExp Y_DIV UnaryExp
   80       | MulExp Y_MODULO UnaryExp

   81 AddExp: MulExp
   82       | AddExp Y_ADD MulExp
   83       | AddExp Y_SUB MulExp

   84 RelExp: AddExp
   85       | AddExp Y_LESS RelExp
   86       | AddExp Y_GREAT RelExp
   87       | AddExp Y_LESSEQ RelExp
   88       | AddExp Y_GREATEQ RelExp

   89 EqExp: RelExp
   90      | RelExp Y_EQ EqExp
   91      | RelExp Y_NOTEQ EqExp

   92 LAndExp: EqExp
   93        | EqExp Y_AND LAndExp

   94 LOrExp: LAndExp
   95       | LAndExp Y_OR LOrExp

   96 ConstExp: AddExp

   97 Type: Y_INT
   98     | Y_FLOAT
   99     | Y_VOID
