#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "genllvm.h"

int stack_top = 0;
int regCount = 1;
int varCount = 0;
int reg[40];
char *variables[40];
char *variable_type[40];
int whilecheckpoint[10];
int ifcheckpoint[10];
int if_stack_top = 0;
int process(past node, char *result);

void addLLVMCodes(char *codes)
{
    // 把生成的指令加入到指令队列，这里为了说明，仅用printf把生成的指令打印出来
    printf("%s", codes);
}
int checkVariable(char *variable_name)
{
    int res = 0;
    for (int i = 1; i < regCount; i++)
    {
        if (strcmp(variable_name, variables[i]) == 0)
        {
            res = i;
        }
    }

    return res;
}
int genExprStmt(past node, char *result)
{
    char *key = (char *)malloc(sizeof(char) * 5);
    char *left = (char *)malloc(sizeof(char) * 5);
    char *right = (char *)malloc(sizeof(char) * 5);
    int left_record = 0, right_record = 0;
    if (strcmp(node->strValue, "@") == 0 || strcmp(node->strValue, "==") == 0 || strcmp(node->strValue, "!=") == 0 || strcmp(node->strValue, ">=") == 0 || strcmp(node->strValue, "<=") == 0)
    {
        switch (node->ivalue)
        {
        case '+':
            sprintf(key, "add");
            break;
        case '-':
            sprintf(key, "sub");
            break;
        case '*':
            sprintf(key, "mul");
            break;
        case '/':
            sprintf(key, "div");
            break;
        default:
            sprintf(key, "else");
            break;
        }
        if (strcmp(node->left->nodeType, "intValue") == 0)
        {
            sprintf(left, "%d", node->left->ivalue);
        }
        else if (strcmp(node->left->nodeType, "parameter") == 0)
        {
            left_record = checkVariable(node->left->strValue);
            if (left_record != 0)
            {
                ++varCount;
                sprintf(left, "%%%d", varCount);
                char *tmp = (char *)malloc(sizeof(char) * 200);
                sprintf(tmp, "%%%d = load i32, i32* %%%d, align 4\n", varCount, reg[left_record]);
                result = strcat(result, tmp);
                free(tmp);
            }
        }
        else if (strcmp(node->left->nodeType, "expr") == 0)
        {
            sprintf(left, "%%%d", genExprStmt(node->left, result));
        }
        if (strcmp(node->right->nodeType, "intValue") == 0)
        {
            sprintf(right, "%d", node->right->ivalue);
        }
        else if (strcmp(node->right->nodeType, "parameter") == 0)
        {
            right_record = checkVariable(node->right->strValue);
            if (right_record != 0)
            {
                ++varCount;
                sprintf(right, "%%%d", varCount);
                char *tmp = (char *)malloc(sizeof(char) * 200);
                sprintf(tmp, "%%%d = load i32, i32* %%%d, align 4\n", varCount, reg[right_record]);
                result = strcat(result, tmp);
                free(tmp);
            }
        }
        else if (strcmp(node->right->nodeType, "expr") == 0)
        {
            sprintf(right, "%%%d", genExprStmt(node->right, result));
        }
        char *tmp = (char *)malloc(sizeof(char) * 200);
        if (strcmp(key, "else") == 0)
        {
            if (strcmp(node->strValue, "@") == 0 && node->ivalue == '>')
                sprintf(tmp, "%%%d = icmp %s i32 %s, %s\n", ++varCount, "sgt", left, right);
            else if (strcmp(node->strValue, "@") == 0 && node->ivalue == '<')
                sprintf(tmp, "%%%d = icmp %s i32 %s, %s\n", ++varCount, "slt", left, right);
            else if (strcmp(node->strValue, "==") == 0)
                sprintf(tmp, "%%%d = icmp %s i32 %s, %s\n", ++varCount, "eq", left, right);
            else if (strcmp(node->strValue, "!=") == 0)
                sprintf(tmp, "%%%d = icmp %s i32 %s, %s\n", ++varCount, "ne", left, right);
            else if (strcmp(node->strValue, ">=") == 0)
                sprintf(tmp, "%%%d = icmp %s i32 %s, %s\n", ++varCount, "sge", left, right);
            else if (strcmp(node->strValue, "<=") == 0)
                sprintf(tmp, "%%%d = icmp %s i32 %s, %s\n", ++varCount, "sle", left, right);
            strcat(result, tmp);
            free(tmp);
            free(key);
            free(left);
            free(right);
            return 0;
        }
        sprintf(tmp, "%%%d = %s i32 %s, %s\n", ++varCount, key, left, right);
        result = strcat(result, tmp);

        free(tmp);
        free(key);
        free(left);
        free(right);
        return varCount;
    }

    return 0;
}
int genDeclStmt(past node, char *result)
{
    if (strcmp(node->left->left->strValue, "int") == 0)
    {
        past l = node->left->right->left;
        for (int i = 0; i < node->left->right->ivalue; i++)
        {
            if (strcmp(l->right->nodeType, "intValue") == 0)
            {
                variables[regCount] = l->left->strValue;
                variable_type[regCount] = "int";
                reg[regCount++] = ++varCount;
                char *tmp = malloc(sizeof(char) * 200);
                sprintf(tmp, "%c%d = alloca i32, align 4\nstore i32 %d, i32* %c%d, align 4\n", '%', varCount, l->right->ivalue, '%',
                        varCount);
                strcat(result, tmp);
                free(tmp);
            }
            l = l->next;
        }
        return 0;
    }
}
int genAssignStmt(past node, char *result)
{
    char *tmp = malloc(sizeof(char) * 200);
    if (strcmp(node->right->nodeType, "expr") == 0)
    {
        int pos = checkVariable(node->left->strValue);
        sprintf(tmp, "store i32 %c%d , i32* %c%d, align 4\n", '%', genExprStmt(node->right, result), '%', reg[pos]);
        result = strcat(result, tmp);
        free(tmp);
        return 0;
    }
    else if (strcmp(node->right->nodeType, "intValue") == 0)
    {
        int pos = checkVariable(node->left->strValue);
        sprintf(tmp, "store i32 %d , i32* %c%d, align 4\n", node->right->ivalue, '%', reg[pos]);
        result = strcat(result, tmp);
        free(tmp);
        return 0;
    }
    else if (strcmp(node->right->nodeType, "parameter") == 0)
    {
        char *tmp1 = malloc(sizeof(char) * 200);
        sprintf(tmp1, "%%%d = load i32, i32* %%%d, align 4\n", ++varCount, reg[checkVariable(node->right->strValue)]);
        result = strcat(result, tmp1);
        free(tmp1);
        int pos = checkVariable(node->left->strValue);
        sprintf(tmp, "store i32 %c%d , i32* %c%d, align 4\n", '%', varCount, '%', reg[pos]);
        result = strcat(result, tmp);
        free(tmp);
        return 0;
    }
    else
    {
        free(tmp);
        result = "";
        return 0;
    }
}
int genIfStmt(past node, char *result)
{
    char *res = (char *)malloc(200);
    char *tmp = (char *)malloc(200);
    genExprStmt(node->left, result);
    char *tmp2 = (char *)malloc(sizeof(char) * 200);
    sprintf(tmp2, "br i1 %c%d, label %c%d, label %c%d\n; <label>:%d:\n", '%', varCount, '%', varCount + 1, '%', varCount + 2, varCount + 1);
    varCount++;
    result = strcat(result, tmp2);
    process(node->right, result);
    char *tmp3 = (char *)malloc(sizeof(char) * 200);
    ++varCount;
    sprintf(tmp3, "br label %c%d\n; <label>:%d:\n", '%', varCount, varCount);
    result = strcat(result, tmp3);
    free(tmp);
    free(res);
    return 0; // res
}
int genIfElseStmt(past node, char *result)
{
    char *res = (char *)malloc(200);
    char *tmp = (char *)malloc(200);
    genExprStmt(node->left, result);
    ifcheckpoint[if_stack_top++] = varCount;
    char *tmp2 = (char *)malloc(sizeof(char) * 200);
    sprintf(tmp2, "br i1 %c%d, label %c%d, label %c%d\n; <label>:%d:\n", '%', varCount, '%', varCount + 1, '%', varCount + 2, varCount + 1);
    varCount++;
    result = strcat(result, tmp2);
    process(node->right->left, result);
    char *tmp3 = (char *)malloc(sizeof(char) * 200);
    ++varCount;
    sprintf(tmp3, "br label %c%d\n; <label>:%d:\n", '%', varCount, varCount);
    result = strcat(result, tmp3);
    process(node->right->left->next, result);
    char *tmp4 = (char *)malloc(sizeof(char) * 200);
    ++varCount;
    sprintf(tmp4, "br label %c%d\n; <label>:%d:\n", '%', varCount, varCount);
    result = strcat(result, tmp4);
    free(tmp);
    free(res);
    return 0; // res
}
int genWhileStmt(past node, char *result)
{
    char *res = (char *)malloc(200);
    char *tmp = (char *)malloc(200);
    sprintf(res, "br label %c%d\n", '%', ++varCount);
    whilecheckpoint[stack_top++] = varCount;
    sprintf(tmp, "; <label>:%d:\n", varCount);
    res = strcat(res, tmp);
    result = strcat(result, res);
    genExprStmt(node->left, result);
    char *tmp2 = (char *)malloc(sizeof(char) * 200);
    sprintf(tmp2, "br i1 %c%d, label %c%d, label %c%d\n; <label>:%d:\n", '%', varCount - 1, '%', varCount, '%', varCount + 1, varCount + 1);
    varCount++;
    result = strcat(result, tmp2);
    process(node->right, result);
    char *tmp3 = (char *)malloc(sizeof(char) * 200);
    sprintf(tmp3, "br label %c%d\n; <label>:%d:\n", '%', whilecheckpoint[stack_top - 1], ++varCount);
    result = strcat(result, tmp3);
    free(tmp);
    free(res);
    return 0;
}
int genReturnStmt(past node, char *result)
{
    char *tmp = (char *)malloc(sizeof(char) * 200);
    if (strcmp(node->left->nodeType, "expr") == 0)
    {
        sprintf(tmp, "ret i32 %c%d\n", '%', genExprStmt(node->left, result));
        result = strcat(result, tmp);
        free(tmp);
        return 0;
    }
    else if (strcmp(node->left->nodeType, "intValue") == 0)
    {
        sprintf(tmp, "ret i32 %d\n", node->left->ivalue);
        result = strcat(result, tmp);
        free(tmp);
        return 0;
    }
    else if (strcmp(node->left->nodeType, "parameter") == 0)
    {
        char *tmp = (char *)malloc(sizeof(char) * 200);
        sprintf(tmp, "%%%d = load i32, i32* %%%d, align 4\n", ++varCount, reg[checkVariable(node->left->strValue)]);
        result = strcat(result, tmp);
        free(tmp);
        char *tmp2 = (char *)malloc(sizeof(char) * 200);
        sprintf(tmp2, "ret i32 %c%d\n", '%', varCount++);
        result = strcat(result, tmp2);
        free(tmp2);
        return 0;
    }
    else
    {
        free(tmp);
        result = "";
        return 0;
    }
}

