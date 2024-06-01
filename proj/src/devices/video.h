#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <lcom/lcf.h>

/**
 *Inicializa o buffer da placa gráfica (vram) e inicializa o modo gráfico
 * @param Modo gráfico pretendido
 * @returns 1 se ocorrer um erro e 0 caso tenha corrido tudo bem
*/
int (map_VRAM)(uint16_t mode);

/**
 * Desenha uma linha horizontal no ecrã
 * @param x valor inicial de x
 * @param y valor inicial de y
 * @param len comprimento da linha
 * @param color cor da linha
 * @returns 1 se ocorrer um erro e 0 caso tenha corrido tudo bem
*/
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * Desenha um retângulo no ecrã
 * @param x valor inicial de x
 * @param y valor inicial de y
 * @param width comprimento do retângulo
 * @param height altura do retângulo
 * @param color cor do retângulo
 * @returns 1 se ocorrer um erro e 0 caso tenha corrido tudo bem
*/
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * Desenha a cor num dos pixeis do ecrã
 * @param x valor do x
 * @param y valor o y
 * @param color Cor que vamos desenha o pixel
 * @returns 1 se ocorrer um erro e 0 caso tenha corrido tudo bem
*/
int (vg_draw_color)(uint16_t x, uint16_t y, uint32_t color);

/**
 * Desenha um xpm no ecrã
 * @param xpm xpm a desenhar
 * @param type tipo de modo de imagem a usar
 * @param x valor inicial de x
 * @param y valor inicial de y
 * @returns 1 se ocorrer um erro e 0 caso tenha corrido tudo bem
*/
int (draw_xpm)(xpm_map_t xpm, enum xpm_image_type type, uint16_t x, uint16_t y);

/**
 * Retorna a informação do modo gráfico em uso para que possa ser usada em outros documentos
 * @returns informação do modo gráfico
*/
vbe_mode_info_t (get_mode_inf)();

/**
 * Retorna a altura máxima do modo gráfico em uso
 * @returns altura máxima do modo gráfico em uso
*/
unsigned (get_hres)();

/**
 * Retorna a largura máxima do modo gráfico em uso
 * @returns largura máxima do modo gráfico em uso
*/
unsigned (get_vres)();

/**
 * Retorna a quantidade de bits por pixel no modo gráfico em uso
 * @returns quantidade de bits por pixel no modo gráfico em uso
*/
unsigned (get_bits_per_pixel)();

/**
 * Retorna a quantidade de bytes por pixel no modo gráfico em uso
 * @returns quantidade de bytes por pixel no modo gráfico em uso
*/
unsigned (get_bytes_per_pixel)();

/**
 * Retorna o buffer da memória gráfica
 * @returns buffer da memória gráfica
*/
char* (get_video_mem)();

/**
 * Passa o conteúdo do segundo buffer para o buffer principal da memória gráfica
 * @returns conteúdo do segundo buffer para o buffer principal da memória gráfica
*/
void (swap_buffer)();

/**
 * Retorna o segundo buffer
 * @return segundo buffer
*/
char* (get_second_buffer)();

/**
 * Liberta a memória alocada para o segundo buffer
*/
void (free_second_buffer)();

/**
 * @brief limpa a tela
 * @return 1 se algum erro ocorrer se não 0
*/
int (clear_screen)();

#endif
