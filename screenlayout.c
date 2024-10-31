#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *ROFI_SCREENLAYOUT_DIR = ".screenlayout";

void list(const char *path) {
    struct dirent *file;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Error while opening directory: %s\n", path);
        return;
    }
    regex_t regex;
    if (regcomp(&regex, ".sh$", 0)) {
        return;
    }
    while ((file = readdir(dir)) != NULL) {
        if (regexec(&regex, file->d_name, 0, NULL, 0) == 0) {
            printf("%s\n", file->d_name);
        }
    }
    regfree(&regex);
    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *home = getenv("HOME");
    if (home == NULL) {
        printf("HOME env variable missing\n");
        exit(EXIT_FAILURE);
    }
    const char *dir = getenv("ROFI_SCREENLAYOUT_DIR");
    if (dir == NULL) {
        dir = ROFI_SCREENLAYOUT_DIR;
    }
    char path[1024];
    if (argc < 2) {
        snprintf(path, sizeof(path), "%s/%s", home, dir);
        list(path);
    } else {
        snprintf(path, sizeof(path), "%s/%s/%s", home, dir, argv[1]);
        if (system(path) != 0) {
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}
