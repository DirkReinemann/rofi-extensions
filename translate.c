#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "config.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        exit(EXIT_SUCCESS);
    }
    const char* bin = get_env_or_alt("ROFI_TRANSLATE_BROWSER_BINARY",
        ROFI_TRANSLATE_BROWSER_BINARY);
    const char* url = get_env_or_alt("ROFI_TRANSLATE_SEARCH_URL",
        ROFI_TRANSLATE_SEARCH_URL);
    pid_t child = fork();
    if (child == 0) {
        char query[1024];
        snprintf(query, sizeof(query), "%s%s", url, argv[1]);
        char* const args[] = { "new-tab", query, NULL };
        if (execv(bin, args) < 0) {
            fprintf(stderr, "Command execution failed: %s\n",
                strerror(errno));
            exit(1);
        }
    } else if (child > 0) {
        int wstatus;
        if (wait(&wstatus) < 0) {
            fprintf(stderr, "Wait failed: %s\n", strerror(errno));
            exit(1);
        }
    } else {
        fprintf(stderr, "Fork failed: %s\n", strerror(errno));
        exit(1);
    }
    exit(EXIT_SUCCESS);
}
