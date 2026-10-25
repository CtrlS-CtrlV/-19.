/* довготривалий процес для gdb attach */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256

static int request_count = 0;
static char last_request[BUF_SIZE] = "(none)";

void process_request(const char *req)
{
    request_count++;
    strncpy(last_request, req, BUF_SIZE - 1);
    last_request[BUF_SIZE - 1] = '\0';
    printf("[%d] Оброблено: %s\n", request_count, req);
}

int main(void)
{
    printf("Довготривалий процес. PID: %d\n", getpid());
    printf("Для інспекції: gdb -p %d\n\n", getpid());

    const char *requests[] = {
        "GET /index.html",
        "POST /api/data",
        "GET /about",
        "DELETE /api/item/42",
        "GET /status",
    };
    int nreq = sizeof(requests) / sizeof(requests[0]);

    for (int cycle = 0; ; cycle++) {
        process_request(requests[cycle % nreq]);
        sleep(3);
    }

    return 0;
}
