#include "menu.h"
#include "color.h"
#include <stdlib.h>



Menu* (initialize_menu)(bool isStartMenu){
    Menu *menu = (Menu*)malloc(sizeof(Menu));
    if(menu == NULL){
        printf("Menu is null");
        return NULL;
    }
    
    menu->selected=0;

    xpm_image_t img;

    if (isStartMenu) {
        Sprite *sprite_title = (Sprite*) malloc(sizeof(Sprite));
        sprite_title->map = (uint32_t *) malloc(sizeof(char*));
        sprite_title->map = (uint32_t *) xpm_load((xpm_map_t) title_xpm, XPM_8_8_8_8, &img);
        sprite_title->height = img.height;
        sprite_title->width = img.width;
        menu->title = *sprite_title;

        free(sprite_title);

        if(menu->title.map==NULL){
            printf("title is null");
            return NULL;
        }

        Sprite *sprite_start_button = (Sprite*) malloc(sizeof(Sprite));
        sprite_start_button->map = (uint32_t *) malloc(sizeof(char*));
        sprite_start_button->map = (uint32_t *) xpm_load((xpm_map_t) start_xpm, XPM_8_8_8_8, &img);
        sprite_start_button->height = img.height;
        sprite_start_button->width = img.width;
        menu->play_button = *sprite_start_button;

        free(sprite_start_button);

        Sprite *sprite_quit_button = (Sprite*) malloc(sizeof(Sprite));
        sprite_quit_button->map = (uint32_t *) malloc(sizeof(char*));
        sprite_quit_button->map = (uint32_t *) xpm_load((xpm_map_t) quit_xpm, XPM_8_8_8_8, &img);
        sprite_quit_button->height = img.height;
        sprite_quit_button->width = img.width;
        menu->quit = *sprite_quit_button;

        free(sprite_quit_button);

        Sprite *sprite_start_button_hover = (Sprite*) malloc(sizeof(Sprite));
        sprite_start_button_hover->map = (uint32_t *) malloc(sizeof(char*));
        sprite_start_button_hover->map = (uint32_t *) xpm_load((xpm_map_t) start_hover_xpm, XPM_8_8_8_8, &img);
        sprite_start_button_hover->height = img.height;
        sprite_start_button_hover->width = img.width;
        menu->play_button_hover = *sprite_start_button_hover;
    
        free(sprite_start_button_hover);

        Sprite *sprite_quit_button_hover = (Sprite*) malloc(sizeof(Sprite));
        sprite_quit_button_hover->map = (uint32_t *) malloc(sizeof(char*));
        sprite_quit_button_hover->map = (uint32_t *) xpm_load((xpm_map_t) quit_hover_xpm, XPM_8_8_8_8, &img);
        sprite_quit_button_hover->height = img.height;
        sprite_quit_button_hover->width = img.width;
        menu->quit_hover = *sprite_quit_button_hover;

        free(sprite_quit_button_hover);
    }
    else {
        Sprite *pause_menu = (Sprite*) malloc(sizeof(Sprite));
        pause_menu->map = (uint32_t *) xpm_load((xpm_map_t) pause_menu_xpm, XPM_8_8_8_8, &img);
        pause_menu->height = img.height;
        pause_menu->width = img.width;
        menu->pause_menu = *pause_menu;

        free(pause_menu);

        if(menu->pause_menu.map==NULL){
            printf("pause menu is null\n");
            return NULL;
        }

        Sprite *sprite_resume = (Sprite*) malloc(sizeof(Sprite));
        sprite_resume->map = (uint32_t *) xpm_load((xpm_map_t) resume_xpm, XPM_8_8_8_8, &img);
        sprite_resume->height = img.height;
        sprite_resume->width = img.width;
        menu->resume = *sprite_resume;

        free(sprite_resume);

        Sprite *sprite_restart = (Sprite*) malloc(sizeof(Sprite));
        sprite_restart->map = (uint32_t *) xpm_load((xpm_map_t) restart_xpm, XPM_8_8_8_8, &img);
        sprite_restart->height = img.height;
        sprite_restart->width = img.width;
        menu->restart = *sprite_restart;

        free(sprite_restart);

        Sprite *sprite_quit_pause = (Sprite*) malloc(sizeof(Sprite));
        sprite_quit_pause->map = (uint32_t *) xpm_load((xpm_map_t) quit_pause_xpm, XPM_8_8_8_8, &img);
        sprite_quit_pause->height = img.height;
        sprite_quit_pause->width = img.width;
        menu->quit_pause = *sprite_quit_pause;

        free(sprite_quit_pause);

        Sprite *sprite_resume_hover = (Sprite*) malloc(sizeof(Sprite));
        sprite_resume_hover->map = (uint32_t *) xpm_load((xpm_map_t) resume_hover_xpm, XPM_8_8_8_8, &img);
        sprite_resume_hover->height = img.height;
        sprite_resume_hover->width = img.width;
        menu->resume_hover = *sprite_resume_hover;
        
        free(sprite_resume_hover);

        Sprite *sprite_restart_hover = (Sprite*) malloc(sizeof(Sprite));
        sprite_restart_hover->map = (uint32_t *) xpm_load((xpm_map_t) restart_hover_xpm, XPM_8_8_8_8, &img);
        sprite_restart_hover->height = img.height;
        sprite_restart_hover->width = img.width;
        menu->restart_hover = *sprite_restart_hover;

        free(sprite_restart_hover);

        Sprite *sprite_quit_pause_hover = (Sprite*) malloc(sizeof(Sprite));
        sprite_quit_pause_hover->map = (uint32_t *) xpm_load((xpm_map_t) quit_pause_hover_xpm, XPM_8_8_8_8, &img);
        sprite_quit_pause_hover->height = img.height;
        sprite_quit_pause_hover->width = img.width;
        menu->quit_pause_hover = *sprite_quit_pause_hover;

        free(sprite_quit_pause_hover);
    }
    return menu;
}

