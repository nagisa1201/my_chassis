/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-03 16:08:23
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-04 14:27:21
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\Control.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __CONTROL_H
#define __CONTROL_H
#include "Kinematic.h"
#include "Lib_Static.h"
#include "motor.h"


namespace Control
{
    enum Control_Mode_t
    {
        OpenLoop,
        HalfCloseLoop,
        PureCloseLoop
    };

    class Control_t
    {
        public:
        Control_t(Control_Mode_t mode):_motors(
            std::make_tuple(&htim8, &htim1, TIM_CHANNEL_1, IN1_GPIO_Port, IN1_Pin, IN2_Pin),
            std::make_tuple(&htim2, &htim1, TIM_CHANNEL_3, IN1_GPIO_Port, IN1_Pin, IN2_Pin),
            std::make_tuple(&htim2, &htim1, TIM_CHANNEL_3, IN1_GPIO_Port, IN1_Pin, IN2_Pin),
            std::make_tuple(&htim8, &htim1, TIM_CHANNEL_3, IN1_GPIO_Port, IN1_Pin, IN2_Pin)
        ){
            _mode=mode;
         }
        ~Control_t(){};


        void setTarget(vel_t car_target_vel);
        void initMotor();
        void controlLoop();


        Kinematic::Kinematic_t<4> _kinematic=Kinematic::Kinematic_t<4>(Kinematic::O_shape,0.2,0.2);
        Static::Static_t<Motor::Motorcommon_t,4> _motors;
        private:
        Control_Mode_t _mode;
    };
}
#endif //__CONTROL_H