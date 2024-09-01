#include "../include/UI.h"
void MainMenu();
void HintInput();
Status GetOpNum(char* op, const char* ops[], int size, int *opnum);
void ShowERROR();
void GraphChoose(char *s);
void ManageMenu();
void OpenOrNew();
void Manage();
void CalcMenu();
void Calc();
void ShowHelp();

/* 主菜单打印
*/
void MainMenu() {
    printf("Welcome.\n");
    printf("Menu:\n");
    printf("  1> Manage Graph Files. (-manage)\n");
    printf("  2> Graph Computations. (-calc)\n");
    printf("  3> Show Help Informations. (-help)\n");
    printf("  4> Quit System. (-quit)\n");
}

/* 提示输入
*/
void HintInput() {
    // printf("Select your operations by input a string:\n");
    printf("Input> ");
}

/* 获取操作类型
*/
Status GetOpNum(char* op, const char* ops[], int size, int *opnum) {
    for(int i = 0; i < size; i ++) {
        if(strcmp(op, ops[i]) == 0) {
            *opnum = i;
            return SUCCESS;
        }
    }
    return ERROR;
}

/* 展示错误信息
*/
void ShowERROR() {
    printf("Invalid input. Please try again.\n");
}

/* 选择图
*/
void GraphChoose(char *s) {
    printf("Please enter the Graph's name:\n");
    printf("Enter 'quit' to go back.\n");
    HintInput();
    scanf("%20s", s);
}

/* 管理界面菜单打印
*/
void ManageMenu() {
    printf("Manage Menu:\n");
    printf("  1> Add an edge. (-add)\n");
    printf("  2> Delete an edge. (-del)\n");
    printf("  3> Modify an edge. (-mod)\n");
    printf("  4> Quit. (-quit)\n");
}

/* 询问打开或者新建图
*/
void OpenOrNew() {
    printf("Open a graph or create a graph?\n");
    printf("  1> open an existing graph (-open)\n");
    printf("  2> Create a new graph (-new)\n");
    printf("  3> Back to menu (-quit)\n");
}

/* 管理部分的主体程序
*/
void Manage() {
    OpenOrNew:
    OpenOrNew();
    HintInput();
    char operation[11]; int opnum; scanf("%10s", operation);
    const char* OpenOrNewOperations[] = {"open", "new", "quit"};
    if(GetOpNum(operation, OpenOrNewOperations, 3, &opnum) == ERROR) {
        ShowERROR();
        goto OpenOrNew;
    }
    int IsNew = opnum;
    if(IsNew == 2) return;
    // 询问好了就接着管理
    Manage:
    printf("Choose a graph first:\n");
    char GraphName[30]; // 最大 20 字符
    GraphChoose(GraphName);
    if(strcmp(GraphName, "quit") == 0) goto OpenOrNew;
    char Prefix[50] = "Graph/";
    size_t prefixLen = strlen(Prefix);
    size_t graphNameLen = strlen(GraphName);
    char* result = (char*) malloc(prefixLen + graphNameLen + 1);
    strcpy(result, Prefix);
    strcpy(result + prefixLen, GraphName);
    strcpy(GraphName, result);
    free(result);
    FILE *fp;
    switch (IsNew) {
    case 0:
        fp = fopen(GraphName, "r+");
        if(fp == NULL) {
            ShowERROR();
            goto Manage;
        }
        else {
            readGraphFromFile(fp);
        }
        break;
    case 1:
        fp = fopen(GraphName, "w+");
        break;
    default:
        break;
    }

    ManageMenu:
    ManageMenu();
    HintInput();
    const char* ManageMenuOperations[] = {"add", "del", "mod", "quit"};
    scanf("%10s", operation);
    if(GetOpNum(operation, ManageMenuOperations, 4, &opnum) == ERROR) {
        ShowERROR();
        goto ManageMenu;
    }
    readGraphFromFile(fp);
    int u, v, w, nw;
    switch (opnum) {
    case 0: // add
        add:
        printf("Please enter u, v, w:\n");
        printf("u, v, w should be 3 integers separated by space.\n");
        printf("u is for the start point of the edge.\n");
        printf("v is for the end point of the edge.\n");
        printf("w is for the weight of the edge.\n");
        HintInput();
        scanf("%d%d%d", &u, &v, &w);
        if(AddEdge(u, v, w) == ERROR) {
            ShowERROR();
            goto add;
        }
        printf("Finished.\n");
        goto ManageMenu;
        break;
    case 1: // del
        del:
        printf("Please enter u, v, w:\n");
        printf("u, v, w should be 3 integers separated by space.\n");
        printf("u is for the start point of the edge.\n");
        printf("v is for the end point of the edge.\n");
        printf("w is for the weight of the edge.\n");
        HintInput();
        scanf("%d%d%d", &u, &v, &w);
        if(DeleteEdge(u, v, w) == ERROR) {
            ShowERROR();
            goto del;
        }
        printf("Finished.\n");
        goto ManageMenu;        
        break;
    case 2: // mod
        mod:
        printf("Please enter u, v, w, w':\n");
        printf("u, v, w, w' should be 4 integers separated by space.\n");
        printf("u is for the start point of the edge.\n");
        printf("v is for the end point of the edge.\n");
        printf("w is for the weight of the edge.\n");
        printf("w' is for the new weight of the edge.\n");
        HintInput();
        scanf("%d%d%d%d", &u, &v, &w, &nw);
        if(ModifyEdge(u, v, w, nw) == ERROR) {
            ShowERROR();
            goto mod;
        }
        printf("Finished.\n");
        goto ManageMenu;        
        break;
    case 3: // quit
        fclose(fp);
        fp = fopen(GraphName,"w+");
        writeGraphToFile(fp);
        fclose(fp);
        break;
    
    default:
        break;
    }
}

