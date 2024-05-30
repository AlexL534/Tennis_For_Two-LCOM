#include "menu.h"
#include "color.h"
#include <stdlib.h>

Menu *menu;

Menu* (initialize_menu)(){
    Menu *menu = (Menu*)malloc(sizeof(Menu));
    if(menu == NULL){
        printf("Menu is null");
        return NULL;
    }
    menu->state=START_MENU;
    menu->selected=0;

    xpm_image_t img;
    Sprite *sprite_tiltle = (Sprite*) malloc(sizeof(Sprite));
    sprite_tiltle->map = (uint32_t *) malloc(sizeof(char*));
    sprite_tiltle ->map = (uint32_t *) xpm_load((xpm_map_t) title_xpm, XPM_8_8_8_8, &img);
    sprite_tiltle ->height = img.height;
    sprite_tiltle ->width = img.width;
    menu->title = *sprite_tiltle;

    free(sprite_tiltle);

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

int (update_selected)(unsigned char code){
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
            menu->state=GAME;
            break;
        case 2:
            menu->state=QUIT;
            break;
        default:
            break;
        }
    }
    
    return EXIT_SUCCESS;
}

int (kbdhandler)(){
    update_selected(get_scancode());
    return EXIT_SUCCESS;
}

int (draw_menu)(){
    
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

int (timehandler)(){
    if(draw_menu()!=0){
        printf("draw menu failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;   
}

Game_state (get_state)(){
    return menu->state;
}

int (menu_destroyer)(){
    free(menu->play_button.map);
    free(menu->quit.map);
    free(menu->play_button_hover.map);
    free(menu->quit_hover.map);
    free(menu->title.map);
    free(menu);
    menu=NULL;
    return EXIT_SUCCESS;
}

int (menu_loop)(){
    menu = initialize_menu();
    
    if(menu == NULL){
        printf("menu creation failed");
        return EXIT_FAILURE;
    }

    printf("menu created");

    int ipc_status;
    message msg;
    int r = 0;
    uint8_t bit_no;



    if(mouse_write_byte(MOUSE_EN_DATA_REP) != 0){
        menu_destroyer();
        return EXIT_FAILURE;
    }
    printf("mouse write byte");
    timer_set_frequency(0, 30);
    printf("set timer freq");
    if(kbd_subscribe_int(&bit_no) != 0){
        menu_destroyer();
        return EXIT_FAILURE;
    }
    printf("kbd subd");

    uint8_t kbc_mask = BIT(bit_no);

    if(timer_subscribe_int(&bit_no) != 0){
        menu_destroyer();
        return EXIT_FAILURE;
    }
    printf("timer subd");
    uint8_t timer_mask = BIT(bit_no);

    if(mouse_subscribe_int(&bit_no) != 0){
        menu_destroyer();
        return EXIT_FAILURE;
    }
    printf("mouse subd");
    uint8_t mouse_mask = BIT(bit_no);

    if(draw_menu()!=0){
        menu_destroyer();
        return EXIT_FAILURE;
    }
    printf("menu drawn");
    while (get_scancode() != KBD_ESC_BREAK && menu->state==START_MENU)
    {
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        }
        if(is_ipc_notify(ipc_status)){
            switch(_ENDPOINT_P(msg.m_source)){
                case HARDWARE:
                    if (msg.m_notify.interrupts & kbc_mask) { 
                       kbc_ih();
                       kbdhandler();
                    }
                    if(msg.m_notify.interrupts & timer_mask){
                        timer_int_handler();
                        if(timehandler()!=0){
                            menu_destroyer();
                            printf("time handler failed");
                            return EXIT_FAILURE;
                        }
                        swap_buffer();
                        
                    }
                    if(msg.m_notify.interrupts & mouse_mask){

                    }
                    break;
                default:
                    break;
            }
        }
    }

    if(kbd_unsubscribe_int() != 0){
        menu_destroyer();
        return EXIT_FAILURE;
    }

    if(timer_unsubscribe_int() != 0){
        menu_destroyer();
        return EXIT_FAILURE;
    }

    if(mouse_unsubscribe_int() != 0){
        menu_destroyer();
        return EXIT_FAILURE;
    }

    if(mouse_write_byte(MOUSE_DIS_DATA_REP) != 0){
        menu_destroyer();
        return EXIT_FAILURE;
    }

    menu_destroyer();

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
