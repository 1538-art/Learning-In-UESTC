#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�������������� 
#include "Caculator.h"

int main() {
    int mode;
    printf("Please choose Calculate mode��\n");
    printf("1. Batch Calculate mode\n");
    printf("2. Common Calculate mode\n");
    scanf("%d", &mode);

    if (mode == 1) {
        Batch_Caculate(); 
        
    } else if (mode == 2) {
		// ��ȡѡ��mode������������µĻ��з�
        getchar(); 
        
        Stdin_Caculate();
    }
    return 0;
}
