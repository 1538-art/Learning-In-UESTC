//二叉树
typedef int DataType;

typedef struct Node{
  DataType data;
  struct Node* left;
  struct Node* right;
}BiTNode, *BiTree;

//普通树
#define MAX_CHILDREN_NUM 5
struct _CSNode
{
  DataType data;
  struct _CSNode *children[MAX_CHILDREN_NUM];
};
typedef struct _CSNode CSNode;

//队列
struct __Queue
{
  int i, j; //指向数组内元素的游标
  void **array;
};
typedef struct __Queue Queue;

Queue* create_queue(); //创建队列
bool is_empty_queue(Queue *tree); //队为空返回true,不为空时返回false
void* del_queue(Queue *tree); //结点指针出队
void add_queue(Queue *tree, void *node); //结点指针入队
void free_queue(Queue *tree); //释放队列

//完成
BiTNode* transform(CSNode *root);