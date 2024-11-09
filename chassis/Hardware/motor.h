/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-09 15:31:14
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-11-09 21:14:09
 * @FilePath: \MDK-ARMf:\project\cubemax\chassis\Hardware\motor.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/**
 * @file motor.cpp
 * @author nagisa (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __MOTOR_H
#define __MOTOR_H
#include "common.h"
#include "pid.h"
namespace Motor
{
    class MotorInterface_t
    {
        public:
            // 构造函数初始化TIM和通道
            void MotorpinInit(TIM_HandleTypeDef *htimx, uint32_t Channelx)
            {
                _htim = htimx;
                _Channel = Channelx;
            }


        protected:
            TIM_HandleTypeDef *_htim;  // 定时器句柄
            uint32_t _Channel;         // 定时器通道
            uint16_t _period_load;     // 定时器的自动重装载值
            uint16_t _compare_arr;     // 定时器的比较值
    };

    class Motor_speed_set :public MotorInterface_t
    {
        public:
     // 设置电机速度
            int Motor_speedset(float pulse)
            {
                // 获取定时器的自动重载值
                _period_load = _htim->Init.Period;

                // 计算比较值
                _compare_arr = (int16_t)(pulse * 100 / 10000 * _period_load); // 转换为16位整数

                return _compare_arr;
            }

            // 启动电机并设置占空比
            void Motor_start()
            {
                HAL_TIM_PWM_Start(_htim, _Channel); // 启动PWM
                __HAL_TIM_SET_COMPARE(_htim, _Channel, _compare_arr); // 设置比较值
            }
    };


    class Motor_speed_control :public Motor_speed_set
    {
        public:
            // 电机速度控制
            void Motor_speedcontrol(float target_speed, float current_speed)
            {
                // 速度PID
                pid_base_template_t<float, float> speed_pid(5, 2, 0, 0, 1000);
                // 设置目标速度
                speed_pid.target_ = target_speed;
                // 计算PID
                float output = speed_pid.cal(target_speed, current_speed);
                // 设置电机速度
                Motor_speedset(output);
            }
    };

}

#endif
