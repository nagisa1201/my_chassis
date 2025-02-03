/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-02 21:54:00
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-03 22:43:08
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\Kinematic.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "Kinematic.h"

using namespace Kinematic;

/**
 * @brief 
 * 左上1右上0
 * 左下2右下3   从车身目标速度到轮子目标速度的逆向解算
 */
template<size_t number>
void Kinematic_t<number>::inverseCalbody()
{
    switch (_wheel)
    {
    case O_shape:
        _linear_vel_target[0] = _target_xyw.vy - _target_xyw.vx + _target_xyw.w * (_track_length + _track_width);
        _linear_vel_target[1] = _target_xyw.vy + _target_xyw.vx - _target_xyw.w * (_track_length + _track_width);
        _linear_vel_target[2] = _target_xyw.vy - _target_xyw.vx - _target_xyw.w * (_track_length + _track_width);
        _linear_vel_target[3] = _target_xyw.vy + _target_xyw.vx + _target_xyw.w * (_track_length + _track_width);
        break;
    case X_shape:
        _linear_vel_target[0] = _target_xyw.vx + _target_xyw.vy + _target_xyw.w * (_track_length + _track_width);
        _linear_vel_target[1] = _target_xyw.vx - _target_xyw.vy - _target_xyw.w * (_track_length + _track_width);
        _linear_vel_target[2] = _target_xyw.vx + _target_xyw.vy - _target_xyw.w * (_track_length + _track_width);
        _linear_vel_target[3] = _target_xyw.vx - _target_xyw.vy + _target_xyw.w * (_track_length + _track_width);
        break;
    default:
        break;
    }
} 
/**
 * @brief 
 * 从轮子实际速度到车身实际速度
 */
template<size_t number>
void Kinematic_t<number>::forwardCalbody()
{
    float v0 = _linear_vel_raw[0];
    float v1 = _linear_vel_raw[1];
    float v2 = _linear_vel_raw[2];
    float v3 = _linear_vel_raw[3];
    switch (_wheel)
    {
        case O_shape:
            _current_xyw.vx = (v1 - v0 + v3 - v2) / 4.0;
            _current_xyw.vy = (v0 + v1 + v2 + v3) / 4.0;
            _current_xyw.w = (v0 - v1 - v2 + v3) / (4.0 * (_track_length + _track_width));
            break;
        case X_shape:
            _current_xyw.vx = (v0 + v1 + v2 + v3) / 4.0;               // X轴方向速度
            _current_xyw.vy = (v0 + v1 - v2 - v3) / 4.0;              // Y轴方向速度
            _current_xyw.w = (v0 - v1 - v2 + v3) / (4.0 * (_track_length + _track_width)); // 角速度
            break;
    }
}

template<size_t number>
template<typename T,typename... Args>
void Kinematic_t<number>::updateTargetvel(Args&&... args)
{
    // 使用initializer_list来接收可变参数
        std::initializer_list<T> values = {std::forward<Args>(args)...};
        
        size_t index = 0;
        for (const T& val : values) 
        {
            _linear_vel_target[index++] = val;
        }
    
}

