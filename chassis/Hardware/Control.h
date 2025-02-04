/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-03 16:08:23
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-04 21:22:23
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
        Control_t(Control_Mode_t mode):_motors(//将所有IN1置0，IN2置1，但连接时1连1,2连2
            std::make_tuple(&htim8, &htim1, TIM_CHANNEL_1, AIN1_GPIO_Port, AIN1_Pin, AIN2_Pin),
            std::make_tuple(&htim8, &htim3, TIM_CHANNEL_2, BIN1_GPIO_Port, BIN1_Pin, BIN2_Pin),
            std::make_tuple(&htim8, &htim4, TIM_CHANNEL_3, CIN1_GPIO_Port, CIN1_Pin, CIN2_Pin),
            std::make_tuple(&htim8, &htim5, TIM_CHANNEL_4, DIN1_GPIO_Port, DIN1_Pin, DIN2_Pin)
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