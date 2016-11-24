#include "drivers_car_config.h"
#include "us_sensor.h"

float ultrasonic_distance_cm[ULTRASONIC_NB] = {0.0};

int main(void) {
	services_init();
	while(1){
    ultrasonic_distance_cm[ULTRASONIC_AVC] = ultrasonic_get_distance(ULTRASONIC_AVC);
	}
  return 0;
}
