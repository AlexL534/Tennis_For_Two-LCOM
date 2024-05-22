#include "menu.h"
#include "color.h"
#include <stdlib.h> 

Mouse* createMouse() {
    Mouse* mouse = (Mouse*)malloc(sizeof(Mouse));
    if (mouse == NULL) {
        return NULL;
    }

    mouse->sprite = (Sprite*)malloc(sizeof(Sprite));
    if (mouse->sprite == NULL) {
        free(mouse);
        return NULL;
    }

    xpm_image_t img;
    mouse->sprite->map = (uint32_t *) xpm_load((xpm_map_t) cursor_xpm, XPM_8_8_8_8, &img);
    if (mouse->sprite->map == NULL) {
        free(mouse->sprite);
        free(mouse);
        return NULL;
    }
    mouse->sprite->width = img.width;
    mouse->sprite->height = img.height;

    mouse->x = 0;
    mouse->y = 0;

    return mouse;
}

int drawMouse(Mouse* mouse) {
    if (mouse == NULL || mouse->sprite == NULL) {
        return EXIT_FAILURE;
    }

    int width = mouse->sprite->width;
    int height = mouse->sprite->height;
    uint32_t *map = mouse->sprite->map;

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            uint16_t x = mouse->x + i;
            uint16_t y = mouse->y + j;

            if (x < MAX_X && y < MAX_Y && *map != TRANSPARENCY_COLOR) {
                if (vg_draw_color(x, y, *map) != 0) {
                    return EXIT_FAILURE;
                }
            }
            map++;
        }
    }
    return EXIT_SUCCESS;
}

void destroyMouse(Mouse* mouse) {
    if (mouse == NULL) {
        return;
    }

    if (mouse->sprite != NULL) {
        free(mouse->sprite->map);
        free(mouse->sprite);
    }

    free(mouse);
}

int updateMousePosition(Mouse* mouse, int dx, int dy) {
    mouse->x += dx;
    mouse->y -= dy;

    // Adjust for screen boundaries
    if (mouse->x < 0) {
        mouse->x = 0;
    } else if (mouse->x + mouse->sprite->width > MAX_X) {
        mouse->x = MAX_X - mouse->sprite->width;
    }

    if (mouse->y < 0) {
        mouse->y = 0;
    } else if (mouse->y + mouse->sprite->height > MAX_Y) {
        mouse->y = MAX_Y - mouse->sprite->height;
    }

    return EXIT_SUCCESS;
}
