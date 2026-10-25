/* виправлена версія */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ВИПРАВЛЕНО: додано звільнення пам'яті */
char *create_message(const char *prefix, const char *text)
{
    size_t len = strlen(prefix) + strlen(text) + 2;
    char *msg = malloc(len);
    if (!msg) return NULL;
    snprintf(msg, len, "%s %s", prefix, text);
    return msg;
}

void process_messages(void)
{
    const char *texts[] = { "alpha", "beta", "gamma", "delta", "epsilon" };

    for (int i = 0; i < 5; i++) {
        char *msg = create_message("Message:", texts[i]);
        printf("[%d] %s\n", i, msg);
        free(msg); /* ВИПРАВЛЕНО: запобігання витоку пам'яті */
    }
}

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *create_list(int n)
{
    Node *head = NULL;
    for (int i = n; i > 0; i--) {
        Node *node = malloc(sizeof(Node));
        if (!node) return head;
        node->value = i;
        node->next  = head;
        head = node;
    }
    return head;
}

void print_and_free_list(Node *head)
{
    Node *curr = head;
    while (curr != NULL) {
        printf("%d → ", curr->value);
        Node *next_node = curr->next; /* ВИПРАВЛЕНО: зберігаємо посилання на наступний вузол */
        free(curr);                   /* звільнення поточного вузла */
        curr = next_node;             /* перехід до збереженого наступного вузла без use-after-free */
    }
    printf("NULL\n");
}

/* ВИПРАВЛЕНО: коректний розмір буфера */
void copy_data(void)
{
    const char *src = "This string is definitely longer than 16 bytes!";
    size_t len = strlen(src) + 1;
    char *buf = malloc(len);
    if (!buf) return;
    
    strcpy(buf, src);
    printf("Data: %s\n", buf);
    free(buf);
}

int main(void)
{
    printf("=== Тест 1: Витоки пам'яті ===\n");
    process_messages();

    printf("\n=== Тест 2: Use-after-free ===\n");
    Node *list = create_list(5);
    print_and_free_list(list);

    printf("\n=== Тест 3: Heap buffer overflow ===\n");
    copy_data();

    return 0;
}
