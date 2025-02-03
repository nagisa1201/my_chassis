/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-02 21:53:47
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-03 22:44:17
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


namespace Kinematic
{
    struct vel_t
    {
        float vx;
        float vy;
        float w;
    };
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
            // :motors( 
            // std::make_tuple(&htim8, &htim1, TIM_CHANNEL_1, IN1_GPIO_Port, IN1_Pin, IN2_Pin),
            // std::make_tuple(&htim2, &htim1, TIM_CHANNEL_1, IN1_GPIO_Port, IN1_Pin, IN2_Pin),
            // std::make_tuple(&htim2, &htim1, TIM_CHANNEL_1, IN1_GPIO_Port, IN1_Pin, IN2_Pin),
            // std::make_tuple(&htim8, &htim1, TIM_CHANNEL_1, IN1_GPIO_Port, IN1_Pin, IN2_Pin)
            // )
            {
                _target_xyw={0,0,0};
                _current_xyw={0,0,0};
                _wheel=wheelclass;
                _track_width=track_width;
                _track_length=track_length;
            }
            
            void inverseCalbody();//从车身目标速度到轮子目标速度
            void forwardCalbody();//从轮子实际速度到车身实际速度
            
            template<typename T, typename... Args>
            void updateTargetvel(Args&&... args);

            void updateCurrentvel();
            

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

}


#endif