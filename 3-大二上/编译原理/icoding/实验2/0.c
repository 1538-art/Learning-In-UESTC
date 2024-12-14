/*
 * 完成人　：2023091602014(张烨涛)
 * 评测时间：2024-11-28, Thu, 20:59:01
 * 系统评分：100
 */


#include "rdlab2.h"
#include <stdbool.h>

// 声明函数
past newBinaryOper(int oper, past left, past right);        // 创建一个新的二元操作节点
past newDeclRefExp(char *name, past left, past right);      // 创建一个新的声明引用表达式节点
past newWhileStmt(past condition, past body);               // 创建一个新的 while 语句节点
past newIfStmt(past condition, past ifBody, past elseBody); // 创建一个新的 if 语句节点
past newBreakStmt();                                        // 创建一个新的 break 语句节点
past newContinueStmt();                                     // 创建一个新的 continue 语句节点
past newReturnStmt(past left, past right);                  // 创建一个新的 return 语句节点

past rd_add_exp();     // 解析加法和减法表达式
past rd_mul_exp();     // 解析乘法、除法和取模表达式
past rd_unary_exp();   // 解析一元表达式
past rd_primary_exp(); // 解析基本表达式
past rd_l_or_exp();    // 解析逻辑或表达式
past rd_l_and_exp();   // 解析逻辑与表达式
past rd_eq_exp();      // 解析相等性表达式
past rd_call_paras();  // 解析函数调用参数列表
past rd_relexp();      // 解析关系运算表达式
past rd_stmt();        // 解析语句
// 函数定义

// 创建一个新的二元操作节点
past newBinaryOper(int oper, past left, past right)
{
    past node = newAstNode();
    if (node)
    {
        // 设置节点的类型为二进制操作符
        node->nodeType = BINARY_OPERATOR;
        // 存储操作符
        node->ivalue = oper;
        // 存储左右操作数
        node->left = left;
        node->right = right;
    }
    return node;
}

// 创建一个新的声明引用表达式节点
past newDeclRefExp(char *name, past left, past right)
{
    past node = newAstNode();
    if (node)
    {
        // 设置节点的类型为声明引用表达式
        node->nodeType = DECL_REF_EXPR;
        // 存储名称
        node->svalue = name;
        // 存储左右子节点
        node->left = left;
        node->right = right;
    }
    return node;
}

// 创建一个新的 while 语句节点
past newWhileStmt(past condition, past body)
{
    past node = newAstNode();
    if (node)
    {
        // 设置节点的类型为 while 语句
        node->nodeType = WHILE_STMT;
        // 存储条件表达式和循环体
        node->left = condition;
        node->right = body;
    }
    return node;
}

// 创建一个新的 if 语句节点
past newIfStmt(past condition, past ifBody, past elseBody)
{
    past node = newAstNode();
    if (node)
    {
        // 设置节点的类型为 if 语句
        node->nodeType = IF_STMT;
        // 存储条件表达式、if 分支和else分支
        node->if_cond = condition;
        node->left = ifBody;
        node->right = elseBody;
    }
    return node;
}

// 创建一个新的 break 语句节点
past newBreakStmt()
{
    past node = newAstNode();
    if (node)
    {
        // 设置节点的类型为 break 语句
        node->nodeType = BREAK_STMT;
    }
    return node;
}

// 创建一个新的 continue 语句节点
past newContinueStmt()
{
    past node = newAstNode();
    if (node)
    {
        // 设置节点的类型为 continue 语句
        node->nodeType = CONTINUE_STMT;
    }
    return node;
}

// 创建一个新的 return 语句节点
past newReturnStmt(past left, past right)
{
    past node = newAstNode();
    if (node)
    {
        // 设置节点的类型为 return 语句
        node->nodeType = RETURN_STMT;
        // 存储返回表达式
        node->left = left;
        node->right = right;
    }
    return node;
}

// 解析基本表达式
past rd_primary_exp()
{
    past node = NULL; // 初始化节点为NULL

    if (cur_token.token == Y_LPAR)
    { // (表达式)
        advance();
        node = rd_add_exp(); // 见下面的rd_add_exp()函数
        if (cur_token.token != Y_RPAR)
        { // 缺右括号
            return NULL;
        }
        advance();
    }
    else if (cur_token.token == Y_ID)
    { // LVal
        char *s = cur_token.attr.svalue;
        past Arr = rd_array_subscripts();
        node = newDeclRefExp(s, Arr, NULL);
        advance();
    }
    else if (cur_token.token == num_INT)
    {
        node = newInt(cur_token.attr.ivalue); // 构造整数节点
        advance();
    }
    else if (cur_token.token == num_FLOAT)
    {
        node = newAstNode(); // 构造浮点数节点
        advance();
        node->fvalue = cur_token.attr.fvalue;
    }

    return node; // 返回表达式树
}

