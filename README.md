# Organix  
Organix is a terminal-based file organizer written in C. It scans a directory and sorts file into subfolders based on their extension (i.e. Images, Documents, Vidoes, Audio, Archives, Others). It provides an interactive preview (TUI) before moving files, supports a dry-run mode and includes an undo feature.

---
![Screenshot 1](/ORGANIX.png)

---
![Screenshot 2](/ORGANIX1.png)

---
![Screenshot 3](/ORGANIX2.png)

---


## Program flow (main.c)
--dry-run ==> show a preview with render_preview() and exit.  
else launch the interactive TUI (render_tui()) and ask the user to confirm.  
if user confirms- move files with move_files(), save an undo log with save_undo_log() and print a summary  
--undo ==> call perform_undo() to reverse the last organization.  

scan the directory using scan_directory()  
group files by category using group_files()  

---

## core concepts used:
- Basics
- Pointers
- Strcutures
- Preprocessor macros
- Standard library functions
- Directory operations
- File system operations
- Command-line arguments
- Modular programming
- Makerfiles

---

## Code structure:

1. organix.h - Header file:
three strcuture types: FileEntry, FileGroup, MoveRecord

2. main.c - Entry point
print_usage() 

3. scanner.c - Directory Scanning

Platform-specific code, system calls, error handling, string concatenation

4. organizer.c - Grouping and Moving

get_category()
group_files()
move_files()

5. ui.c - user interface

NCURSES ( if USE_NCURSES defined):
Uses ncurses library for a full-screen TUI with colors and keyboard controls.

Fallback (no ncurses):
Simple console output with printf and getchar.

6. undo.c - Undo functionality 

save_undo_log()

perform_undo()

7. utils.c -Utility Functions 

get_extension()

is_hidden_file()

path_join()

---

## Key C features used in the project 

- Preprocessor Macros
#define constants and platform-specific code
#ifdef_WINN32
#if def USE_NCURSES

- Arrays and Pointers

- Structures

- String Handling

- FILE I/O and System Calls: 
POSIX: opendir, readdir, closedir, stat, rename, mkdir.  
Windows: FindFirstFile, FindNextFile, FinfClose, _mkdir.  
Standard: fopen, fegts, fprintf, fclose, remove

- Error Handling

- Modular Design

---

## License 
Made for hack club


## Author 
Pramis Kunwar
