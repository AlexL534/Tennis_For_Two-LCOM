#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <lcom/lcf.h>

/**
 * Desenha e inicializa o background do jogo
 * @param background Buffer com o conteúdo do background
 * @returns 1 se ocorreu algum erro e 0 se correu tudo bem
*/
int (drawBackground)(uint32_t *background);

/**
 * Refresca o background para criar um novo frame apagando os conteúdos que se encontravam antes no buffer da gráfica
 * @param background Buffer com o conteúdo do background
 * @returns 1 se ocorreu algum erro e 0 se correu tudo bem
*/
int (refreshBackground)(uint32_t *background);

#endif
