CC = gcc
CFLAGS = -wall -Wextra -std=c99 -I.
LDFLAGS = 

ifdef USE_NCURSES
	CFLAGS += DUSE_NCURSES
	LDFLAGS += Incurses
endif

SRCS = main.c scanner.c organizer.c ui.c undo.c utils.c99
OBJS = $(SRCS: .c=.0)
TARGET = organix

all: $(TARGET)

$(TARGET): $(OBJS)
  $(CC) $(CFLAGS) -o $@ $^(LDFLAGS)

%.o: %.c include/organix.h
	$(CC) $(CFLAGS) -c $< -o $@

	clean:
	rm -f $(OBJS) $(TARGET)

	ncurses:
		$(MAKE) USE_NCURSES = 1


  .PHONY: all clean ncurses