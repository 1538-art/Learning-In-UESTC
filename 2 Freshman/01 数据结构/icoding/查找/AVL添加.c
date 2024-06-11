/*AVL添加
  
  平衡二叉树，是一种二叉排序树，其中每个结点的左子树和右子树的高度差至多等于1。它是一种高度平衡的二叉排序树。现二叉平衡树结点定义如下：

typedef struct node
{
  int val;
  struct node *left;
  struct node *right;
  struct node *parent;
  int height;
} node_t;
//请实现平衡二叉树的插入算法：

//向根为 root 的平衡二叉树插入新元素 val，成功后返回新平衡二叉树根结点
node_t *avl_insert(node_t *root, int val);
*/
#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

// 获取节点的高度
int get_height(node_t *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

// 计算节点的平衡因子
int get_balance_factor(node_t *node) {
  if (node == NULL)
    return 0;
  return get_height(node->left) - get_height(node->right);
}

// 更新节点的高度
void update_height(node_t *node) {
  int left_height = get_height(node->left);
  int right_height = get_height(node->right);
  // 节点的高度等于左子树高度和右子树高度的较大值加1
  node->height = (left_height > right_height ? left_height : right_height) + 1;
}

// 创建新节点
node_t *create_node(int val) {
  // 分配内存空间来创建一个新节点
  node_t *new_node = (node_t *) malloc(sizeof(node_t));
  new_node->val = val;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = NULL;
  new_node->height = 1;
  return new_node;
}

// 左旋操作
node_t *left_rotate(node_t *root) {
  // 将根节点的右子节点作为中心节点进行左旋
  node_t *pivot = root->right;
  node_t *subtree = pivot->left;
  
  // 执行左旋操作
  pivot->left = root;
  root->right = subtree;
  
  // 更新节点的高度
  update_height(root);
  update_height(pivot);
  
  // 返回旋转后的根节点
  return pivot;
}

// 右旋操作
node_t *right_rotate(node_t *root) {
  // 将根节点的左子节点作为中心节点进行右旋
  node_t *pivot = root->left;
  node_t *subtree = pivot->right;
  
  // 执行右旋操作
  pivot->right = root;
  root->left = subtree;
  
  // 更新节点的高度
  update_height(root);
  update_height(pivot);
  
  // 返回旋转后的根节点
  return pivot;
}

// 插入节点
node_t *avl_insert(node_t *root, int val) {
  // 执行BST插入 注意递归是递归的avl_insert 在递归返回时就能找到最低失衡结点
  if (root == NULL)
    return create_node(val);
  
  if (val < root->val) {
    // 递归进入左子树
    root->left = avl_insert(root->left, val);
    root->left->parent = root;
  } else if (val > root->val) {
    // 递归进入右子树
    root->right = avl_insert(root->right, val);
    root->right->parent = root;
  } else
    return root;  // 如果已经存在相同的值，不执行插入
  
  // 更新节点的高度
  update_height(root);
  
  // 检查节点的平衡因子
  int balance = get_balance_factor(root);
  
  // 平衡树
  // 左-左情况：插入节点在左子树的左子树中
  if (balance > 1 && val < root->left->val)
    return right_rotate(root);
  
  // 右-右情况：插入节点在右子树的右子树中
  if (balance < -1 && val > root->right->val)
    return left_rotate(root);
  
  // 左-右情况：插入节点在左子树的右子树中
  if (balance > 1 && val > root->left->val) {
    // 先对左子树进行左旋操作，再对根节点进行右旋操作
    root->left = left_rotate(root->left);
    return right_rotate(root);
  }
  
  // 右-左情况：插入节点在右子树的左子树中
  if (balance < -1 && val < root->right->val) {
    // 先对右子树进行右旋操作，再对根节点进行左旋操作
    root->right = right_rotate(root->right);
    return left_rotate(root);
  }
  
  // 如果树已经平衡，直接返回根节点
  return root;
}
