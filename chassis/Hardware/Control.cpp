/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-03 16:08:21
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-14 15:05:54
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\Control.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "Control.h"

using namespace Control;

// template<typename Static>
void Control_t::setTarget(vel_t target_car_vel)
{
    switch(_mode)
    {
        case HalfCloseLoop:
        _kinematic._target_xyw = target_car_vel;
        _kinematic.inverseCalbody();
        _motors._static[0].setSpeed(_kinematic._linear_vel_target[0]);
        _motors._static[1].setSpeed(_kinematic._linear_vel_target[1]);
        _motors._static[2].setSpeed(_kinematic._linear_vel_target[2]);
        _motors._static[3].setSpeed(_kinematic._linear_vel_target[3]);
        break;
    }
}

void Control_t::initMotor()
{
    _motors._static[0].initMotor();
    _motors._static[1].initMotor();
    _motors._static[2].initMotor();
    _motors._static[3].initMotor();
}


void Control_t::controlLoop()
{
    switch(_mode)
    {
        case HalfCloseLoop:
        _motors._static[0].update();
        _motors._static[1].update();
        _motors._static[2].update();
        _motors._static[3].update();
        _kinematic.updateCurrentvel<float>(_motors._static[0]._linear_vel_raw, _motors._static[1]._linear_vel_raw,
        _motors._static[2]._linear_vel_raw, _motors._static[3]._linear_vel_raw);
        _kinematic.forwardCalbody();
        break;
    }
}
#if DEBUG
void Control_t::debugSingleMotor()
{
    _motors._static[0].setSpeed(debug_target_group[0]);
    _motors._static[1].setSpeed(debug_target_group[1]);
    _motors._static[2].setSpeed(debug_target_group[2]);
    _motors._static[3].setSpeed(debug_target_group[3]);
}

#endif
