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
	Key_Bang,
	Key_At,
	Key_Hash,
	Key_Dollar,
	Key_Percent,
	Key_Caret,
	Key_Ampersand,
	Key_Asterisk,
	Key_Lparen,
	Key_Rparen,
	Key_Dash,
	Key_Underscore,
	Key_Plus,
	Key_Equals,
	Key_Pipe,
	Key_Backslash,
	Key_Squote,
	Key_Dquote,
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
} Key;


typedef struct {
	bool (*init)(void); // returns success
	// TODO: colour
	void (*write)(u32 glyph, u32 y, u32 x, bool underline, bool bold, bool italic);
	Key (*read)(void);
	void (*clear)(void);
	void (*blit)(void);
	void (*quit)(void);
} Windowprocs;

extern Windowprocs curses_windowprocs;
//extern Windowprocs blt_windowprocs;

#endif //GRAPHICS_H
