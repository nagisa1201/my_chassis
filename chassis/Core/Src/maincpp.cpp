#include "maincpp.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
extern Motor::MotorInterface_t motor;  
extern Motor::EncoderInterface_t encoder;
char buffer[50]; 
void OnceMain();

int main_cpp()
{ 
    encoder.EncoderpinInit();
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

    sprintf(buffer," %f\n", encoder._velocity);
    HAL_UART_Transmit(&huart4, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);

}


