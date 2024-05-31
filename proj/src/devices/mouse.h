#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <lcom/lcf.h>

/**
 * Ativa as interrupções para o mouse.
 * @param bit_no Valor inicial do hook_id
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (mouse_subscribe_int)(uint8_t *bit_no);

/**
 * Desativa as interrupções para o rato.
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (mouse_unsubscribe_int)();

/**
 * Lê o status atual do KBC para verificar se podemos ler os valores correspondentes ao mouse.
 * @param status Valor do status que é lido
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (mouse_read_status)(uint8_t *status);

/**
 * Lê um byte proveniente do mouse
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (mouse_read_byte)();

/**
 * Escreve um byte/comando para o mouse
 * @param command Comando/Byte que quermos mandar para o mouse
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (mouse_write_byte)(uint8_t command);

/**
 * Escreve um comando no porto selecionada.
 * @param command  Comando/Byte que quermos mandar para o mouse
 * @param port Porto onde vamos escrever o comando/byte
 * @returns 1 se ocorreu um erro. 0 se correu tudo bem
*/
int (mouse_write_command)(uint8_t command, int port);

/**
 * Trata das interrupções que são recebidas relativas ao mouse
*/
void (mouse_ih)();

/**
 * Insere um byte lido do mouse num array
*/
void (mouse_insert_byte)();

/**
 * Insere os valores do array de bytes do mouse num mouse packet
*/
void (mouse_insert_in_packet)();

/**
 * Converte os valores do byte para 2's complement no caso de este ser negativo
 * @param mouse_byte valor que queremos converter
 * @returns Valor convertido
*/
uint16_t (convert_to_2sComplement)(uint8_t mouse_byte);

/**
 * Obtém o hook_id para ser usado em outros documentos
 * @returns Valor do hook_id
*/
int (get_mouse_hook_id)();

/**
 * Obtém o indice do byte atual para que possa ser acedido em outros documentos
 * @returns Valor do indice do byte atual
*/
uint8_t (get__mouse_byte_index)();

/**
 * Obtém o valor do byte atual (último lido) para que possa ser usado em outros documentos
 * @returns Valor do byte atual (último lido)
*/
uint8_t (get_current_byte)();

/**
 * Obtém o mouse packet para que possa ser usado em outros documentos
 * @returns Valor do mouse packet
*/
struct packet (get_mouse_packet)();

/**
 * Reseta (colcoca a zero) o valor do indice do byte atual
*/
void (reset_byte_index)();

#endif
