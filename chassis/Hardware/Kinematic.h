/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-02 21:53:47
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-04 11:42:28
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\Kinematic.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __KINEMATIC_H
#define __KINEMATIC_H

#define USE_MECANUM_WHEEL 1
#include "stdint.h"
#include "math.h"
#include "motor.h"
#include "Lib_Static.h"
#include "main.h"

#define PI 3.1415926

struct vel_t
{
    float vx;
    float vy;
    float w;
};
namespace Kinematic
{

    enum wheelclass_t
    {
        O_shape,
        X_shape
    };
    /**
     * @brief 
     * 运动学类，切记模板类可以声明定义分离，但一定要加上模板类的那个模板参数，此处表现为template<size_t number>
     * @tparam number 
     */
    template<size_t number>
    class Kinematic_t
    {
        public:
            Kinematic_t(wheelclass_t wheelclass,float track_width,float track_length)
            {
                _target_xyw={0,0,0};
                _current_xyw={0,0,0};
                _wheel=wheelclass;
                _track_width=track_width;
                _track_length=track_length;
            }
            
            void inverseCalbody();//从车身目标速度到轮子目标速度
            void forwardCalbody();//从轮子实际速度到车身实际速度
            
            template<typename Static, typename... Args>
            void updateTargetvel(Args&&... args);

            template<typename Static, typename... Args>
            void updateCurrentvel(Args&&... args);
            

            float _linear_vel_target[number];
            float _linear_vel_raw[number];

            vel_t _target_xyw;
            vel_t _current_xyw;
        private:        
            wheelclass_t _wheel;
            float _track_width;
            float _track_length;
            // Static::Static_t<Motor::Motorcommon_t, 4> motors;
    };
    /**
     * @brief 
     * 左上1右上0
     * 左下2右下3   从车身目标速度到轮子目标速度的逆向解算
     */
    #if USE_MECANUM_WHEEL
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
    /**
     * @brief 
     * 弃用
     * @tparam number 
     * @tparam Static 
     * @tparam Args 
     * @param args 
     */
    template<size_t number>
    template<typename Static,typename... Args>
    void Kinematic_t<number>::updateTargetvel(Args&&... args)
    {
        // 使用initializer_list来接收可变参数
            std::initializer_list<Static> values = {std::forward<Args>(args)...};
            
            size_t index = 0;
            for (const Static& val : values) 
            {
                _linear_vel_target[index++] = val;
            }
        
    }

    /**
     * @brief 
     * 将各个电机的线速度更新到运动学类中
     * @tparam number 
     * @tparam Static 
     * @tparam Args 
     * @param args 
     */
    template<size_t number>
    template<typename Static,typename... Args>
    void Kinematic_t<number>::updateCurrentvel(Args&&... args)
    {
        // 使用initializer_list来接收可变参数
            std::initializer_list<Static> values = {std::forward<Args>(args)...};
            
            size_t index = 0;
            for (const Static& val : values) 
            {
                _linear_vel_raw[index++] = val;
            }
        
    }

#endif
}
#endif