/*
 * ec.c - EC rewrite of WMI functions
 * 
 * Copyright (C) 2017 Jeremy Soller <jeremy@system76.com>
 *
 * This program is free software;  you can redistribute it and/or modify
 * it under the terms of the  GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is  distributed in the hope that it  will be useful, but
 * WITHOUT  ANY   WARRANTY;  without   even  the  implied   warranty  of
 * MERCHANTABILITY  or FITNESS FOR  A PARTICULAR  PURPOSE.  See  the GNU
 * General Public License for more details.
 *
 * You should  have received  a copy of  the GNU General  Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
 
 // EC Registers
 
 #define FCMD 0xF8
 #define FDAT 0xF9
 #define FBUF 0xFA
 #define FBF1 0xFB
 #define FBF2 0xFC
 #define FBF3 0xFD

enum EcKbRegion {
    EC_KB_LEFT,
    EC_KB_CENTER,
    EC_KB_RIGHT,
    EC_KB_EXTRA,
};

static void ec_kb_color_set(enum EcKbRegion region, u32 color) {
    u8 region_code;
    switch(region) {
    case EC_KB_LEFT:
        region_code = 0x3;
        break;
    case EC_KB_CENTER:
        region_code = 0x4;
        break;
    case EC_KB_RIGHT:
        region_code = 0x5;
        break;
    case EC_KB_EXTRA:
        region_code = 0x7;
        break;
    default:
        return;
    }
    
    ec_write(FDAT, region_code);
    ec_write(FBUF, (color & 0xFF));
    ec_write(FBF1, ((color >> 16) & 0xFF));
    ec_write(FBF2, ((color >> 8) & 0xFF));
    ec_write(FCMD, 0xCA);
}

static int ec_init(void) {    
    return 0;
}

static void ec_exit(void) {
}
