
#include "riotee.h"
#include "riotee_gpio.h"
#include "riotee_timing.h"
#include "printf.h"
#include "riotee_uart.h"

static unsigned int counter = 0;

/* Executes after every reset */
void lateinit(void) {
  riotee_gpio_cfg_output(PIN_LED_CTRL);
  riotee_uart_init(PIN_D1, RIOTEE_UART_BAUDRATE_1000000);
  printf("reset\r\n");
}

/* Executes when capacitor voltage gets low */
void suspend(void) {
  riotee_gpio_clear(PIN_LED_CTRL);
  printf("suspend\r\n");
  printf("suspend 123\r\n");
}

/* Executes when capacitor voltage has recovered and after reset */
void resume(void) {
  riotee_gpio_set(PIN_LED_CTRL);
  printf("resume\r\n");
}

/* Executes once after programming the device */
void bootstrap(void) {
  printf("bootstrap\r\n");
}

int main(void) {
  riotee_gpio_set(PIN_LED_CTRL);
  printf("main start\r\n");
  for (;;) {
    riotee_sleep_ms(1000);
    printf("main loop %u\r\n", counter++);
  }
}
