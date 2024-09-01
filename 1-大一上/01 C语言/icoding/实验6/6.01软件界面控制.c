/*题目：

实现一个数字选项式的启动界面，程序输入数据为（1-8），参考界面如下：

  1.显示所有商品的信息
  2.修改某个商品的信息
  3.插入某个商品的信息
  4.删除某个商品的信息
  5.查找某个商品的信息
  6.商品存盘并退出系统
  7.对商品价格进行排序
  8.(慎用)删除所有内容
  其他.不存盘并退出系统

程序当输入1-8时，执行相关功能，完成后再次显示菜单让用户选择。当输入其它数值时，程序不存盘并退出系统。

本小题只需实现 main 函数即可，相关结构及函数声明如下：

#define GOODS_FILE_NAME "goodsinfo.txt"

#define MAX_ID_LEN 30

#define MAX_NAME_LEN 30

#define MAX_PRICE_LEN 30

#define MAX_DISCOUNT_LEN 30
typedef struct {
char goods_id[MAX_ID_LEN];
char goods_name[MAX_NAME_LEN];
int goods_price;
char goods_discount[MAX_DISCOUNT_LEN];
int goods_amount;
int goods_remain;
} GoodsInfo;


typedef struct node
{
GoodsInfo data;
struct node *next;
} GoodsList;


GoodsInfo read_goods_info();
void init_list(GoodsList **pL);
void destory_list(GoodsList **pL);
void destory_list_and_file(GoodsList **pL);
int save_to_file(GoodsList *L);
void output_one_item(GoodsList *L);
void output_all_items(GoodsList *L);
bool insert_item(GoodsList *L, GoodsInfo item, int choice);
bool delete_item(GoodsList *L, char* goods_id);
GoodsList* search_item(GoodsList *L, char* goods_id);
bool change_item(GoodsList *L, char* goods_id, GoodsInfo new_info);
void bubble_sort(GoodsList *L);
int read_line(char str[], int n);

该部分声明已包含在 “lab52.h”中。*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

int main() {
  GoodsList *list;
  init_list(&list);
  char idd[MAX_ID_LEN] = {0};
  int x = 0;

  for (;;) {
    printf("1.显示所有商品的信息\n");
    printf("2.修改某个商品的信息\n");
    printf("3.插入某个商品的信息\n");
    printf("4.删除某个商品的信息\n");
    printf("5.查找某个商品的信息\n");
    printf("6.商品存盘并退出系统\n");
    printf("7.对商品价格进行排序\n");
    printf("8.(慎用)删除所有内容\n");
    printf("其他.不存盘并退出系统\n");

    int ope;
    scanf("%d", &ope);
    switch (ope) {
    case 1:
      output_all_items(list);
      break;

    case 2:
      printf("输入要修改的商品ID：\n");
      read_line(idd, MAX_ID_LEN);
      printf("输入商品参数：\n");
      if (change_item(list, idd, read_goods_info()))
        printf("修改成功！\n");
      else
        printf("修改失败！\n");
      memset(idd, 0, sizeof(0));
      break;

    case 3:
      printf("0:插入到链表尾部\n");
      printf("1:插入到链表头部\n");
      printf("其它正整数：插入到该位置\n");
      scanf("%d", &x);
      printf("输入商品参数:\n");
      if (insert_item(list, read_goods_info(), x))
        printf("插入成功！\n");
      else
        printf("插入失败！\n");
      break;

    case 4:
      printf("输入需要删除的商品ID：\n");
      read_line(idd, MAX_ID_LEN);
      if (delete_item(list, idd))
        printf("删除成功！\n");
      else
        printf("删除失败！\n");
      memset(idd, 0, sizeof(0));
      break;

    case 5:
      printf("输入需要删除的商品ID：\n");
      read_line(idd, MAX_ID_LEN);
      if (search_item(list, idd) == NULL)
        printf("查找失败！\n");
      else {
        printf("查找成功！\n");
        output_one_item(search_item(list, idd));
      }
      break;

    case 6:
      save_to_file(list);
      return 0;
      break;

    case 7:
      bubble_sort(list);
      break;

    case 8:
      destory_list_and_file(&list);
      break;

    default:
      destory_list(&list);
      return 0;
      break;
    }

    printf("\n");
  }

  return 0;
}

void output_one_item(GoodsList *p) {
  printf("%s\t%s\t%d\t%s\t%d\t%d\n", p->data.goods_id, p->data.goods_name,
         p->data.goods_price, p->data.goods_discount, p->data.goods_amount,
         p->data.goods_remain);
}