// 解析一元表达式
past rd_unary_exp()
{
    past node = rd_primary_exp(); // 获取基本表达式

    while (node == NULL)
    { // 当基本表达式为空时
        if (cur_token.token == Y_ID)
        { // 当当前符号为标识符时
            char *s = cur_token.attr.svalue;
            advance();
            if (cur_token.token == Y_LPAR)
            {
                advance();
                past params;
                if (cur_token.token != Y_RPAR)
                {
                    params = rd_call_paras(); // 解析函数调用参数
                }
                node = newDeclRefExp(s, params, NULL); // 构造声明引用表达式
            }
        }
        else if (cur_token.token == Y_ADD || cur_token.token == Y_SUB || cur_token.token == Y_NOT)
        {                               // 当当前符号为加号、减号或取反符号
            int oper = cur_token.token; // 记录运算符
            advance();
            past operand = rd_unary_exp();             // 获取一元表达式
            node = newBinaryOper(oper, NULL, operand); // 构造二元操作表达式
        }
        else
        {
            return NULL; // 无法匹配其他情况，返回空
        }
    }

    return node; // 返回表达式树
}

// 解析加法表达式
past rd_add_exp()
{
    past left = rd_mul_exp(); // 获取乘法表达式

    while (cur_token.token == Y_ADD || cur_token.token == Y_SUB)
    {                               // 当当前符号为加号或减号时
        int oper = cur_token.token; // 记录运算符
        advance();
        past right = rd_mul_exp();               // 获取乘法表达式
        left = newBinaryOper(oper, left, right); // 构造二元操作表达式
    }

    return left; // 返回表达式树
}

// 解析乘法表达式
past rd_mul_exp()
{
    past left = rd_unary_exp(); // 获取一元表达式

    while (cur_token.token == Y_MUL || cur_token.token == Y_DIV || cur_token.token == Y_MODULO)
    {                               // 当当前符号为乘号、除号或取模符号时
        int oper = cur_token.token; // 记录运算符
        advance();
        past right = rd_unary_exp();             // 获取一元表达式
        left = newBinaryOper(oper, left, right); // 构造二元操作表达式
    }

    return left; // 返回表达式树
}

// 解析相等表达式
past rd_eq_exp()
{
    past left = rd_relexp(); // 获取关系表达式

    while (cur_token.token == Y_EQ || cur_token.token == Y_NOTEQ)
    {                               // 当当前符号为等号或不等号时
        int oper = cur_token.token; // 记录运算符
        advance();
        past right = rd_relexp();                // 获取关系表达式
        left = newBinaryOper(oper, left, right); // 构造二元操作表达式
    }

    return left; // 返回表达式树
}

// 解析关系表达式
past rd_relexp()
{
    past left = rd_add_exp(); // 获取加法表达式

    while (true)
    {
        switch (cur_token.token)
        {
        case Y_LESS:
        case Y_LESSEQ:
        case Y_GREAT:
        case Y_GREATEQ:
        {                               // 当当前符号为小于、小于等于、大于或大于等于时
            int oper = cur_token.token; // 记录运算符
            advance();
            past right = rd_add_exp();               // 获取加法表达式
            left = newBinaryOper(oper, left, right); // 构造二元操作表达式
            break;
        }
        default:
            return left; // 返回表达式树
        }
    }
}

// 解析逻辑与表达式
past rd_l_and_exp()
{
    past left = rd_eq_exp(); // 获取相等表达式

    while (cur_token.token == Y_AND)
    {                               // 当当前符号为逻辑与符号时
        int oper = cur_token.token; // 记录运算符
        advance();
        past right = rd_eq_exp();                // 获取相等表达式
        left = newBinaryOper(oper, left, right); // 构造二元操作表达式
    }

    return left; // 返回表达式树
}

