#include <BearLibTerminal.h>

#include "fancy.h"
#include "graphics.h"

bool blt_init(void) {
	i32 res = terminal_open();
	if (!res) {
		return false;
	}

	terminal_set("input.cursor-blink-rate=2147483647");
	terminal_set("input.cursor-symbol=0x2588");
	terminal_set("font: dvsm.ttf, use-box-drawing=false, use-block-elements=false, size=12x24");
	terminal_set("default font: dvsm.ttf, use-box-drawing=false, use-block-elements=false, size=12x24");
	terminal_set("italic font: dvsmi.ttf, use-box-drawing=false, use-block-elements=false, size=12x24");
	terminal_set("bold font: dvsmb.ttf, use-box-drawing=false, use-block-elements=false, size=12x24");
	terminal_set("bolditalic font: dvsmbi.ttf, use-box-drawing=false, use-block-elements=false, size=12x24");

	return true;
}

void blt_write(u32 glyph, u32 y, u32 x, bool underline, bool bold, bool italic) {
	const char *fontab[2][2] = {{"default", "italic"}, {"bold", "bolditalic"}};
	terminal_font(fontab[bold][italic]);

	terminal_put(x, y, glyph);

	// underline => draw an underline character on top of it (not under it)
	if (underline) {
		terminal_layer(1);
		terminal_put(x, y, u'▁');
		terminal_layer(0);
	}

	// shouldn't be necessary -- because every blt_write call overwrites
	// the font, but just in case
	terminal_font("default");
}

Key blt_read(void) {
	switch (terminal_read()) {
		case TK_1: return Key_1;
		case TK_2: return Key_2;
		case TK_3: return Key_3;
		case TK_4: return Key_4;
		case TK_5: return Key_5;
		case TK_6: return Key_6;
		case TK_7: return Key_7;
		case TK_8: return Key_8;
		case TK_9: return Key_9;
		case TK_0: return Key_0;
		// commented out entries aren't literal keys, but shift-
		// combinations-- have to figure that out by peeking at shift
		// TODO:
		/*
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
		*/
		case TK_MINUS: return Key_Dash;
		//case '_': return Key_Underscore;
		//case '+': return Key_Plus;
		case TK_EQUALS: return Key_Equals;
		//case '|': return Key_Pipe;
		case TK_BACKSLASH: return Key_Backslash;
		case TK_APOSTROPHE: return Key_Squote;
		//case '"': return Key_Dquote;
		case TK_A: return Key_a;
		case TK_B: return Key_b;
		case TK_C: return Key_c;
		case TK_D: return Key_d;
		case TK_E: return Key_e;
		case TK_F: return Key_f;
		case TK_G: return Key_g;
		case TK_H: return Key_h;
		case TK_I: return Key_i;
		case TK_J: return Key_j;
		case TK_K: return Key_k;
		case TK_L: return Key_l;
		case TK_M: return Key_m;
		case TK_N: return Key_n;
		case TK_O: return Key_o;
		case TK_P: return Key_p;
		case TK_Q: return Key_q;
		case TK_R: return Key_r;
		case TK_S: return Key_s;
		case TK_T: return Key_t;
		case TK_U: return Key_u;
		case TK_V: return Key_v;
		case TK_W: return Key_w;
		case TK_X: return Key_x;
		case TK_Y: return Key_y;
		case TK_Z: return Key_z;
		default: return blt_read();
	}
}

Windowprocs blt_windowprocs = {
	.init = blt_init,
	.write = blt_write,
	.read = blt_read,
	.clear = terminal_clear,
	.blit = terminal_refresh,
	.quit = terminal_close,
};
