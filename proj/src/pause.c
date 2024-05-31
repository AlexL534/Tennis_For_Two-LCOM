#include "pause.h"
#include "color.h"
#include <stdlib.h>

Pause *pause;

Pause* (initialize_pause)(){
    Pause *pause = (Pause*)malloc(sizeof(Pause));
    if(pause == NULL){
        printf("Pause is null");
        return NULL;
    }
    pause->state=PAUSE_MENU;
    pause->selected=0;

    xpm_image_t img;
    Sprite *pause_menu = (Sprite*) malloc(sizeof(Sprite));
    pause_menu->map = (uint32_t *) malloc(sizeof(char*));
    pause_menu ->map = (uint32_t *) xpm_load((xpm_map_t) pause_menu_xpm, XPM_8_8_8_8, &img);
    pause_menu ->height = img.height;
    pause_menu ->width = img.width;
    pause->title = *pause_menu;

    free(pause_menu);

    if(pause->pause_menu.map==NULL){
        printf("pause menu is null");
        return NULL;
    }

    Sprite *sprite_resume = (Sprite*) malloc(sizeof(Sprite));
    sprite_resume->map = (uint32_t *) malloc(sizeof(char*));
    sprite_resume->map = (uint32_t *) xpm_load((xpm_map_t) resume_xpm, XPM_8_8_8_8, &img);
    sprite_resume->height = img.height;
    sprite_resume->width = img.width;
    pause->resume = *sprite_resume;

    free(sprite_resume);

    Sprite *sprite_restart = (Sprite*) malloc(sizeof(Sprite));
    sprite_restart->map = (uint32_t *) malloc(sizeof(char*));
    sprite_restart->map = (uint32_t *) xpm_load((xpm_map_t) restart_xpm, XPM_8_8_8_8, &img);
    sprite_restart->height = img.height;
    sprite_restart->width = img.width;
    pause->restart = *sprite_restart;

    free(sprite_restart);

    Sprite *sprite_quit_pause = (Sprite*) malloc(sizeof(Sprite));
    sprite_quit_pause->map = (uint32_t *) malloc(sizeof(char*));
    sprite_quit_pause->map = (uint32_t *) xpm_load((xpm_map_t) quit_pause_xpm, XPM_8_8_8_8, &img);
    sprite_quit_pause->height = img.height;
    sprite_quit_pause->width = img.width;
    pause->quit_pause = *sprite_quit_pause;

    free(sprite_quit_pause);

    Sprite *sprite_resume_hover = (Sprite*) malloc(sizeof(Sprite));
    sprite_resume_hover->map = (uint32_t *) malloc(sizeof(char*));
    sprite_resume_hover->map = (uint32_t *) xpm_load((xpm_map_t) resume_hover_xpm, XPM_8_8_8_8, &img);
    sprite_resume_hover->height = img.height;
    sprite_resume_hover->width = img.width;
    pause->resume_hover = *sprite_resume_hover;
    
    free(sprite_resume_hover);

    Sprite *sprite_restart_hover = (Sprite*) malloc(sizeof(Sprite));
    sprite_restart_hover->map = (uint32_t *) malloc(sizeof(char*));
    sprite_restart_hover->map = (uint32_t *) xpm_load((xpm_map_t) restart_hover_xpm, XPM_8_8_8_8, &img);
    sprite_restart_hover->height = img.height;
    sprite_restart_hover->width = img.width;
    pause->restart_hover = *sprite_restart_hover;

    free(sprite_restart_hover);

    Sprite *sprite_quit_pause_hover = (Sprite*) malloc(sizeof(Sprite));
    sprite_quit_pause_hover->map = (uint32_t *) malloc(sizeof(char*));
    sprite_quit_pause_hover->map = (uint32_t *) xpm_load((xpm_map_t) quit_pause_hover_xpm, XPM_8_8_8_8, &img);
    sprite_quit_pause_hover->height = img.height;
    sprite_quit_pause_hover->width = img.width;
    pause->quit_pause_hover = *sprite_quit_pause_hover;

    free(sprite_quit_pause_hover);

    return pause;


}

