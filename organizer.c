#include "include/organix.h"

typedef struct { const char *extensions[16]; int ext_count; const char *folder;} CategoryMap;

static CategoryMap categories[] ={
    { {"jpg","jpeg","png","gif","bmp","svg","webp","ico","tiff"}, 9, "Images" },
    { {"pdf","doc","docx","txt","odt","xls","xlsx","ppt","pptx","csv","rtf"}, 11, "Documents" },
    { {"mp4","mkv","avi","mov","wmv","flv","webm"}, 7, "Videos" },
    { {"mp3","wav","flac","aac","ogg","wma","m4a"}, 7, "Audio" },
    { {"zip","tar","gz","rar","7z","bz2","xz","tgz"}, 8, "Archives" },
};
#define NUM_CATEGORIES (sizeof(categories) / sizeof(categories[0]))

const char *get_category(const char *extension) {
    if(!extension || extension[0] == '\0') return "Others";
    for(size_t i = 0; i< NUM_CATEGORIES; i++)
        for (int j=0;j<categories[i].ext_count;j++)
            if (strcmp(extension, categories[i].extensions[j]) ==0)
                return categories[i].folder;
        return "Others";
}

 int group_files(FileEntry *entries, int count, FileGroup *groups, int max_groups){
    int group_count = 0;
    for(int i=0; i< count; i++){
        const char *cat = get_category(entries[i].extension);
        int gidx = -1;
        for(int g = 0; g< group_count; g++)
            if (strcmp(groups[g].folder_name, cat) == 0) { gidx = g; break; }
        if(gidx == -1){
            if(group_count >= max_groups ) continue;
            gidx = group_count++;
            strncpy(groups[gidx].folder_name, cat, MAX_NAME -1);
            groups[gidx].count = 0;
        }
        if (groups[gidx].count < MAX_FILES)
            groups[gidx].files[groups[gidx].count++] = entries[i];
    }
    return group_count;
}

int move_files(const char *base_dir, FileGroup *groups, int group_count, MoveRecord *records, int *record_count) {
    *record_count = 0;
    for(int g =0; g< group_count; g++){
        char folder_path[MAX_PATH_LEN];
        path_join(folder_path, MAX_PATH_LEN, base_dir, groups[g].folder_name);
        MKDIR(folder_path);
        for(int f=0;f<groups[g].count;f++) {
            char new_path[MAX_PATH_LEN];
            path_join(new_path, MAX_PATH_LEN, folder_path, groups[g].files[f].name);
            if (rename(groups[g].files[f].full_path, new_path) ==0) {
                strncpy(records[*record_count].original_path, groups[g].files[f].full_path, MAX_PATH_LEN -1);
                strncpy(records[*record_count].new_path, new_path, MAX_PATH_LEN -1);
                (*record_count)++;
            } else fprintf(stderr, "Failed to move: %s\n", groups[g].files[f].name);
        }
    }
    return 0;
}

