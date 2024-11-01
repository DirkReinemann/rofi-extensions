#include "config.h"
#include <stdlib.h>
#include <string.h>

const char *get_env_or_alt(const char *key, const char *alt) {
    const char *val = getenv(key);
    if (val == NULL || strcmp(val, "") == 0) {
        val = alt;
    }
    return val;
}