int (update_selected_pause)(unsigned char code){
    if(code == ARROW_DOWN || code == ARROW_UP){
        if(pause->selected==2){
            pause->selected--;
        }
        else{
          pause->selected++;  
        }
    }
    if(code == A_KEY){
        switch (pause->selected)
        {
        case 1:
            pause->state=GAME;
            break;
        case 2:
            pause->state=QUIT;
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

int (draw_pause)(){
    
    switch (pause->selected)
    {
        case 0:
            if(draw_field(260,10,pause->title)!=0){
                printf("draw title failed");
            }
            if(draw_field(467,350,pause->play_button)!=0){
                printf("draw start failed");
                return EXIT_FAILURE;
            }
            if(draw_field(492,475,pause->quit)!=0){
                printf("draw quit failed");
                return EXIT_FAILURE;
            }
            break;
        case 1:
            clear_screen();
            if(draw_field(260,10,pause->title)!=0){
                printf("draw title failed");
            }
            if(draw_field(461,345,pause->play_button_hover)!=0){
                return EXIT_FAILURE;
            }
            if(draw_field(492,475,pause->quit)!=0){
                return EXIT_FAILURE;
            }
            break;
        case 2:
            clear_screen();
            if(draw_field(260,10,pause->title)!=0){
                printf("draw title failed");
            }
            if(draw_field(467,350,pause->play_button)!=0){
                return EXIT_FAILURE;
            }
            if(draw_field(487,471,pause->quit_hover)!=0){
                return EXIT_FAILURE;
            }
            break;
        default:
        
            break;
    }

    return EXIT_SUCCESS;
}

int (timehandler)(){
    if(draw_pause()!=0){
        printf("draw pause failed");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;   
}

Game_state (get_state)(){
    return pause->state;
}

int (pause_destroyer)(){
    free(pause->play_button.map);
    free(pause->quit.map);
    free(pause->play_button_hover.map);
    free(pause->quit_hover.map);
    free(pause->title.map);
    free(pause);
    pause=NULL;
    return EXIT_SUCCESS;
}

int (pause_loop)(){
    pause = initialize_pause();
    
    if(pause == NULL){
        printf("pause creation failed");
        return EXIT_FAILURE;
    }

    printf("pause created");

    int ipc_status;
    message msg;
    int r = 0;
    uint8_t bit_no;



    if(mouse_write_byte(MOUSE_EN_DATA_REP) != 0){
        pause_destroyer();
        return EXIT_FAILURE;
    }
    printf("mouse write byte");
    timer_set_frequency(0, 30);
    printf("set timer freq");
    if(kbd_subscribe_int(&bit_no) != 0){
        pause_destroyer();
        return EXIT_FAILURE;
    }
    printf("kbd subd");

    uint8_t kbc_mask = BIT(bit_no);

    if(timer_subscribe_int(&bit_no) != 0){
        pause_destroyer();
        return EXIT_FAILURE;
    }
    printf("timer subd");
    uint8_t timer_mask = BIT(bit_no);

    if(mouse_subscribe_int(&bit_no) != 0){
        pause_destroyer();
        return EXIT_FAILURE;
    }
    printf("mouse subd");
    uint8_t mouse_mask = BIT(bit_no);

    if(draw_pause()!=0){
        pause_destroyer();
        return EXIT_FAILURE;
    }
    printf("pause drawn");
    while (get_scancode() != KBD_ESC_BREAK && pause->state==PAUSE_MENU_MENU)
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
                            pause_destroyer();
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
        pause_destroyer();
        return EXIT_FAILURE;
    }

    if(timer_unsubscribe_int() != 0){
        pause_destroyer();
        return EXIT_FAILURE;
    }

    if(mouse_unsubscribe_int() != 0){
        pause_destroyer();
        return EXIT_FAILURE;
    }

    if(mouse_write_byte(MOUSE_DIS_DATA_REP) != 0){
        pause_destroyer();
        return EXIT_FAILURE;
    }

    pause_destroyer();

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
