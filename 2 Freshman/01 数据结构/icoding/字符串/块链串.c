/*

 */

#include <stdlib.h>
#include <stdio.h>
#include"dsstring.h" // 请不要删除，否则检查不通过

bool blstr_substr(BLString src, int start_pos, int len, BLString* sub) {
  // 检查参数合法性
  if (start_pos < 0 || start_pos >= src.len || len < 1 || sub == NULL) {
    return false;
  }
  
  // 初始化子字符串的头指针和源字符串的指针
  sub->head = (Block*)malloc(sizeof(Block));
  if (sub->head == NULL) {
    return false;
  }
  Block* curr_block = sub->head, * src_block = src.head;
  
  // 初始化计数器
  //src_pos指示在原字符串中要提取子字符串的位置
  //sub_pos指示在子字符串中要复制字符的位置
  //char_count指示已经遍历过的字符数
  int src_pos = 0, sub_pos = 0, char_count = 0;
  
  // 初始化尾指针和长度
  curr_block->next = NULL;
  sub->tail = curr_block;
  sub->len = 0;
  
  // 循环遍历源字符串和子字符串
  while (char_count <= start_pos + len - 1 && src_block != NULL && src_block->ch[src_pos] != BLS_BLANK) {
    if (char_count < start_pos) { // 跳过前 start_pos 个字符，到 start_pos 的位置
      if (src_pos < BLOCK_SIZE - 1) { // 如果当前块未满，继续读取该块的下一个字符
        src_pos++;
      }
      else { // 否则，移动到下一个块
        src_block = src_block->next;
        src_pos = 0;
      }
      char_count++;
    }
    else { // 复制子字符串到 sub 中
      curr_block->ch[sub_pos] = src_block->ch[src_pos]; // 复制当前字符
      if (src_pos < BLOCK_SIZE - 1) { // 原字符串块：如果当前块未满，继续读取该块的下一个字符
        src_pos++;
      }
      else { // 否则，移动到下一个块
        src_block = src_block->next;
        src_pos = 0;
      }
      
      if (sub_pos < BLOCK_SIZE - 1) { // 子字符串块：如果当前块未满，继续复制到当前块
        sub_pos++;
      }
      else { // 否则，分配新块
        curr_block->next = (Block*)malloc(sizeof(Block));
        curr_block = curr_block->next;
        curr_block->next = NULL;
        sub_pos = 0;
      }
      char_count++;
      sub->len++;
    }
  }
  
  // 处理尾指针和多余的空间
  if (sub_pos != 0) { // 如果最后一个块未满，用空格填充
    sub->tail = curr_block;
    while (sub_pos < BLOCK_SIZE) {
      curr_block->ch[sub_pos++] = BLS_BLANK;
    }
  }
  else { // 如果最后一个块是空的，删除该块
    
    // 遍历找到最后一个块的前一个块
    sub->tail = sub->head;
    while (sub->tail->next != curr_block) {
      sub->tail = sub->tail->next;
      if (sub->tail == NULL) { // 仅仅为了消除VS的警告“sub->tail为NULL，取消对空指针的引用”
        return false;
      }
    }
    sub->tail->next = NULL;
    free(curr_block);
  }
  
  return true;
}