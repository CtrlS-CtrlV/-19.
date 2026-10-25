/* виправлена версія з м'ютексами */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS   4
#define ITERATIONS    100000

static int shared_counter = 0;
static int shared_array[100];
static int array_index = 0;

/* Ініціалізація м'ютексів */
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t array_mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&counter_mutex);
        shared_counter++; /* Захищено м'ютексом */
        pthread_mutex_unlock(&counter_mutex);
    }
    printf("Потік %d завершив роботу.\n", id);
    return NULL;
}

void *append_to_array(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < 25; i++) {
        pthread_mutex_lock(&array_mutex);
        if (array_index < 100) {
            shared_array[array_index] = id * 100 + i;
            array_index++;
        }
        pthread_mutex_unlock(&array_mutex);
        usleep(10);
    }
    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    printf("=== Тест 1: Гонка на лічильнику (виправлено) ===\n");
    printf("Очікуваний результат: %d\n", NUM_THREADS * ITERATIONS);

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, increment_counter, &ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Фактичний результат: %d\n\n", shared_counter);

    printf("=== Тест 2: Гонка на масиві (виправлено) ===\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, append_to_array, &ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Записано елементів: %d (очікується <= 100)\n", array_index);

    return 0;
}
