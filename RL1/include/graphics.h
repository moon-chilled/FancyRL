#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "fancy.h"

typedef enum {
	Key_1,
	Key_2,
	Key_3,
	Key_4,
	Key_5,
	Key_6,
	Key_7,
	Key_8,
	Key_9,
	Key_0,
	Key_bang,
	Key_at,
	Key_hash,
	Key_dollar,
	Key_percent,
	Key_caret,
	Key_ampersand,
	Key_asterisk,
	Key_lparen,
	Key_rparen,
	Key_dash,
	Key_underscore,
	Key_plus,
	Key_equals,
	Key_tab,
	Key_pipe,
	Key_backslash,
	Key_squote,
	Key_dquote,
	Key_a,
	Key_b,
	Key_c,
	Key_d,
	Key_e,
	Key_f,
	Key_g,
	Key_h,
	Key_i,
	Key_j,
	Key_k,
	Key_l,
	Key_m,
	Key_n,
	Key_o,
	Key_p,
	Key_q,
	Key_r,
	Key_s,
	Key_t,
	Key_u,
	Key_v,
	Key_w,
	Key_x,
	Key_y,
	Key_z,
	Key_period,
	Key_comma,
	Key_lessthan,
	Key_greaterthan,
	Key_semicolon,
	Key_colon,
	Key_lbracket,
	Key_rbracket,
	Key_lbrace,
	Key_rbrace,
	Key_slash,
	Key_question,

	Key_space,
	Key_enter,
	Key_esc,
	//Key_delete, //TODO: figure out how/whether this works
	Key_backspace,
	Key_pgup,
	Key_pgdown,
	Key_home,
	Key_end,
	Key_up,
	Key_down,
	Key_left,
	Key_right,
} Key;


typedef struct {
	bool (*init)(void); // returns success
	void (*write)(u32 glyph, u32 y, u32 x, u32 fgclr, u32 bgclr, bool underline, bool bold, bool italic);
	Key (*read)(void);
	void (*clear)(void);
	void (*blit)(void);
	void (*quit)(void);
} Windowprocs;

extern Windowprocs curses_windowprocs;
extern Windowprocs blt_windowprocs;

#endif //GRAPHICS_H
