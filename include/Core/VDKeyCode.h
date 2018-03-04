/*
    VDEngine virtual dimension game engine.
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_KEYCODE_H_
#define _VD_KEYCODE_H_ 1


/**
 *
 */
enum VDKeyCodes{
    VD_UNKNOWN = 0,

    VD_RETURN = '\r',
	VD_ENTER = '\r',
    VD_ESCAPE = '\033',
    VD_BACKSPACE = '\b',
    VD_TAB = '\t',
    VD_SPACE = ' ',
    VD_EXCLAIM = '!',
    VD_QUOTEDBL = '"',
    VD_HASH = '#',
    VD_PERCENT = '%',
    VD_DOLLAR = '$',
    VD_AMPERSAND = '&',
    VD_QUOTE = '\'',
    VD_LEFTPAREN = '(',
    VD_RIGHTPAREN = ')',
    VD_ASTERISK = '*',
    VD_PLUS = '+',
    VD_COMMA = ',',
    VD_MINUS = '-',
    VD_PERIOD = '.',
    VD_SLASH = '/',
    VD_0 = '0',
    VD_1 = '1',
    VD_2 = '2',
    VD_3 = '3',
    VD_4 = '4',
    VD_5 = '5',
    VD_6 = '6',
    VD_7 = '7',
    VD_8 = '8',
    VD_9 = '9',
    VD_COLON = ':',
    VD_SEMICOLON = ';',
    VD_LESS = '<',
    VD_EQUALS = '=',
    VD_GREATER = '>',
    VD_QUESTION = '?',
    VD_AT = '@',
    /*
    Skip uppercase letters
    */
    VD_LEFTBRACKET = '[',
    VD_BACKSLASH = '\\',
    VD_RIGHTBRACKET = ']',
    VD_CARET = '^',
    VD_UNDERSCORE = '_',
    VD_BACKQUOTE = '`',
    VD_a = 'a',
    VD_b = 'b',
    VD_c = 'c',
    VD_d = 'd',
    VD_e = 'e',
    VD_f = 'f',
    VD_g = 'g',
    VD_h = 'h',
    VD_i = 'i',
    VD_j = 'j',
    VD_k = 'k',
    VD_l = 'l',
    VD_m = 'm',
    VD_n = 'n',
    VD_o = 'o',
    VD_p = 'p',
    VD_q = 'q',
    VD_r = 'r',
    VD_s = 's',
    VD_t = 't',
    VD_u = 'u',
    VD_v = 'v',
    VD_w = 'w',
    VD_x = 'x',
    VD_y = 'y',
    VD_z = 'z',

    VD_Left,
    VD_Right,
    VD_Up,
    VD_Down,
    VD_Numpad0,
    VD_Numpad1,
    VD_Numpad2,
    VD_Numpad3,
    VD_Numpad4,
    VD_Numpad5,
    VD_Numpad6,
    VD_Numpad7,
    VD_Numpad8,
    VD_Numpad9,
    VD_F1,
    VD_F2,
    VD_F3,
    VD_F4,
    VD_F5,
    VD_F6,
    VD_F7,
    VD_F8,
    VD_F9,
    VD_F10,
    VD_F11,
    VD_F12,
    VD_F13,
    VD_F14,
    VD_F15,
    VD_Pause,
	VD_Add,
	VD_Subtract,
	VD_Multiply,
	VD_Divide,
	VD_End,
	VD_Home,
	VD_Insert,
	VD_Delete,
	VD_LControl,
	VD_LShift,
	VD_LAlt,
	VD_LSystem,
	VD_RControl,
	VD_RShift,
	VD_RAlt,
	VD_RSystem,

};

#endif
