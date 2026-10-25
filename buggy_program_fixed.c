/* виправлена версія */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculate_average(const int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++) {   /* ВИПРАВЛЕНО: i від 0 до size - 1 */
        sum += arr[i];
    }
    return (double)sum / size;   /* ВИПРАВЛЕНО: приведено до double для уникнення цілочисельного ділення */
}

void reverse_string(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i]         = str[len - 1 - i];   /* ВИПРАВЛЕНО: коректний індекс len - 1 - i */
        str[len - 1 - i] = tmp;
    }
}

typedef struct {
    char *name;
    int   score;
} Student;

void print_student(const Student *s)
{
    if (s == NULL) {
        printf("Студент не знайдений (NULL покажчик).\n");
        return;
    }
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
    print_student(found);   /* ВИПРАВЛЕНО: функція обробляє NULL */

    return 0;
}
