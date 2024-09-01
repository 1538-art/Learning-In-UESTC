//
// Created by Thomas on 2023/12/11.
//

//
// Created by Thomas on 2023/12/11.
//

#include "linked-list-stack.h"

Stack *StackConstruct(int sizeOfElement) {
  return ListConstruct(sizeOfElement);
}

void StackDestruct(Stack *pStack) {
  ListDestruct(pStack);
}

void StackClear(Stack *pStack) {
  ListClear(pStack);
}

Bool StackIsEmpty(Stack *pStack) {
  return ListIsEmpty(pStack);
}

int StackGetLength(Stack *pStack) {
  return List_GetLength(pStack);
}

Status StackPop(Stack *pStack, void *pElem) {
  if (StackIsEmpty(pStack)) {
    return ERROR;
  }
  memcpy(pElem, pStack->pFirstNode->pData, pStack->dataSize);
  return ListDeleteFirstNode(pStack);
}

Status StackPush(Stack *pStack, void *pElem) {
  return ListInsertAtFront(pStack, pElem);
}

Status StackGetTop(Stack *pStack, void *pElem) {
  if (StackIsEmpty(pStack)) {
    return ERROR;
  }
  memcpy(pElem, pStack->pFirstNode->pData, pStack->dataSize);
  return OK;
}

Status StackTraverse(Stack *pStack, Status (*visit)(void *)) {
  return ListTraverse(pStack, visit);
}
