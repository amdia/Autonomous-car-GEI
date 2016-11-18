#include "us_sensor.h"

#include "time_systick.h"
#include "sensor_IT.h"
#include "callback_functions.h"
#include "services_config.h" 

Sensor_IT_TypeDef structSensor_US_AVC;

uint64_t rise_time[ULTRASONIC_NB] = {0};

static void ultrasonic_trigger(void);
static void ultrasonic_untrigger(void);
static void ultrasonic_config_echo_pin(void);
static void ultrasonic_config_trig_pin(void);

__weak void ultrasonic_callback(Ultrasonic_Position pos){}
  
void ultrasonic_config_echo_pin(void){
	structSensor_US_AVC.pin = ULTRASONIC_AVC_ECHO_PIN;
	structSensor_US_AVC.port = ULTRASONIC_AVC_ECHO_PORT;
	structSensor_US_AVC.gpioSpeed = GPIO_SPEED;
	structSensor_US_AVC.gpioMode = GPIO_Mode_IPD;
	structSensor_US_AVC.triggerType = EXTI_Trigger_Rising_Falling;
	structSensor_US_AVC.priority = ULTRASONIC_PRIO;
  
	Sensor_IT_Config(&structSensor_US_AVC);
}

void ultrasonic_config_trig_pin(void){
	GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = ULTRASONIC_TRIG_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED;

  GPIO_Init(ULTRASONIC_TRIG_PORT, &GPIO_InitStructure);
}

void ultrasonic_config(void){
	ultrasonic_config_echo_pin();
	ultrasonic_config_trig_pin();
}

void ultrasonic_trig_all(void){
	uint64_t trigger_time = 0;
	ultrasonic_trigger();
	trigger_time = micros();
	while(micros() - trigger_time < ULTRASONIC_TRIGGER_DELAY){};
	ultrasonic_untrigger();
}

void ultrasonic_trigger(void){
	GPIO_WriteBit(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, Bit_SET);
}

void ultrasonic_untrigger(void){
	GPIO_WriteBit(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, Bit_RESET);
}

void ultrasonic_exti_callback (uint16_t GPIO_Pin){
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

 uint64_t ultrasonic_get_distance(Ultrasonic_Position pos){
  uint64_t ret = rise_time[pos] / ULTRASONIC_CONVERSION_CONSTANT;
  return ret;
}
