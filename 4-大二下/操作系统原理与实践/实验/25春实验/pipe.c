#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int pipe_fd[2];
    sem_t *sem;
    int shmid;
    char w_buffer[100];
    char r_buffer[100];
    if (pipe(pipe_fd) == -1) {
        printf("Pipe creation failed!\n");
        exit(1);
    }
    // 分配缓冲区
    else if ((shmid = shmget(IPC_PRIVATE, sizeof(sem_t), 0600)) == -1) {
        printf("Memory allocation error!\n");
        exit(1);
    } else if ((sem = shmat(shmid, 0, 0600)) == NULL) {
        printf("Mapping error!\n");
        exit(1);
    }
    sem_init(sem, 1, 0); // 信号量初始化
    if ((pid1 = fork()) == 0) {
        close(pipe_fd[0]); // 关闭读
        sprintf(w_buffer, "child process 1 is sending message.\n");
        write(pipe_fd[1], w_buffer, 50);
        sem_post(sem); // 释放信号量
        exit(0);
    }
    if ((pid2 = fork()) == 0) {
        sem_wait(sem);
        close(pipe_fd[0]); // 关闭读
        sprintf(w_buffer, "child process 2 is sending message.\n");
        write(pipe_fd[1], w_buffer, 50);
        exit(0);
    }
    if (pid1 > 0 && pid2 > 0) {
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        close(pipe_fd[1]);  // 关闭写
        if (read(pipe_fd[0], r_buffer, 50) > 0)
            printf("%s", r_buffer);
        if (read(pipe_fd[0], r_buffer, 50) > 0)
            printf("%s", r_buffer);
        exit(0);
    }
}
