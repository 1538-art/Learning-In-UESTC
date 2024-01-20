#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "SuperStack.h"

Stack* Stack_Construct(int sizeOfElement){
    Stack *pStack;
    pStack=(Stack*)malloc(sizeof(Stack));
    if(pStack==NULL){
        return NULL;
        #if DEBUG
        printf("NULL");
        #endif // DEBUG
    }
    pStack->pBase=malloc(STACK_INIT_SIZE*sizeOfElement);
    if(pStack->pBase==NULL){
        free(pStack);
        return NULL;
        #if DEBUG
        printf("NULL");
        #endif // DEBUG
    }
    pStack->pTop=pStack->pBase;
    pStack->elementSize=sizeOfElement;
    pStack->stackSize=STACK_INIT_SIZE;
    return pStack;
    #if DEBUG
    printf("OK");
    #endif // DEBUG
}

void Stack_Destruct(Stack* pStack){
    if(pStack==NULL){
        return;
    }
    free(pStack->pBase);
    free(pStack);
    return;
    #if DEBUG
    printf("OK");
    #endif // DEBUG
}

void Stack_Clear(Stack* pStack){
    if(pStack==NULL){
        return;
    }
    pStack->pTop=pStack->pBase;
    #if DEBUG
    printf("OK");
    #endif // DEBUG
}

Bool Stack_IsEmpty(Stack* pStack){
    if(pStack->pTop==pStack->pBase){
        return TRUE;
        #if DEBUG
        printf("TURE");
        #endif // DEBUG
    }
    else{
        return FALSE;
        #if DEBUG
        printf("FALSE");
        #endif // DEBUG
    }
}

int Stack_Length(Stack* pStack){
    if(pStack==NULL){
        return -1;
        #if DEBUG
        printf("ERROR");
        #endif // DEBUG
    }
    else{
        int e = ((pStack->pTop) - (pStack->pBase))/(pStack->elementSize);
        return e;
        #if DEBUG
        printf("OK£¬ Õ»³¤¶ÈÎª%d"£¬e);
        #endif // DEBUG
    }

}

Status Stack_GetTop(Stack* pStack,void* pElem){
    char* pc;
    if(pStack->pTop==pStack->pBase){
        return ERROR;
        #if DEBUG
        printf("ERROR");
        #endif // DEBUG
    }
    pc=(char*)(pStack->pTop);
    pc-=pStack->elementSize;
    memcpy(pElem,pc,pStack->elementSize);
    return OK;
    #if DEBUG
    printf("OK");
    #endif // DEBUG
}

Status Stack_Push(Stack* pStack,void* pElem){
    int newSize;
    void *pTemp;
    char *pc;
    if(Stack_Length(pStack)>=pStack->stackSize){
        newSize=pStack->stackSize+STACK_INCREMENT;
        pTemp=realloc(pStack->pBase,newSize*(pStack->elementSize));
        if(pTemp==NULL){
            return ERROR;
            #if DEBUG
            printf("ERROR");
            #endif // DEBUG
        }
        else {
                pStack->pBase=pTemp;
                pc=(char*)pTemp;
                pc+=pStack->stackSize;
                pStack->pTop = pc;
                pStack->stackSize=newSize;
        }
     }
     pc = (char*)(pStack->pTop);
     memcpy(pc,pElem,pStack->elementSize);
     pStack->pTop=pc+pStack->elementSize;
     return OK;
     #if DEBUG
     printf("OK");
     #endif // DEBUG
}

Status Stack_Pop(Stack* pStack,void* pElem){
    char* pc;
    if(pStack->pTop==pStack->pBase){
        return ERROR;
        #if DEBUG
        printf("ERROR");
        #endif // DEBUG
    }
    else{
        pc = (char*)(pStack->pTop);
        pStack->pTop=pc-pStack->elementSize;
        memcpy(pElem,pStack->pTop,pStack->elementSize);
        return OK;
        #if DEBUG
        printf("OK");
        #endif // DEBUG
    }
}


Status Stack_Traverse(Stack* pStack,Status (*visit)(void*)){
    int i,n;
    char* pc;
    n=Stack_Length(pStack);
    pc=(char*)(pStack->pBase);
    for(i=0;i<n;i++){
        if(visit(pc)== ERROR){
            return ERROR;
            #if DEBUG
            printf("ERROR");
            #endif // DEBUG
        }
        pc+=pStack->elementSize;
    }
    return OK;
    #if DEBUG
    printf("OK");
    #endif // DEBUG
}
