#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "rtc.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (proj_main_loop)(int argc, char **argv) {
  uint8_t day = 32; 
  uint8_t month = 13;
  uint8_t year = 100;

  if(get_date(&day, &month, &year) != 0){
    return EXIT_FAILURE;
  }
  
  printf("Day = %d\n", day);
  printf("Month = %d\n", month);
  printf("Year = %d\n", year);

  return 0;
}
