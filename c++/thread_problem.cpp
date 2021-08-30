#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond_var;
bool print = false;
// use while to avoid spurious problem
void* ProducerThread(void* arg){
    for (int i = 0; i < 10; i+=2){
        pthread_mutex_lock(&mutex);
        while(print){
            pthread_cond_wait(&cond_var, &mutex);
        }
        printf("%d\n",i);
        print = !print;
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void* ConsumerThread(void* arg){
    for (int i = 1; i < 10; i+=2){
        pthread_mutex_lock(&mutex);
        while(!print){
            pthread_cond_wait(&cond_var, &mutex);
        }
        printf("%d\n",i);
        print = !print;
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main() {
    pthread_t producer;
    pthread_t consumer;
    pthread_create(&producer, NULL, &ProducerThread, NULL);
    pthread_create(&consumer, NULL, &ConsumerThread, NULL);
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    exit(EXIT_SUCCESS);
}