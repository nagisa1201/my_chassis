/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-09 15:31:14
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-11-30 17:26:34
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
#include "Encoder.h"
class EncoderInterface_t; 

namespace Motor
{   
    class Motor_base_t
    {
        public:
            ~Motor_base_t(){};
            // 构造函数初始化TIM和通道
            Motor_base_t(TIM_HandleTypeDef *htimx, uint32_t Channelx)
            {
                _htim = htimx;
                _Channel = Channelx;
                _period_load = _htim->Init.Period;
            }

            void MotorpinInit()
            {
                HAL_TIM_PWM_Start(_htim, _Channel);
            }
            
        protected:
            TIM_HandleTypeDef *_htim;  // 定时器句柄
            uint32_t _Channel;         // 定时器通道
            uint16_t _period_load;     // pwm的定时器的自动重装载值

    };

    class MotorInterface_t :public Motor_base_t
    {
        public:
            ~MotorInterface_t(){};

             MotorInterface_t(TIM_HandleTypeDef *htimx_pwm, uint32_t Channelx,TIM_HandleTypeDef *htimx_encoder, float reduction_ratio,
            float encoder_ppr, float e_rpm, float r, float reload_ms): Motor_base_t(htimx_pwm, Channelx), 
          _encoder(htimx_encoder, reduction_ratio, encoder_ppr, e_rpm, r, reload_ms) {}

            void pidControlV(float Target_val);
            void Motor_start();

            float _output_velocity; 
            int32_t _output_pulse_v;
            EncoderInterface_t _encoder;
        protected:
            
            Pid_Incremental_template_t<float, float> _pid = Pid_Incremental_template_t<float, float>({5, 2, 0, -5000, 5000, 2000});
            float _target_val;
            

            uint16_t _dutyCycle_arr;
    };

}

#endif
