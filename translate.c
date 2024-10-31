#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char *ROFI_TRANSLATE_BROWSER = "/usr/bin/firefox";
const char *ROFI_TRANSLATE_URL =
    "https://www.linguee.com/english-german/search?source=german&query=";

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(EXIT_SUCCESS);
    }
    const char *browser = getenv("ROFI_TRANSLATE_BROWSER");
    if (browser == NULL) {
        browser = ROFI_TRANSLATE_BROWSER;
    }
    const char *url = getenv("ROFI_TRANSLATE_URL");
    if (url == NULL) {
        url = ROFI_TRANSLATE_URL;
    }
    pid_t child = fork();
    if (child == 0) {
        char query[1024];
        snprintf(query, sizeof(query), "%s%s", url, argv[1]);
        const char *args[] = {"new-tab", query, NULL};
        if (execv(browser, (char *const *)args) < 0) {
            fprintf(stderr, "Command execution failed: %s\n", strerror(errno));
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
