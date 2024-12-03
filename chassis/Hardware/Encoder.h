/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-29 17:29:00
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-12-02 16:11:33
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
    class Encoder_base_t
    {   
        public:

        ~Encoder_base_t(){};
        Encoder_base_t(TIM_HandleTypeDef *htimx)
        {   
            _htim = htimx;
        }
      
        void EncoderpinInit()
        {
             HAL_TIM_Encoder_Start(_htim, TIM_CHANNEL_ALL);
            _period_load = _htim->Init.Period;
            // 获取定时器PSC和ARR值
            _timer_psc = 1+_htim->Instance->PSC;

        }
        void clockCntGet()
        {
            _pulse_count = int16_t(__HAL_TIM_GET_COUNTER(_htim));
            __HAL_TIM_SET_COUNTER(_htim, 0);  // 将计数器清零
        }


        int16_t _pulse_count;//当前编码器时钟计数值
        protected:
            TIM_HandleTypeDef *_htim;  // 编码器定时器
            uint16_t _period_load;//定时器的自动重装载值
            uint16_t _timer_psc;//编码器时钟的预分频值
            // uint16_t _pulse_count;//当前编码器时钟计数值

    };
    class EncoderInterface_t : public Encoder_base_t
    {
        public:

            ~EncoderInterface_t(){};
            EncoderInterface_t(TIM_HandleTypeDef *htimx,int16_t full_CNT, float reload_ms):Encoder_base_t(htimx)
            {
                _full_CNT = full_CNT;
                _reload_ms = reload_ms;
            }
    /*
        在 C++ 中，子类是对父类的扩展，但是父类的构造函数仍然负责初始化父类部分的数据成员，
        而子类负责扩展和初始化子类的成员。具体来说，子类的构造函数必须显式调用父类的构造函数，
        以确保父类部分的成员变量能够被正确初始化。
    */
            void CalculateSpeed()
            {
                // 计算电机转速（单位：转每秒）
                _pulse_v = (_pulse_count) / (_encoder_ppr* 4 * _reduction_ratio / _timer_psc) * 1000 / _reload_ms ;
                _angular_v = _pulse_v * 2 * PI ;
                _velocity = _angular_v * _r;
            }

            float _pulse_v;
            float _angular_v;
            float _velocity;
            float _e_pulsev;
            float _r;
            int16_t _full_CNT;//自行测量当电机最大功率转速时的编码器一次中断的最大CNT值
        protected:
            
            float _reduction_ratio;
            float _encoder_ppr;
            float _e_rpm;
   
            float _reload_ms;

    };
}
#endif