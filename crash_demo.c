/* програма, що генерує core dump */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char   *data;
    size_t  size;
    size_t  capacity;
} DynArray;

DynArray *dynarray_create(size_t initial_cap)
{
    DynArray *da = malloc(sizeof(DynArray));
    if (!da) return NULL;
    da->data     = malloc(initial_cap);
    da->size     = 0;
    da->capacity = initial_cap;
    return da;
}

void dynarray_append(DynArray *da, char value)
{
    if (da->size >= da->capacity) {
        da->capacity *= 2;
        da->data = realloc(da->data, da->capacity);
    }
    da->data[da->size++] = value;
}

void dynarray_free(DynArray *da)
{
    free(da->data);
    free(da);
}

void buggy_operation(void)
{
    DynArray *arr = dynarray_create(4);

    for (int i = 0; i < 10; i++)
        dynarray_append(arr, 'A' + i);

    printf("Масив: ");
    for (size_t i = 0; i < arr->size; i++)
        printf("%c ", arr->data[i]);
    printf("\n");

    dynarray_free(arr);

    /* BUG: use-after-free — доступ та запис у звільнений об'єкт arr */
    printf("Розмір після free: %zu\n", arr->size);
    dynarray_append(arr, 'X');  /* CRASH */
}

int main(void)
{
    printf("PID: %d\n", getpid());
    printf("Натисніть Enter для запуску...\n");
    getchar();

    buggy_operation();
    return 0;
}
