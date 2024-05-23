#ifndef KBD_H
#define KBD_H
#include <lcom/lcf.h>

/**
 * Lê o estado do KBC para verificar se já podemos efetuar a leitura do scancode
 * @param status status of the KBC
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (kbd_read_status)(uint8_t *status);

/**
 * Lê um scancode enviado pelo teclado no KBC
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (kbd_read_scancode)();

/**
 * Inicia as interrupções para o keyboard
 * @param bit_no Valor inicial do hook_id
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (kbd_subscribe_int)(uint8_t *bit_no);

/**
 * Desativa as interrupções para o keyboard
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (kbd_unsubscribe_int)();

/**
 * Usado para obter o valor do scancode em outros documentos
 * @returns Valor do scancode
*/
uint8_t (get_scancode)();

/**
 * Usado para obter o valor do hook id em outros documentos
 * @returns Valor do hook_id
*/
int (get_KBD_hook_id)();

#endif