// 解析逻辑或表达式
past rd_l_or_exp()
{
    past left = rd_l_and_exp(); // 获取逻辑与表达式

    while (cur_token.token == Y_OR)
    {                               // 当当前符号为逻辑或符号时
        int oper = cur_token.token; // 记录运算符
        advance();
        past right = rd_l_and_exp();             // 获取逻辑与表达式
        left = newBinaryOper(oper, left, right); // 构造二元操作表达式
    }

    return left; // 返回表达式树
}

// 解析函数调用参数
past rd_call_paras()
{
    past head = rd_add_exp(); // 获取加法表达式
    past current = head;

    while (cur_token.token)
    {
        if (cur_token.token != Y_COMMA)
        { // 当当前符号不为逗号时
            break;
        }
        advance();
        past new_node = rd_add_exp(); // 获取加法表达式
        current->next = new_node;
        current = current->next;
    }

    return head; // 返回参数链表头节点
}

// 解析语句
past rd_stmt()
{
    switch (cur_token.token)
    {
    case Y_ID:
    {                                    // LVal 开头 ———— 赋值语句
        char *s = cur_token.attr.svalue; // 处理LVal（等号左边）
        past Arr = rd_array_subscripts();
        past lval = newDeclRefExp(s, Arr, NULL);
        advance();
        if (cur_token.token != Y_ASSIGN)
        { // 语法错误
            return NULL;
        }
        advance();
        past left = rd_add_exp(); // 获取加法表达式（等号右边）
        if (cur_token.token != Y_SEMICOLON)
        { // 语法错误
            return NULL;
        }
        advance();
        return newBinaryOper(Y_ASSIGN, lval, left); // 返回赋值表达式
    }
    case Y_SEMICOLON:
    { // 分号开头 ———— 空语句
        advance();
        return NULL;
    }
    case Y_LBRACKET:
    { // 左大括号开头 ———— 代码块
        advance();
        past block = rd_block(); // 获取块语句
        if (cur_token.token != Y_RBRACKET)
        { // 语法错误
            return NULL;
        }
        advance();
        return block; // 返回块语句
    }
    case Y_WHILE:
    { // WHILE语句
        advance();
        if (cur_token.token != Y_LPAR)
        { // 如果下一个符号不是左括号，语法错误
            return NULL;
        }
        advance();
        past condition = rd_l_or_exp(); // 获取逻辑或表达式
        if (cur_token.token != Y_RPAR)
        { // 如果下一个符号不是右括号，语法错误
            return NULL;
        }
        advance();
        past stmt = rd_stmt();                // 获取语句
        return newWhileStmt(condition, stmt); // 返回WHILE语句
    }
    case Y_IF:
    { // IF语句
        advance();
        if (cur_token.token != Y_LPAR)
        { // 如果下一个符号不是左括号，语法错误
            return NULL;
        }
        advance();
        past condition = rd_l_or_exp(); // 获取逻辑或表达式
        if (cur_token.token != Y_RPAR)
        { // 如果下一个符号不是右括号，语法错误
            return NULL;
        }
        advance();
        past if_stmt = rd_stmt(); // 获取语句
        if (cur_token.token != Y_ELSE)
        {                                               // 如果下一个符号不是ELSE关键字 ———— 无else
            return newIfStmt(condition, if_stmt, NULL); // 返回IF语句
        }
        advance();
        past else_stmt = rd_stmt();                      // 获取ELSE分支语句
        return newIfStmt(condition, if_stmt, else_stmt); // 返回IF-ELSE语句
    }
    case Y_BREAK:
    { // BREAK语句
        advance();
        if (cur_token.token != Y_SEMICOLON)
        { // 如果下一个符号不是分号，语法错误
            return NULL;
        }
        advance();
        return newBreakStmt(); // 返回BREAK语句
    }
    case Y_CONTINUE:
    { // CONTINUE语句
        advance();
        if (cur_token.token != Y_SEMICOLON)
        { // 如果下一个符号不是分号，语法错误
            return NULL;
        }
        advance();
        return newContinueStmt(); // 返回CONTINUE语句
    }
    case Y_RETURN:
    { // RETURN语句
        advance();
        past left = rd_add_exp(); // 获取加法表达式
        if (cur_token.token != Y_SEMICOLON)
        { // 如果下一个符号不是分号，语法错误
            return NULL;
        }
        advance();
        return newReturnStmt(left, NULL); // 返回RETURN语句
    }
    default:
        return NULL;
    }
}

