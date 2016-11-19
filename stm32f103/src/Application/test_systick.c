#include "stm32f10x.h"
#include "services_config.h"

__IO unsigned long long time = 0;

int main(void) {
  services_init();
  while(1) {
    time = micros();
  }
}
