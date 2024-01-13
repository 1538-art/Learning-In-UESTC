int count_qualified_days(int n, int T) {
  // 在此函数中，需要用到整数输入
  // TODO
  int count = 0;
  for (int i = 0; i < n; i++) {
    int value;
    scanf("%d", &value);
    if (value <= T) {
      count++;
    }
  }
  return count;
  // END OF TODO
}