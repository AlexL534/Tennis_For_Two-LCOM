#include "menu.h"
#include "xpms.h"


int (initialize_menu)(Menu *menu){
    if(menu == NULL){
        return EXIT_FAILURE;
    }

    menu->selected=1;
    xpm_image_t img;
    Sprite *sprite = malloc(sizeof(Sprite));
    //sprite->map = (uint32_t *) xpm_load((xpm_map_t) title_xpm, XPM_8_8_8_8, &img);
    sprite->height = img.height;
    sprite->width = img.width;
    menu->title = *sprite;

    //sprite->map = (uint32_t *) xpm_load((xpm_map_t) start_xpm, XPM_8_8_8_8, &img);
    sprite->height = img.height;
    sprite->width = img.width;
    menu->play_button = *sprite;

    //sprite->map = (uint32_t *) xpm_load((xpm_map_t) quit_xpm, XPM_8_8_8_8, &img);
    sprite->height = img.height;
    sprite->width = img.width;
    menu->quit = *sprite;


}