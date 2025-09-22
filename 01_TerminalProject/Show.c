#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <locale.h>
#include <string.h>

#define DX 7
#define DY 3
#define MAX_LINE_LENGTH 1024

void cut_str(char* str, int w_cols) {
	int cur_len = strlen(str);
	if (cur_len == 0) {
		return;
	}
	if (str[cur_len - 1] == '\n') {
		str[cur_len - 1] = '\0';
		cur_len -= 1;
	}
	if (cur_len > w_cols - 1) {
		str[w_cols - 1] = '\0';		
	}
	return;
}


int main(int argc, char *argv[]) {
	WINDOW *frame, *win;
	char *name;
	FILE *file = NULL;
	
	if (argc > 1) {
		name = argv[1];
		file = fopen(argv[1], "r");
    }

	setlocale(LC_ALL, "");
	initscr();
	noecho();
	cbreak();
	refresh();

	frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
	box(frame, 0, 0);
	mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5) / 2), name);
	wrefresh(frame);

	win = newwin(LINES - 2*DY - 2, COLS - 2*DX-2, DY+1, DX+1);
	int w_lines = LINES - 2*DY - 2;
	int w_cols = COLS - 2*DX-2;
	
	scrollok (win, TRUE);
	char line[MAX_LINE_LENGTH];
	int cur_line = 0;
	while (cur_line < w_lines && fgets(line, sizeof(line), file) != NULL) {
		cut_str(line, w_cols);
		wprintw(win, "%s", line);
		cur_line++;
		if (cur_line < w_lines) {
			wprintw(win, "\n");
		}
	}
	
	wrefresh(win);
	keypad(win, TRUE);

	int c = 0;
	while((c = wgetch(win)) != 27)
		if (c == 32) {
			if (fgets(line, sizeof(line), file) != NULL) {
				cut_str(line, w_cols);
				wprintw(win, "\n%s", line);
				wrefresh(win);
			}
		}
	delwin(win);
	delwin(frame);
	endwin();
	fclose(file);
	
	return 0;
}
