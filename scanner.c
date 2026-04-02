#include "include/organix.h"

#ifdef _WIN32
int scan_directory(const char *path, FileEntry *entries, int max_entries) {
    WIN32_FIND_DATA fdata;
    char search_path[MAX_PATH_LEN];
    snprintf(search_path, sizeof(search_path), "%s\\*", path);
    HANDLE hFind =  FindFirstFile(search_path, &fdata);
    if(hFind == INVALID_HANDLE_VALUE) return -1;
    int count = 0;
    do {
        if (count >= max_entries) break;
        if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        if (is_hidden_file(fdata.cFileName)) continue;
        strncpy(entries[count].name, fdata.cFileName, MAX_NAME -1);
        get_extension(fdata.cFileName, entries[count].extension, MAX_EXT);
        path_join(entries[count].full_path, MAX_PATH_LEN, path, fdata.cFileName);
        count++;
    } while (FindNextFile(hFind, &fdata));
    FindClose(hFind);
    return count;
}
#else 
#include <sys/stat.h>
int scan_directory(const char *path, FileEntry *entries, int max_entries){
    DIR *dir = opendir(path);
    if(!dir) { perror("opendir"); return -1;}
    struct dirent *ent;
    int count = 0;
    while ((ent = readdir(dir)) != NULL && count < max_entries) {
        if(is_hidden_file(ent->d_name)) continue;

        char full[MAX_PATH_LEN];
        path_join(full, MAX_PATH_LEN, path, ent->d_name);
        struct stat st;
        if(stat(full, &st) != 0 || !S_ISREG(st.st_mode)) continue;
        strncpy(entries[count].name, ent->d_name, MAX_NAME -1);
        get_extension(ent->d_name, entries[count].extension, MAX_EXT);
        strncpy(entries[count].full_path, full, MAX_PATH_LEN -1);
        count++;
    }
    closedir(dir);
    return count;
}
#endif