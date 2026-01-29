#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp32/rom/ets_sys.h>
#include "driver/gpio.h"

#define in1 GPIO_NUM_21
#define in2 GPIO_NUM_32
#define in3 GPIO_NUM_22
#define in4 GPIO_NUM_33

#define boton_horario	GPIO_NUM_4
#define boton_antihorario GPIO_NUM_2

#define min_paso 5
#define delay 500
#define velocidad_motor 2000

void giro_horario();
void giro_antihorario();
void desplaza_horario(int desplazamiento);
void desplaza_antihorario(int desplazamiento);


void app_main(void)
{
	gpio_set_direction(in1, GPIO_MODE_OUTPUT);
	gpio_set_direction(in2, GPIO_MODE_OUTPUT);
	gpio_set_direction(in3, GPIO_MODE_OUTPUT);
	gpio_set_direction(in4, GPIO_MODE_OUTPUT);
	gpio_set_direction(boton_horario, GPIO_MODE_INPUT);
	gpio_set_direction(boton_antihorario, GPIO_MODE_INPUT);
	
	int val_boton = 0;
	int val_boton2 = 0;
 // xTaskCreate(ultrasonic_test, "ultrasonictest", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
	while(1){
		//printf("Hello world!\n");
		val_boton = gpio_get_level(boton_horario);
		//printf("Estado boton %d\n",val_boton);
		if(val_boton == 1){
			desplaza_horario(5);
		}else{
			val_boton2 = gpio_get_level(boton_antihorario);
			//printf("Estado boton_antihorario %d\n",val_boton2);
			if(val_boton2 == 1){
				desplaza_antihorario(5);
			}
		}
		
		
		vTaskDelay(delay/portTICK_PERIOD_MS);
	}
}
void desplaza_antihorario(int desplazamiento){
	for(int i=0; i<desplazamiento; i++){
		giro_antihorario();
	}
}
void desplaza_horario(int desplazamiento){
	for(int i=0; i<desplazamiento; i++){
		giro_horario();
	}
}
void giro_horario(void)
{
	gpio_set_level(in1,1);
	gpio_set_level(in2,0);
	gpio_set_level(in3,0);
	gpio_set_level(in4,0);
	ets_delay_us(velocidad_motor);
	gpio_set_level(in1,0);
	gpio_set_level(in2,1);
	gpio_set_level(in3,0);
	gpio_set_level(in4,0);
	ets_delay_us(velocidad_motor);
	gpio_set_level(in1,0);
	gpio_set_level(in2,0);
	gpio_set_level(in3,1);
	gpio_set_level(in4,0);
	ets_delay_us(velocidad_motor);
	gpio_set_level(in1,0);
	gpio_set_level(in2,0);
	gpio_set_level(in3,0);
	gpio_set_level(in4,1);
	ets_delay_us(velocidad_motor);
}
void giro_antihorario(){
	gpio_set_level(in4,1);
	gpio_set_level(in3,0);
	gpio_set_level(in2,0);
	gpio_set_level(in1,0);
	ets_delay_us(velocidad_motor);
	gpio_set_level(in4,0);
	gpio_set_level(in3,1);
	gpio_set_level(in2,0);
	gpio_set_level(in1,0);
	ets_delay_us(velocidad_motor);

	gpio_set_level(in4,0);
	gpio_set_level(in3,0);
	gpio_set_level(in2,1);
	gpio_set_level(in1,0);
	ets_delay_us(velocidad_motor);
	gpio_set_level(in4,0);
	gpio_set_level(in3,0);
	gpio_set_level(in2,0);
	gpio_set_level(in1,1);
	ets_delay_us(velocidad_motor);
}