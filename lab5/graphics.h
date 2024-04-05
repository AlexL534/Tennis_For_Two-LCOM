#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

int (intialize_graphics_mode)(uint16_t mode);
int (map_VRAM)(uint16_t mode);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
vbe_mode_info_t (get_mode_inf)();
unsigned (get_hres)();
unsigned (get_vres)();
unsigned (get_bits_per_pixel)();
unsigned (get_bytes_per_pixel)();
#endif