int process(past node, char *result)
{
    if (strcmp(node->nodeType, "Decl") == 0)
    {
        genDeclStmt(node, result);
    }
    else if (strcmp(node->nodeType, "DeclList") == 0)
    {
        process(node->left, result);
        process(node->left->next, result);
    }
    else if (strcmp(node->nodeType, "Assign_Stmt") == 0)
    {
        genAssignStmt(node, result);
    }
    else if (strcmp(node->nodeType, "Block_list") == 0)
    {
        past l = node->left;
        for (int i = 0; i < node->ivalue; i++)
        {
            process(l, result);
            l = l->next;
        }
    }
    else if (strcmp(node->nodeType, "While_Stmt") == 0)
    {
        genWhileStmt(node, result);
    }
    else if (strcmp(node->nodeType, "Return_Stmt") == 0)
    {
        genReturnStmt(node, result);
    }
    else if (strcmp(node->nodeType, "If_Stmt") == 0)
    {
        genIfStmt(node, result);
    }
    else if (strcmp(node->nodeType, "IfElse_Stmt") == 0)
    {
        genIfElseStmt(node, result);
    }
}
int genExpr(past node)
{
    if (node == NULL)
        return -1;

    if (strcmp(node->nodeType, "Block_list") == 0)
    {
        char *result = (char *)malloc(sizeof(char) * 2000);
        process(node, result);
        addLLVMCodes(result);
    }
    else
    {
        if (node->left != NULL)
        {
            genExpr(node->left);
        }
        if (node->right != NULL)
        {
            genExpr(node->right);
        }
    }

    return -1;
}
