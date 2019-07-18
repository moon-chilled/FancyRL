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


// http://stackoverflow.com/a/41978310
static i32 rgb_colour_to_curses_colour(u32 clr) {
#define v2ci(v) (v < 48 ? 0 : v < 115 ? 1 : (v - 35) / 40)
#define color_index() (36 * ir + 6 * ig + ib)
#define dist_square(A,B,C, a,b,c) ((A-a)*(A-a) + (B-b)*(B-b) + (C-c)*(C-c))
	u8 r = (clr & 0xff0000) >> 16;
	u8 g = (clr & 0x00ff00) >> 8;
	u8 b = (clr & 0x0000ff) >> 0;

	static const i32 i2cv[6] = {0, 0x5f, 0x87, 0xaf, 0xd7, 0xff};

	i32 ir = v2ci(r), ig = v2ci(g), ib = v2ci(b);

	i32 average = (r + g + b) / 3;
	i32 gray_index = average > 238 ? 23 : (average - 3) / 10;

	i32 cr = i2cv[ir], cg = i2cv[ig], cb = i2cv[ib];
	i32 gv = 8 + 10 * gray_index;

	i32 color_err = dist_square(cr, cg, cb, r, g, b);
	i32 gray_err  = dist_square(gv, gv, gv, r, g, b);

	return color_err <= gray_err ? 16 + color_index() : 232 + gray_index;
#undef v2ci
#undef color_index
#undef dist_square
}

void curses_write(u32 glyph, u32 y, u32 x, u32 fg, u32 bg, bool underline, bool bold, bool italic) {
	typedef struct {
		u32 fg;
		u32 bg;
	} CursesClr;
	static CursesClr *curses_colours;
	static usz num_curses_colours;

	u32 attrs = 0
		| A_UNDERLINE * underline
		| A_BOLD * bold
		| A_ITALIC * italic;

	attron(attrs);
	// TODO: better colour handling

	usz colour_index;

	bool colour_pair_in_table = false;
	for (usz i = 0; i < num_curses_colours; i++) {
		if (curses_colours[i].fg == fg && curses_colours[i].bg == bg) {
			colour_pair_in_table = true;
			colour_index = i;
			break;
		}
	}
	if (!colour_pair_in_table) {
		colour_index = num_curses_colours;
		curses_colours = realloc(curses_colours, sizeof(CursesClr) * (++num_curses_colours));
		curses_colours[colour_index] = (CursesClr){fg, bg};
		init_pair(colour_index, rgb_colour_to_curses_colour(fg), rgb_colour_to_curses_colour(bg));
	}


	attron(COLOR_PAIR(colour_index));

	mvaddch(y, x, glyph);
	attroff(attrs);
	attroff(COLOR_PAIR(colour_index));
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
		case '!': return Key_bang;
		case '@': return Key_at;
		case '#': return Key_hash;
		case '$': return Key_dollar;
		case '%': return Key_percent;
		case '^': return Key_caret;
		case '&': return Key_ampersand;
		case '*': return Key_asterisk;
		case '(': return Key_lparen;
		case ')': return Key_rparen;
		case '-': return Key_dash;
		case '_': return Key_underscore;
		case '+': return Key_plus;
		case '=': return Key_equals;
		case '\t': return Key_tab;
		case '|': return Key_pipe;
		case '\\': return Key_backslash;
		case '\'': return Key_squote;
		case '"': return Key_dquote;
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
		case '.': return Key_period;
		case ',': return Key_comma;
		case '<': return Key_lessthan;
		case '>': return Key_greaterthan;
		case ';': return Key_semicolon;
		case ':': return Key_colon;
		case '[': return Key_lbracket;
		case ']': return Key_rbracket;
		case '{': return Key_lbrace;
		case '}': return Key_rbrace;
		case '/': return Key_slash;
		case '?': return Key_question;

		case ' ': return Key_space;
		case '\n': return Key_enter;
		case '\033': return Key_esc;
		case '\b': case KEY_BACKSPACE: return Key_backspace;
		case KEY_PPAGE: return Key_pgup; // (p)revious page
		case KEY_NPAGE: return Key_pgdown; // (n)ext
		case KEY_HOME: return Key_home;
		case KEY_END: return Key_end;
		case KEY_UP: return Key_up;
		case KEY_DOWN: return Key_down;
		case KEY_LEFT: return Key_left;
		case KEY_RIGHT: return Key_right;

		default: return curses_read();
	}
}

// these functions return int, but our windowprocs functions have to return void
// so we can't dump curses functions straight into curses_windowprocs
void curses_blit(void) { refresh(); }
void curses_quit(void) { endwin(); }
void nop() {}


Windowprocs curses_windowprocs = {
	.init = curses_init,
	.write = curses_write,
	.read = curses_read,
	.clear = nop,
	.blit = curses_blit,
	.quit = curses_quit,
};
