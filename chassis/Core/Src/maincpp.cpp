#include "maincpp.h"

int main_cpp()
{
    Motor::MotorInterface_t motor;
    motor.MotorpinInit(&htim8, TIM_CHANNEL_1);
    motor.Motor_speed_set(50);
    motor.Motor_start();

		return 0;
}
