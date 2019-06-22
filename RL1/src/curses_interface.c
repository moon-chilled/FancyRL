#include <curses.h>

#include "fancy.h"
#include "graphics.h"

bool curses_init(void) {
	// from the man-page: If errors occur, initscr writes an appropriate error message to standard error and exits; otherwise, a pointer is returned to stdscr
	// so it always returns success
	initscr();

	clear();
	noecho();
	cbreak();
	keypad(stdscr, true);
	curs_set(0);
	start_color();

	return true;
}

void curses_write(u32 glyph, u32 y, u32 x, bool underline, bool bold, bool italic) {
	u32 attrs = 0
		| A_UNDERLINE * underline
		| A_BOLD * bold
		| A_ITALIC * italic;

	attron(attrs);

	mvaddch(y, x, glyph);
}

Key curses_read(void) {
	switch (getch()) {
		case '1': return Key_1;
		case '2': return Key_2;
		case '3': return Key_3;
		case '4': return Key_4;
		case '5': return Key_5;
		case '6': return Key_6;
		case '7': return Key_7;
		case '8': return Key_8;
		case '9': return Key_9;
		case '0': return Key_0;
		case '!': return Key_Bang;
		case '@': return Key_At;
		case '#': return Key_Hash;
		case '$': return Key_Dollar;
		case '%': return Key_Percent;
		case '^': return Key_Caret;
		case '&': return Key_Ampersand;
		case '*': return Key_Asterisk;
		case '(': return Key_Lparen;
		case ')': return Key_Rparen;
		case '-': return Key_Dash;
		case '_': return Key_Underscore;
		case '+': return Key_Plus;
		case '=': return Key_Equals;
		case '|': return Key_Pipe;
		case '\\': return Key_Backslash;
		case '\'': return Key_Squote;
		case '"': return Key_Dquote;
		case 'a': return Key_a;
		case 'b': return Key_b;
		case 'c': return Key_c;
		case 'd': return Key_d;
		case 'e': return Key_e;
		case 'f': return Key_f;
		case 'g': return Key_g;
		case 'h': return Key_h;
		case 'i': return Key_i;
		case 'j': return Key_j;
		case 'k': return Key_k;
		case 'l': return Key_l;
		case 'm': return Key_m;
		case 'n': return Key_n;
		case 'o': return Key_o;
		case 'p': return Key_p;
		case 'q': return Key_q;
		case 'r': return Key_r;
		case 's': return Key_s;
		case 't': return Key_t;
		case 'u': return Key_u;
		case 'v': return Key_v;
		case 'w': return Key_w;
		case 'x': return Key_x;
		case 'y': return Key_y;
		case 'z': return Key_z;
		default: return curses_read();
	}
}

// these functions return int, but our windowprocs functions have to return void
// so we can't dump curses functions straight into curses_windowprocs
void curses_clear(void) { erase(); }
void curses_blit(void) { refresh(); }
void curses_quit(void) { endwin(); }


Windowprocs curses_windowprocs = {
	.init = curses_init,
	.write = curses_write,
	.read = curses_read,
	.clear = curses_clear,
	.blit = curses_blit,
	.quit = curses_quit,
};
