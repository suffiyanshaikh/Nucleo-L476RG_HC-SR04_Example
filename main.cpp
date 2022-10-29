
/* USER CODE BEGIN Header */
/** Nucleo-L476RG_HC-SR04 Sensor Example
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Suffiyan Shaikh.
  * All rights reserved.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Private includes ----------------------------------------------------------*/
#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <ctime>

/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define Timeout 200 //ms
#define Threshhold 30 //cm

/* Private variables ---------------------------------------------------------*/
RawSerial pc(USBTX, USBRX,9600); // tx, rx
DigitalOut Trigger(PA_6,0); //DA_12 //PA_6
InterruptIn Echo(PA_7); //D11 //PA_7
DigitalOut debug_led(LED1);

Timer pulse_timer;
Timer echo_timer;

/* Global variables ---------------------------------------------------------*/
uint64_t start=0;
uint64_t stop=0;
int correction;
uint64_t trigger_time;
float object_distance;
bool echo_flag=0;



/* Private function prototypes -----------------------------------------------*/
void rise();
void fall();

// main() runs in its own thread in the OS
int main()
{

    /* Initialize all configured peripherals */
    
        
        Echo.rise(&rise);  // attach the address of the flip function to the rising edge
        Echo.fall(&fall);  // attach the address of the flip function to the rising edge

    /*  measure actual software polling timer delays
        delay used later in time correction */
        echo_timer.reset();

        // start timer
        echo_timer.start();

        // min software polling delay to read echo pin
        while (Echo==2) {};

        // stop timer
        echo_timer.stop();

        // read timer
        correction = echo_timer.read_us();
        printf("Approximate software overhead timer delay is %d uS\n\r",correction);

        pulse_timer.start();
        trigger_time=pulse_timer.read_ms();

    /*  CODE BEGIN WHILE */

    while (true) {

        if((pulse_timer.read_ms()-trigger_time)>=Timeout)
        {
            trigger_time=pulse_timer.read_ms();
            if(echo_flag==0)
            {
               printf("New Trigger Generated\n");
                Trigger.write(1);
                wait_us(10);
                Trigger.write(0);

            }
        }

        if(object_distance <= Threshhold && object_distance != 0)
        {
            printf("Object Detected,Distance from Object :%0.2f cm \n ",object_distance);
        }
        else{
            printf("No Object in Range\n");
        }
    }
}

void rise(){

echo_flag=1;
while (Echo.read()==0) {};
echo_timer.start();
debug_led=1;

}

void fall(){

echo_flag=0;
while (Echo.read()==1) {};
echo_timer.stop();
debug_led=0;
object_distance=((echo_timer.read_us()-correction)/58.0);
echo_timer.reset();

}