int (draw_field)(int x_offset, int y_offset, Sprite sprite ){
    uint32_t *map = sprite.map;
    if(map==NULL ){
        printf("map is null");
        return EXIT_FAILURE;
    }
    for(int i = 0; i < sprite.height; i++){
        for(int j = 0; j < sprite.width; j++){
            if(*map != TRANSPARENCY_COLOR && j+x_offset < MAX_X && i+y_offset < MAX_Y){
                if(vg_draw_color(j+x_offset,i+y_offset,*map)!=0){
                    return EXIT_FAILURE;
                }
            }
            map++;
            
        }
        
    }

    return EXIT_SUCCESS;
}

int clear_screen() {
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            if (vg_draw_color(x, y, 0x000000) != 0) {
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}

int (update_selected)(unsigned char code,Game_state* state, Menu* menu){
    if(code == ARROW_DOWN || code == ARROW_UP){
        if(menu->selected==2){
            menu->selected--;
        }
        else{
          menu->selected++;  
        }
    }
    if(code == A_KEY){
        switch (menu->selected)
        {
        case 1:
            *state=GAME;
            break;
        case 2:
            *state=QUIT;
            break;
        default:
            break;
        }
    }
    
    return EXIT_SUCCESS;
}

int (kbd_handler_menu)(Game_state* state, Menu* menu){
    update_selected(get_scancode(),state,menu);
    return EXIT_SUCCESS;
}

int (draw_menu)(Menu* menu){
    
    switch (menu->selected)
    {
        case 0:
            if(draw_field(260,10,menu->title)!=0){
                printf("draw title failed");
            }
            if(draw_field(467,350,menu->play_button)!=0){
                printf("draw start failed");
                return EXIT_FAILURE;
            }
            if(draw_field(492,475,menu->quit)!=0){
                printf("draw quit failed");
                return EXIT_FAILURE;
            }
            break;
        case 1:
            clear_screen();
            if(draw_field(260,10,menu->title)!=0){
                printf("draw title failed");
            }
            if(draw_field(461,345,menu->play_button_hover)!=0){
                return EXIT_FAILURE;
            }
            if(draw_field(492,475,menu->quit)!=0){
                return EXIT_FAILURE;
            }
            break;
        case 2:
            clear_screen();
            if(draw_field(260,10,menu->title)!=0){
                printf("draw title failed");
            }
            if(draw_field(467,350,menu->play_button)!=0){
                return EXIT_FAILURE;
            }
            if(draw_field(487,471,menu->quit_hover)!=0){
                return EXIT_FAILURE;
            }
            break;
        default:
            break;
    }

    return EXIT_SUCCESS;
}

int (time_handler_menu)(Menu* menu){
    if(draw_menu(menu)!=0){
        printf("menu failed to draw");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;   
}


int (choose_number_sprite)(uint8_t num, Sprite* sprite){
    xpm_image_t img;
    

    switch (num)
    {
    case 0:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r0_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;
    case 1:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r1_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;
    case 2:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r2_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;
    case 3:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r3_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;  
    case 4:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r4_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;
    case 5:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r5_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;  
    case 6:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r6_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;
    case 7:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r7_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break; 
    case 8:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r8_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break; 
    case 9:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) r9_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;  
    default:
        sprite->map=(uint32_t *) xpm_load((xpm_map_t) small_ball_xpm, XPM_8_8_8_8, &img);
        sprite->height=img.height;
        sprite->width=img.width;
        break;
    }
    return EXIT_SUCCESS;
}

int (draw_date)(uint8_t day, uint8_t month, uint8_t year){
    Sprite *sprite = (Sprite*) malloc(sizeof(Sprite));
    sprite->map=(uint32_t *) malloc(sizeof(char*));
    int x=730;
    int y=800;
    while(year){
        choose_number_sprite(year%10,sprite);
        if(draw_field(x,y,*sprite)!=0){
            return EXIT_FAILURE;
        }
        year /=10;
        x -= 50;
    }

    x -= sprite->width;
    choose_number_sprite(10,sprite);
    draw_field(x,y,*sprite);
    while(month){
        choose_number_sprite(month%10,sprite);
        if(draw_field(x,y,*sprite)!=0){
            return EXIT_FAILURE;
        }
        month /=10;
        x -= 50;
    }

    x -= sprite->width;
    choose_number_sprite(10,sprite);
    draw_field(x,y,*sprite);
    
    while(day){
        choose_number_sprite(day%10,sprite);
        if(draw_field(x,y,*sprite)!=0){
            return EXIT_FAILURE;
        }
        day /=10;
        x -= 50;
    }

    free(sprite);

    return EXIT_SUCCESS;
}




 

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

    mouse->x = MAX_X / 2;
    mouse->y = MAX_Y / 2;

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
    if(abs(dx) > 1 ){
        mouse->x += dx * 1.5;
    }
    if(abs(dy) > 1){
        mouse->y -= dy * 1.5;
    }

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
