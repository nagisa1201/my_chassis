/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-24 19:36:09
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-11-30 15:15:33
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\motor.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "motor.h"
#include "Encoder.h"
using namespace Motor;
Motor::MotorInterface_t motor(&htim8,TIM_CHANNEL_1);  
Motor::EncoderInterface_t encoder(&htim1,28,13,300,0.62/2,5); 

void MotorInterface_t::pidControlV(float Target_val)
{
    encoder.clockCntGet();
    encoder.CalculateSpeed();
    float actual_val = encoder._velocity;
    _output_velocity = this->_pid.pidIncrementalCalc(Target_val,actual_val);
    _output_pulse_v = _output_velocity / encoder._r / 2 / PI ;
}

void MotorInterface_t::Motor_start()
{   

    this->_dutyCycle_arr = _output_pulse_v / encoder._e_pulsev * _period_load;
    __HAL_TIM_SET_COMPARE(this->_htim, this->_Channel, this->_dutyCycle_arr);

}
