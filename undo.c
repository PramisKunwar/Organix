#include "include/organix.h"
#define UNDO_LOG_FILE ".organix_undo_log"

int save_undo_log(const char *base_dir, MoveRecord *records, int count) {
    char log_path[MAX_PATH_LEN];
    path_join(log_path, MAX_PATH_LEN, base_dir, UNDO_LOG_FILE);
    FILE *fp = fopen(log_path,"w");
    if (!fp) { perror("Failed to create undo log"); return -1;}
  for(int i = 0; i < count; i++) {
    fprintf(fp, "%s -> %s\n", records[i].original_path, records[i].new_path);
  }
fclose(fp);
return 0;
}

  int perform_undo(const char *base_dir) {
    char log_path[MAX_PATH_LEN];
    path_join(log_path, MAX_PATH_LEN, base_dir, UNDO_LOG_FILE);
    FILE *fp = fopen(log_path, "r");
    if (!fp){ fprintf(stderr, "No undo log found in %s\n",base_dir); return -1;}
    char line[MAX_PATH_LEN *2 + 8];
    int restored = 0, failed = 0;
    while( fgets(line, sizeof(line), fp)){
        line[strcspn(line, "\n")] = '\0';
        char *arrow = strstr(line, " -> ");
        if(!arrow) continue;
        *arrow = '\0';
        if (rename(arrow + 4, line) == 0) restored++; else { fprintf(stderr, "Failed to restore: %s\n", arrow+4); failed++;}
    }
    fclose(fp); remove(log_path);
    printf("Undo complete: %d restored, %d failed\n", restored, failed);
    return(failed > 0) ? -1 : 0;
  }