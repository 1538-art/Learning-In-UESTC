#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "head.h"


int main(){
	
	user* head=NULL;
	openfile(&head);//可以改变链表结构 
    homepage(head);//不可以改变链表结构，但传入的是head的值，即一个地址，通过该地址可以改变该地址指向的内容，即链表内的内容，要改变链表结构就就用二级指针，该避难内容，就用一级指针 
	return 0;

}
