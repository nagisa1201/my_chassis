/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-29 17:29:00
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-04 13:58:55
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\Encoder.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __ENCODER_H
#define __ENCODER_H

#include "common.h"
#include "motor.h"


#define PI 3.1415926
namespace Motor
{
    class Encoder_t
    {   
        public:
            ~Encoder_t(){};
            Encoder_t(){};
            Encoder_t(TIM_HandleTypeDef *htimx, float reduction_ratio, float encoder_ppr, float e_rpm,float r, float reload_ms)
            {
                _reduction_ratio = reduction_ratio;
                _encoder_ppr = encoder_ppr;
                _e_rpm = e_rpm;
                _e_pulsev= e_rpm / 60 ;//额定转速从转每分钟转化为转每秒
                _r = r;
                _reload_ms = reload_ms;
            }


            void clockCntGet()
            {
                _pulse_count = _htim->Instance->CNT;
                if (_pulse_count > 0xefff)
                    {
                        _pulse_count -= 0xffff;
                    }
                _htim->Instance->CNT = 0;
            }
            void calculateSpeed()
            {
                // 计算电机转速（单位：转每秒）
                _pulse_v = (_pulse_count) / (_encoder_ppr* 4 * _reduction_ratio / _timer_psc) * 1000 / _reload_ms ;
                _angular_v = _pulse_v * 2 * PI ;
                _velocity = _angular_v * _r;
            }

            int16_t _pulse_count;//当前编码器时钟计数值
    
//=======================================================   
            float _pulse_v;
            float _angular_v;
            float _velocity;
            float _e_pulsev;
            float _r;

            float _reduction_ratio;
            float _encoder_ppr;
            float _e_rpm;
            float _reload_ms;

//=======================================================
            TIM_HandleTypeDef *_htim;  // 编码器定时器
            uint16_t _period_load;//定时器的自动重装载值
            uint16_t _timer_psc;//编码器时钟的预分频值


    };
}
#endif