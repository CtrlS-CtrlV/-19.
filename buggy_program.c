/* програма з помилками для налагодження */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* BUG 1: логічна помилка у обчисленні середнього */
double calculate_average(const int *arr, int size)
{
    int sum = 0;
    for (int i = 1; i <= size; i++) {   /* ПОМИЛКА: вихід за межі масиву (i від 1 до size, а треба 0 до size-1) */
        sum += arr[i];
    }
    return sum / size;   /* ПОМИЛКА: цілочисельне ділення (sum / size дає int) */
}

/* BUG 2: segmentation fault */
void reverse_string(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i]       = str[len - i];   /* ПОМИЛКА: звернення до str[len] (нуль-термінатор або за межами) */
        str[len - i] = tmp;
    }
}

/* BUG 3: доступ до NULL-покажчика */
typedef struct {
    char *name;
    int   score;
} Student;

void print_student(const Student *s)
{
    printf("Студент: %s, бал: %d\n", s->name, s->score);
}

Student *find_student(Student *students, int count, const char *name)
{
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].name, name) == 0)
            return &students[i];
    }
    return NULL;
}

int main(void)
{
    printf("=== Тест 1: Середнє арифметичне ===\n");
    int values[] = { 10, 20, 30, 40, 50 };
    double avg = calculate_average(values, 5);
    printf("Середнє: %.2f (очікується 30.00)\n\n", avg);

    printf("=== Тест 2: Реверс рядка ===\n");
    char greeting[] = "Hello, World!";
    reverse_string(greeting);
    printf("Реверс: '%s' (очікується '!dlroW ,olleH')\n\n", greeting);

    printf("=== Тест 3: Пошук студента ===\n");
    Student students[] = {
        { "Taras",  90 },
        { "Ivan",   85 },
        { "Lesia",  95 },
    };
    Student *found = find_student(students, 3, "Olena");
    print_student(found);   /* ПОМИЛКА: found == NULL, розіменування NULL у print_student */

    return 0;
}
