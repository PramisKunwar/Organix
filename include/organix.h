#ifndef ORGANIX_H
#define ORGANIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
    #define PATH_SEP '\\'
    #define MKDIR(path) _mkdir(path)
#else 
    #include <dirent.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #define PATH_SEP '/'
    #define MKDIR(path) mkdir(path,0755)
#endif

#define MAX_FILES 4096
#define MAX_NAME 256
#define MAX_PATH_LEN 1024
#define MAX_EXT 32 
#define MAX_GROUPS 6

 typedef struct {
    char name[MAX_NAME];
    char extension[MAX_EXT];
    char full_path[MAX_PATH_LEN];
 } FileEntry;

  typedef struct {
    char folder_name[MAX_NAME];
    FileEntry files[MAX_FILES];
    int count;
  } FileGroup;

   typedef struct {
    char original_path[MAX_PATH_LEN];
    char new_path[MAX_PATH_LEN];
   } MoveRecord;

   int scan_directory(const char *path, FileEntry *entries, int max_entries);
   int group_files(FileEntry *entries, int count, FileGroup *groups, int max_groups);
   const char *get_category(const char * extension);
   int move_files(const char *base_dir, FileGroup *groups, int group_count, MoveRecord *records, int *record_count);
   void render_preview(const char *dir, FileGroup *groups, int group_count);
   int render_tui(const char *dir, FileGroup *groups, int group_count);
   int save_undo_log(const char *base_dir, MoveRecord *records, int count);
   int perform_undo(const char *base_dir);
   void get_extension(const char *filename, char *ext, int ext_size);
   int is_hidden_file(const char *name);
   void path_join(char *dest, int dest_size, const char *dir, const char *file);

#endif