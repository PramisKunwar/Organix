#include "include/organix.h"

#ifndef _WIN32
f    #include <conio.h>
    #define CLEAR_SCREEN system("cls")
#else
    #define CLEAR_SCREEN system("clear")
#endif

#ifdef USE_NCURSES
#include <ncurses.h>

int render_tui(const char *dir, FileGroup *groups, int group_count) {
    initscr(); cbreak(); noecho(); keypad(stdscr, TRUE); curs_set(0);
    init max_y, max_x; getmaxyx(stdscr, max_y, max_x); (void)max_x;
    attron(A_BOLD | A_REVERSE);
    mvprintw(0,0, "ORGANIZ -Terminal File Organizerr ");
    attroff(A_BOLD | A_REVERSE);
    mvprintw(2,2,"Directory: %s", dir);
    mvprintw(3,2, "-------------------");
    int row = 5, total_files = 0;
    for (int g = 0;g<group_count && row < max_y -3; g++) {
        attron(A_BOLD); mvprintw(row++, 2, "%s/(%d files)", groups[g].folder_name, groups[g].count); attroff(A_BOLD);
        total_files += groups[g].count;
        for(int f = 0; f < groups[g].count && row < max_y -3; f++)
            mvprintw(row++, 6, "- %s", groups[g].files[f].name);
            row++;
    }
    attron(A_BOLD); mvprintw(max_y -3, 2, "Total: %d files in %d groups ", total_files, group_count); attroff(A_BOLD);
    attron(A_REVERSE); mvprintw(max_y -1, 0, "[Enter] Organize     [Q] Quit     [D] Dry Run "); attroff(A_REVERSE);
    refresh();
    int ch;
    while ((ch = getch())) {
        if (ch == '\n' || ch == KEY_ENTER)  { endwin(); return 1;}
        if (ch == 'q' || ch == 'Q') { endwin(); return 0; }
        if (ch == 'd' || ch == 'D') { endwin(); return 2; }
    }
    endwin(); return 0;
}

#else 

int render_tui(const char *dir, FileGroup *groups, int group_count){
    CLEAR_SCREEN;
    printf("======================================\n");
    printf(" ORGANIX - Terminal File Organizer\n");
    printf("=====================================\n\n");
    printf("  Directory: %s\n", dir);
    printf(" ---------------------------------\n\n");
    int total_files = 0;
    for(int g= 0; g < group_count; g++){
        printf(" %s/ (%d files)\n", groups[g].folder_name, groups[g].count);
        total_files += groups[g].count;
        for( int f = 0; f < groups[g].count; f++)
        printf("        - %s\n", groups[g].files[f].name);
        printf("\n");
    }

    printf("  Total: %d file in %d groups\n\n", total_files, group_count);
    printf("  [Enter] Organize    [Q] Quit\n\n > ");
    fflush(stdout);
    int ch = getchar();
    if(ch =='\n' || ch == '\r') return 1;
    if( ch == 'q' || ch == 'Q') return 0;
    return 0;
}
#endif

  void render_preview(const char *dir, FileGroup *groups, int group_count){
    printf("\n[DRY RUN] Preview for: %s\n===================================\n\n", dir);
    int total = 0;
    for(int g=0; g<group_count; g++){
        printf(" %s\n", groups[g].folder_name);
        total += groups[g].count;
        for (int f=0; f<groups[g].count;f++)
            printf("    %s\n",groups[g].files[f].name);
        printf("\n");
    }
    printf("Total: %d files would be organized into %d folders. \nNo files were moved. \n", total, group_count);
  }