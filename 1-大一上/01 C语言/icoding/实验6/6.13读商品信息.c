/*
函数原型：GoodsInfo read_goods_info()

该函数调用read_line及scanf等函数，按“商品ID、商品名称、商品价格、商品折扣、商品数量、商品剩余数量”的顺序让用户输入，并将这些信息保存到
GoodsInfo 结构体中，函数最后返回该结构体。
*/
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

extern int CurrentCnt; // 请不要删除本行的全局变量声明，否则检查不通过

GoodsInfo read_goods_info() // 13读入数据
{
  GoodsInfo a;
  if (!read_line(a.goods_id, MAX_ID_LEN)) {
    GoodsInfo fail;
    fail.goods_price = -1;
    return fail;
  }
  read_line(a.goods_name, MAX_NAME_LEN);
  scanf("%d", &a.goods_price);
  read_line(a.goods_discount, MAX_DISCOUNT_LEN);
  scanf("%d%d", &a.goods_amount, &a.goods_remain);

  return a;
}