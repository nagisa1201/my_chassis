#ifndef __ENCODER_H
#define __ENCODER_H

#include "common.h"
#include "motor.h"


#define PI 3.1415926
namespace Motor
{
    class Encoder_base_t : public MotorInterface_t
    {   
        public:

        ~Encoder_base_t(){};
        Encoder_base_t(TIM_HandleTypeDef *htimx)//在构造函数里初始化各寄存器值
        {   
            _htim=htimx;
            _period_load = _htim->Init.Period;
            // 获取定时器PSC和ARR值
            _timer_psc = _htim->Instance->PSC;
        }
      
        void EncoderpinInit(TIM_HandleTypeDef *htimx)
        {
            _htim = htimx;
             HAL_TIM_Encoder_Start(_htim, TIM_CHANNEL_ALL); 
        }
        void clockCntGet()
        {
            _pulse_count = _htim->Instance->CNT;
            __HAL_TIM_SET_COUNTER(_htim, 0);  // 将计数器清零
        }


        
        protected:
            TIM_HandleTypeDef *_htim;  // 定时器句柄
            uint32_t _period_load;//定时器的自动重装载值
            uint32_t _timer_psc;//定时器的预分频值
            uint32_t _pulse_count;//当前计数值

    };
    class EncoderInterface_t : public Encoder_base_t
    {
        public:

            ~EncoderInterface_t(){};
           EncoderInterface_t(TIM_HandleTypeDef *htimx, float reduction_ratio, float encoder_ppr, float r): Encoder_base_t(htimx), _reduction_ratio(reduction_ratio), _encoder_ppr(encoder_ppr), _r(r) {}
    /*
        在 C++ 中，子类是对父类的扩展，但是父类的构造函数仍然负责初始化父类部分的数据成员，
        而子类负责扩展和初始化子类的成员。具体来说，子类的构造函数必须显式调用父类的构造函数，
        以确保父类部分的成员变量能够被正确初始化。
    */
            void CalculateSpeed()
            {
                // 计算电机转速（单位：脉冲每秒）
                _pulse_v = _pulse_count / (_encoder_ppr* 4 * _reduction_ratio / _timer_psc);
                _angular_v = _pulse_v * 2 * PI ;
                _velocity = _angular_v * _r;
            }

            float _pulse_v;
            float _angular_v;
            float _velocity;

        private:
            float _r;
            float _reduction_ratio;
            float _encoder_ppr;

    };
}
#endif