/* 计算部分菜单打印
*/
void CalcMenu() {
    printf("Calculation Menu:\n");
    printf("  1> Shortest Path (-sp)\n");
    printf("  2> Maxflow (-mf)\n");
    printf("  3> Quit (-quit)\n");
}

/* 计算部分的主体程序
 */
void Calc() {
    Calc:
    printf("Choose a graph first:\n");
    char GraphName[40]; // 最大 20 字符
    GraphChoose(GraphName);
    if(strcmp(GraphName, "quit") == 0) return;
    char Prefix[40] = "./Graph/";
    strcat(Prefix, GraphName);
    strcpy(GraphName, Prefix);
    FILE *fp;
    fp = fopen(GraphName, "r+");
    if(fp == NULL) {
        ShowERROR();
        goto Calc;
    }
    CalcMenu:
    CalcMenu();
    HintInput();
    char operation[11]; int opnum;
    const char* CalcMenuOperations[] = {"sp", "mf", "quit"};
    scanf("%10s", operation);
    if(GetOpNum(operation, CalcMenuOperations, 3, &opnum) == ERROR) {
        ShowERROR();
        goto CalcMenu;
    }
    int S, T, val; std::vector<int> SPpath;
    switch (opnum) {
    case 0: //sp
        sp:
        printf("Input S, T:\n");
        printf("S is for the start point of the path.\n");
        printf("T is for the end point of the path.\n");
        scanf("%d%d", &S, &T);
        if(Dijkstra(fp, S, T, SPpath, val) == ERROR) {
            ShowERROR();
            goto sp;
        }
        printf("The shortest Distance between S and T is: %d\n", val);
        printf("Path:");
        for(int i = 0;i < SPpath.size() - 1; i ++) printf("%d -> ", SPpath[i]);
        printf("%d", SPpath[SPpath.size() - 1]);
        printf("\n");
        break;
    case 1: //mf
        printf("Input S, T:\n");
        printf("S is for the source point.\n");
        printf("T is for the sink point.\n");
        scanf("%d%d", &S, &T);
        MaxFlow(fp, S, T, val);
        printf("Maxflow from S to T is: %d\n", val);
        break;
    case 2: //quit
        break;
    default:
        break;
    }
}
void ShowHelp() {
    printf("--HELP--\n");
    printf("  1> Type a string to select an operation.\n");
    printf("  2> Edit the graph or calculate on it.\n");
    printf("  3> May it be helpful and enjoy it.\n");
    printf("--END--\n");
}