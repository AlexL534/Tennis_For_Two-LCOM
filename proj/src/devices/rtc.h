#ifndef RTC_H
#define RTC_H

#include <lcom/lcf.h>

#define  RTC_ADDR_REG 0x70
#define  RTC_DATA_REG 0x71 

#define DAY 7
#define MONTH 8
#define YEAR 9

#define REG_A 10
#define REG_A_UIP BIT(7)

#define REG_B 11
#define REG_B_DM BIT(2)

int (get_date)(uint8_t *day, uint8_t *month, uint8_t *year);
int (set_binary)();
int (read_RTC)(uint8_t command, uint8_t *output);

#endif
