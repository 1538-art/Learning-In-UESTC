#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "head.h"


int main(){
	
	user* head=NULL;
	openfile(&head);//���Ըı�����ṹ 
    homepage(head);//�����Ըı�����ṹ�����������head��ֵ����һ����ַ��ͨ���õ�ַ���Ըı�õ�ַָ������ݣ��������ڵ����ݣ�Ҫ�ı�����ṹ�;��ö���ָ�룬�ñ������ݣ�����һ��ָ�� 
	return 0;

}
