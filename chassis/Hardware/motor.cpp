/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-24 19:36:09
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-01 00:05:55
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\motor.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "motor.h"
using namespace Motor;

#if USE_COMMON_Motor
void Motorcommon_t::setSpeed(float target)
{
    _vel_target = target * _Factor * _forward / (_WheelDiameter);
    _pid.targetUpdate(_vel_target);
}
float Motorcommon_t::getLinearspeed()
{
    return _vel_raw.data_float * (_WheelDiameter) / (_Factor * _forward);
}
// void Motorcommon_t::update(void *param)
// {
//     // 获得编码器的值
//     uint16_t dt = *(uint16_t*)(param);//此处void *解模板化，变为uint16_t之后解引用
//     _encoder.clockCntGet();
//     _vel_raw.data_float = _encoder._pulse_count / dt;
//     // 更新速度
//     int pwm = _pid.pidCalc((int16_t)_vel_raw.data_float);
//     pwm_out(pwm);
// }
void Motorcommon_t::update()
{
    // 获得编码器的值
    float dt = 0.005;//此处void *解模板化，变为uint16_t之后解引用
    _encoder.clockCntGet();
    _vel_raw.data_float = _encoder._pulse_count / dt;
    // 更新速度
    int pwm = _pid.pidCalc((int16_t)_vel_raw.data_float);
    pwm_out(pwm);
}
void Motorcommon_t::pwm_out(int pwm)
{
    int out_speed = pwm;
    if (out_speed > 0)
    {
        HAL_GPIO_WritePin(_PH_Port, _PH1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(_PH_Port, _PH2_Pin, GPIO_PIN_RESET);
        __HAL_TIM_SetCompare(_htim, _channel, out_speed);
    }
    else
    {
        HAL_GPIO_WritePin(_PH_Port, _PH1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(_PH_Port, _PH2_Pin, GPIO_PIN_SET);
        __HAL_TIM_SetCompare(_htim, _channel, -out_speed);
    }
}
#endif