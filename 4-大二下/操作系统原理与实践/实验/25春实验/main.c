#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PRODUCER 3
#define NUM_CONSUMER 4
#define BUFFER_SIZE 5
#define FILE_PATH "./source.txt"

FILE *fp;
int data = 0;

int in = 0,
    out = 0,
    buff[BUFFER_SIZE] = {0};

// semaphore
sem_t empty, full;
pthread_mutex_t mutex;
pthread_mutex_t file_mutex;

pthread_t consumers[NUM_CONSUMER];
pthread_t producers[NUM_PRODUCER];
int consumer_id[NUM_CONSUMER];
int producer_id[NUM_PRODUCER];

void PrintBuffer() {
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (buff[i] == 0)
            printf("·");
        else
            printf("%d ", buff[i]);
    }
    printf(" [in:%d out:%d]\n", in, out);
}

void *producer(void *id) {
    printf("Producer %d\n", *(int *)id);

    while (1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&file_mutex);
        int stat = fscanf(fp, "%d", &data);
        pthread_mutex_unlock(&file_mutex);

        if (stat == EOF)
        {
            buff[in] = -1;
            sem_post(&full);
            pthread_mutex_unlock(&mutex);
            break;
        }

        buff[in] = data;
        printf("Producer %d produced [%d] in buffer[%d]\n",
        *(int *)id, buff[in], in);

        in = (in + 1) % BUFFER_SIZE;
        PrintBuffer();

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

    }
    fclose(fp);
    pthread_exit(NULL);
}



void *consumer(void *id) {
    printf("Consumer %d\n", *(int *)id);
    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int product = buff[out];
        if (product == -1) {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
            break;
        }

        buff[out] = 0;
        printf("Consumer %d consumed [%d] in buffer[%d]\n",
            *(int *)id, product, out);

        out = (out + 1) % BUFFER_SIZE;
        PrintBuffer();

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void Init() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&file_mutex, NULL);

    fp = fopen(FILE_PATH, "r");

    for (int i =0; i<NUM_PRODUCER; i++) {
        producer_id[i] = i+1;
        pthread_create(&producers[i], NULL, producer, &producer_id[i]);
    }
    for (int i =0; i<NUM_CONSUMER; i++) {
        consumer_id[i] = i+1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_id[i]);
    }
}

void Destroy() {
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&file_mutex);
}

int main(void) {
    printf("Hello, World!\n");

    Init();
    for (int i = 0; i < NUM_PRODUCER; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMER; i++)
    {
        pthread_join(consumers[i], NULL);
    }

    Destroy();
    printf("All done");


    return 0;
}
