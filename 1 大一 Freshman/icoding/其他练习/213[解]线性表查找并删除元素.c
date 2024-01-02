void del_value(list *L, int value) {
  // TODO
  //  找到值为 value 的元素的位置
  int pos = 0;
  while (pos < L->len && L->data[pos] != value) {
    pos++;
  }

  // 如果找到了值为 value 的元素
  if (pos < L->len) {
    // 将删除位置之后的所有元素向前移动一位
    for (int i = pos; i < L->len - 1; i++) {
      L->data[i] = L->data[i + 1];
    }

    // 线性表的长度减1
    L->len--;
  }
  // END OF TODO
}
