/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-24 19:36:09
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-12-02 16:24:38
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\motor.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "motor.h"
#include "Encoder.h"
#include "common.h"
using namespace Motor;


void MotorInterface_t::pidControlV(float Target_val)
{
    _encoder.clockCntGet();
    _encoder.CalculateSpeed();
    float actual_val = _encoder._pulse_count;
    _output_pulse_count = this->_pid.pidCalc(Target_val,actual_val);
    /*
        编码器算出真实速度，target不变，放到pid中，其中的output变了，得到输出速度，再转化为脉冲速度
    */
}

void MotorInterface_t::Motor_start()
{   
    this->_actual_proportion = _output_pulse_count / _encoder._full_CNT;
    if(_actual_proportion > 0)
    {
        HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);

    }
    else
    {
        HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);
        _actual_proportion = -_actual_proportion;
    }  
    this->_dutyCycle_arr = _actual_proportion * _period_load;
    __HAL_TIM_SET_COMPARE(this->_htim, this->_Channel, this->_dutyCycle_arr);


}
