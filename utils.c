#include "include/organix.h"
#include <ctype.h>

void get_extension(const char *filename, char *ext, int ext_size) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) { ext[0] = '\0'; return; }
    strncpy(ext, dot +1, ext_size -1);
    ext[ext_size - 1] = '\0';
    for (int i = 0; ext[i]; i++) ext[i] = (char)tolower((unsigned char)ext[i]);
}

int is_hidden_file(const char *name) { return (name[0] == '.');}

void path_join(char *dest, int dest_size, const char *dir, const char *file) {
    snprintf(dest, dest_size, "%s%c%s", dir, PATH_SEP, file);
}