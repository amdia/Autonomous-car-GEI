#include "us_sensor.h"

#include "time_systick.h"
#include "sensor_IT.h"
#include "callback_functions.h"
#include "services_config.h"

// macros, lazy way configure echo pins
#define CONFIG_ECHO_PINS(name)  \
  do { \
    ultrasonic_##name.pin = ULTRASONIC_##name##_ECHO_PIN;  \
    ultrasonic_##name.port = ULTRASONIC_##name##_ECHO_PORT;  \
    ultrasonic_##name.gpioSpeed = GPIO_SPEED;  \
    ultrasonic_##name.gpioMode = GPIO_Mode_IPU;  \
    ultrasonic_##name.triggerType = EXTI_Trigger_Rising_Falling; \
    ultrasonic_##name.priority = ULTRASONIC_PRIO;  \
    Sensor_IT_Config(&ultrasonic_##name);  \
  } while(0) \

// ---------------------------- //
// ----- Private section ------ //
// ---------------------------- //
  
// declaration of 6 ultrasonic echo pins
static Sensor_IT_TypeDef ultrasonic_AVC;
static Sensor_IT_TypeDef ultrasonic_AVG;
static Sensor_IT_TypeDef ultrasonic_AVD;
static Sensor_IT_TypeDef ultrasonic_ARC;
static Sensor_IT_TypeDef ultrasonic_ARG;
static Sensor_IT_TypeDef ultrasonic_ARD;

// private variable storing rise time of each echo signal
static uint64_t rise_time[ULTRASONIC_NB] = {0};

// private functions which set and reset trig pin
static void ultrasonic_trigger(void);
static void ultrasonic_untrigger(void);

// overloadable callback function, reserved for user
__weak void ultrasonic_callback(Ultrasonic_Position pos) {}

void init_ultrasonic_sensors(void) {
  // configure 6 echo pins as input with EXTI
	CONFIG_ECHO_PINS(AVC);
  CONFIG_ECHO_PINS(AVG);
  CONFIG_ECHO_PINS(AVD);
  CONFIG_ECHO_PINS(ARC);
  CONFIG_ECHO_PINS(ARG);
  CONFIG_ECHO_PINS(ARD);
  
  // configure trig pin as output push-pull
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = ULTRASONIC_TRIG_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED;
  GPIO_Init(ULTRASONIC_TRIG_PORT, &GPIO_InitStructure);
}

void ultrasonic_trig_all(void) {
	uint64_t trigger_time = 0;
	ultrasonic_trigger();
	trigger_time = micros();
	while(micros() - trigger_time < ULTRASONIC_TRIGGER_DELAY){};
	ultrasonic_untrigger();
}

void ultrasonic_trigger(void) {
	GPIO_WriteBit(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, Bit_SET);
}

void ultrasonic_untrigger(void) {
	GPIO_WriteBit(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, Bit_RESET);
}

void ultrasonic_exti_callback (uint16_t GPIO_Pin) {
  static uint64_t time_tmp[ULTRASONIC_NB] = {0};
  static Ultrasonic_State state[ULTRASONIC_NB] = {DOWN};
	Ultrasonic_Position position = get_ultrasonic_position(GPIO_Pin);
	if(state[position] == DOWN) {
		state[position] = UP;
		time_tmp[position] = micros();
	} else {
		state[position] = DOWN;
		rise_time[position] = micros() - time_tmp[position];
		ultrasonic_callback(position);
	}
}

uint64_t ultrasonic_get_distance(Ultrasonic_Position pos) {
  return rise_time[pos] / ULTRASONIC_CONVERSION_CONSTANT;
}
