/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-09 15:31:14
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-01 00:07:06
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
#define USE_COMMON_Motor 1       
#include "main.h"
#include "pid.h"
#include "Encoder.h"
class EncoderInterface_t; 

namespace Motor
{   
    union data_t
    {
        uint8_t data_raw[4];
        float data_float;
        int32_t data_int;
        // int16_t data_int16;
    };
    class MotorBase_t
    {
        public:
            MotorBase_t()
            {
            }
            MotorBase_t(uint8_t id) : _id(id)
            {
            }
            uint8_t _id;
            float _vel_target;
            float _angle_target;
            data_t _vel_raw;
            data_t _angle_raw;
    };
    class MotorInterface_t
    {
        public:
            MotorInterface_t()=default;
            MotorInterface_t(uint8_t id) : _id(id)
            {
            }
            virtual void setSpeed(float target) = 0;
            // virtual void update(void *param) = 0;
            virtual void update() = 0;
            virtual float getLinearspeed() = 0;
            uint8_t _id;
    };
    class Motorcommon_t :public MotorBase_t, public MotorInterface_t
    {
        public:
            ~Motorcommon_t(){};
            // 构造函数初始化TIM和通道
            Motorcommon_t(TIM_HandleTypeDef *htim_motor, TIM_HandleTypeDef *htim_encoder,uint32_t channel_motor,GPIO_TypeDef *PH_Port, uint16_t PH_Pin,uint8_t id = 0): MotorBase_t(id), MotorInterface_t(id)
            {
                _htim = htim_motor;
                _channel = channel_motor;
                HAL_TIM_PWM_Start(_htim, _channel);
                _encoder._htim = htim_encoder;
                // _period_load = _htim->Init.Period;//没初始化读个钩子的值
                 HAL_TIM_Encoder_Start(_htim, TIM_CHANNEL_ALL);
                _encoder._period_load = _htim->Init.Period;
                // 获取定时器PSC和ARR值
                _encoder._timer_psc = 1+_htim->Instance->PSC;
            }
            void setSpeed(float target) override;
            // void update(void *param) override;
            void update() override;
            float getLinearspeed() override;
            void pwm_out(int pwm);

            float _Factor = 19;
            float _WheelDiameter = 0.08;
            int _forward = 1;

        protected:
            TIM_HandleTypeDef *_htim;  // 定时器句柄
            uint32_t _channel;         // 定时器通道
            GPIO_TypeDef *_PH_Port;
            uint16_t _PH_Pin;
            // uint16_t _period_load;     // pwm的定时器的自动重装载值
            Encoder_t _encoder;//or Encoder_t(TIM_HandleTypeDef *htimx, float reduction_ratio, float encoder_ppr, float e_rpm,float r, float reload_ms)
            Pid_basetemplate_t<float, float> _pid = Pid_basetemplate_t<float, float>({0.1, 0.05, 0, 10, 200, -200});
    };
}

#endif
