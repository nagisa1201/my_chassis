/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-02 21:53:47
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-02 22:13:39
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\Kinematic.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __KINEMATIC_H
#define __KINEMATIC_H

#define USE_MECANUM_WHEEL 1
#include "stdint.h"
#include "math.h"
#include "pid.h"
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
    class Kinematic_t
    {
        public:
            Kinematic_t(wheelclass_t wheelclass,float track_width,float track_length)
            {
                _real_vel={0,0,0};
                _target_vel={0,0,0};
                _wheel=wheelclass;
                _track_width=track_width;
                _track_length=track_length;
            }
        void inverseCalbody();
        void forwardCalbody();




        private:
            vel_t _real_vel;
            vel_t _target_vel;
            wheelclass_t _wheel;
            float _track_width;
            float _track_length;
    };

}


#endif