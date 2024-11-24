#include "maincpp.h"

int main_cpp()
{
    Motor::MotorInterface_t motor;
    Motor::EncoderInterface_t encoder;
    encoder.EncoderInit(&htim1);
    motor.MotorpinInit(&htim8, TIM_CHANNEL_1);
    //motor.Motor_speed_set(50);
    motor.Motor_start();

		return 0;
}
