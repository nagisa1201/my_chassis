#include "maincpp.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"

Motor::MotorInterface_t motor(&htim8 , TIM_CHANNEL_1, &htim2 ,28, 13, 300, 0.62 / 2, 5);
char buffer[50]; 
void OnceMain();

int main_cpp()
{ 
    motor._encoder.EncoderpinInit();
    motor.MotorpinInit();
    return 0;
}

void OnceMain()
{
    motor.pidControlV(0.8);
    motor.Motor_start();
}
void SerialSend()
{

    sprintf(buffer," %f\n", motor._encoder._velocity);
    HAL_UART_Transmit(&huart4, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

}


