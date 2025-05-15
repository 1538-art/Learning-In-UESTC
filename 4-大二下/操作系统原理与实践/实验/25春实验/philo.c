#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define TIMES 6
pthread_mutex_t chops[5]; // 筷子的互斥量
pthread_t philosopher[5]; // 哲学家进程号
int phi_ID[5]; // 哲学家编号
// 哲学家编号取筷子
void get_chop(int id)
{
    if (id % 2 == 0) //偶数哲学家先拿左边的筷子
    {
        pthread_mutex_lock(chops + id);
        pthread_mutex_lock(chops + ((id + 1) % 5));
    }
    else //奇数哲学家先拿右边的筷子
    {
        pthread_mutex_lock(chops + ((id + 1) % 5));
        pthread_mutex_lock(chops + id);
    }
}

// 哲学家放筷子
void put_chop(int id) {
    if (id % 2 == 0)
    {
        pthread_mutex_unlock(chops + id);
        pthread_mutex_unlock(chops + ((id + 1) % 5));
    }
    else
    {
        pthread_mutex_unlock(chops + ((id + 1) % 5));
        pthread_mutex_unlock(chops + id);
    }
}

// 哲学家进程
void *philosopher_(void *phi_id)
{
    int id = *(int *)phi_id;
    printf("\e[1;32m 哲学家%d 来了\e[0m \n", id + 1);
    for (int i = 0; i < TIMES; i++)
    {
        // 开始思考
        printf("哲学家%d 思考第 %d 个问题\n", id + 1, i + 1);
        srand(0);

        // 取筷子
        get_chop(id);
        // 吃饭
        printf("哲学家%d 吃第 %d 顿饭\n", id + 1, i + 1);
        srand(0);
        // 放下筷子
        put_chop(id);
    }
    // 进餐结束
    printf("\e[1;32m 哲学家%d 走了\e[0m \n", id + 1);
    pthread_exit(0);
}
// 初始化互斥量
void init_mutex()
{
    for (int i = 0; i < 5; i++)
        pthread_mutex_init(chops + i, NULL);
}
// 释放互斥量
void dispose_mutex()
{
    for (int j = 0; j < 5; j++)
        pthread_mutex_destroy(chops + j);
}
void main() {
    // 初始化信号量
    init_mutex();
    // 创建五个进程
    for (int i = 0; i < 5; i++)
    {
        // 设置哲学家的 ID
        phi_ID[i] = i;
        // 创建对应的线程
        pthread_create(philosopher + i, NULL, philosopher_, phi_ID + i);
    }
    // 等待五个哲学家进程返回
    for (int i = 0; i < 5; i++)
    {
        pthread_join(*(philosopher + i), NULL);
    }
    // 释放信号量
    dispose_mutex();
    // 结束
    printf("结束\n");
    return ;
}