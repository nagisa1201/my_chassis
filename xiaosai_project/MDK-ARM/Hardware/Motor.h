#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f4xx_hal.h"

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

            // 设置电机速度
            int Motor_speed_set(float pulse)
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

        private:
            TIM_HandleTypeDef *_htim;  // 定时器句柄
            uint32_t _Channel;         // 定时器通道
            uint16_t _period_load;     // 定时器的自动重装载值
            uint16_t _compare_arr;     // 定时器的比较值
    };

}

#endif
