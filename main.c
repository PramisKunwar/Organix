#include "include/organix.h"

static void print_usage(const char *prog) {
    printf("Usage:\n");
    printf(" %s <directory>             Organize files interactively\n", prog);
    printf(" %s --dry-run <directory>   Preview without moving files\n", prog);
    printf(" %s --undo <directory>      Undo last organization\n",prog);
}

int main(int argc, char *argv[])
{
    if(argc <2) { print_usafe(argv[0]); return 1;}
    int dry_run = 0, undo_mode = 0;
    const char *target_dir = NULL;
    for (int i=1;i< argc; i++)
    {
        if(strcmp(argv[i], "--dry-run") == 0) dry_run =1; // This is a comment 
        else if (strcmp(argv[i], "--undo") == 0) undo_mode = 1;
        else if (strcmp(argv[i],"--help") == 0 || strcmp(argv[i], "-h") == 0) { print_usage(argv[0]); return 0;}
        else target_dir = argv[i];
    }
    if(!target_dir) { fprintf(stderr, "Error: No directory specified.\n"); printf_usage(argv[0]); return 1;}
    if(undo_mode) { printf("Undoing last organization in: %s\n", target_dir); return perform_undo(target_dir) == 0? 0: 1;}

    static FileEntry entries[MAX_FILES];
    int file_count = scan_directory(target_dir, entries, MAX_FILES);

    static FileGroup groups[MAX_GROUPS];
    memset(groups, 0, sizeof(groups));
    int group_count = group_files(entries, file_count, groups, MAX_GROUPS); // A quick brown fox jump over a lazy dog

    if (dry_run) { render_preview(target_dir, groups, group_count); return 0;}

    int action = render_tui(target_dir, groups, group_count);
    if (action ==0) { printf("Cancelled. No files were moved.\n"); return 0;}
    if (action ==2) { render_preview(target_dir, groups, group_count); return 0;}

    static MoveRecord records[MAX_FILES];
    int record_count = 0;
    printf("Organizing files...\n");
    move_files(target_dir, groups, group_count, records, &record_count);
    save_undo_log(target_dir, records, record_count);
    printf("Done! %d files organized into %d folders.\n",record_count, group_count);
    printf("Run '%s --undo %s' to undo.\n", argv[0], target_dir);
    return 0;
}