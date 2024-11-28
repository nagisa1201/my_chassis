#include "maincpp.h"

int main_cpp()
{
    Motor::MotorInterface_t motor;
    motor.MotorpinInit(&htim8, TIM_CHANNEL_1);
    Motor::Motor_speed_set motor1;
    motor1.Motor_speedset(1000);
    motor1.Motor_start();
    return 0;
}
