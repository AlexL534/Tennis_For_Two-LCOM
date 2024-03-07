#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>


/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the KBC
 */

/* I/O port adresses*/
#define IRQ_KEYBOARD 1

#define KBC_OUT_BUF   0x60    /*Out buffer (to read scancodes from the keyboard and return values)*/
#define KBC_ST_REG    0x64    /*Used to read the KBC state*/
#define KBC_CMD_REG   0x64    /*Used to send commands to the KBC*/

/* Status Register */

#define KBC_PARITY    BIT(7)  /*Parity error - invalid data*/
#define KBC_TIMEOUT   BIT(6)  /*Timeout error - invalid data*/
#define KBC_AUX       BIT(5)  /*Mouse data*/
#define KBC_INH       BIT(4)  /*Inhibit flag: 0 if keyboard is inhibited*/
#define KBC_A2        BIT(3)  /*A2 input line: irrelevant for LCOM*/
#define KBC_SYS       BIT(2)  /*System flag: irrelevant for LCOM*/
#define KBC_IBF       BIT(1)  /*Input buffer full dont write commands or arguments*/
#define KBC_OBF       BIT(0)  /*Output buffer full - data available for reading*/

/* KBC Commands */

#define KBC_RD_CM_B   0x20    /*Read Command Byte*/
#define KBC_WRT_CM_B  0x60    /*Write Command Byte*/
#define KBC_CHECK     0xAA    /*Check KBC (Self-test)*/
#define KDB_KB_INTER  0xAB    /*Check Keyboard Interface*/
#define KDB_DISABLE_INTER   0xAD  /*Disable KBD Interface*/
#define KDB_ENABLE_INTER    0xAE  /*Enable KBD Interface*/


#define KBD_ESC_BREAK   0x81     /*ESC breakcode*/

#define KBD_BREAKCODE   BIT(7)
#define KBD_MAKECODE    0x00

#define KBD_TWOBYTES    0xE0

#define DELAY_US    20000





#endif
