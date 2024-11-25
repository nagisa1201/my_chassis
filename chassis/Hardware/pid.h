/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-09 15:31:14
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-11-09 15:46:59
 * @FilePath: \MDK-ARMf:\project\cubemax\chassis\Hardware\pid.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __PID_H
#define __PID_H
#include "common.h"

template <typename T1,typename T2>
{
    struct Pidparam_t
    {
        T2 Kp;
        T2 Ki;
        T2 Kd;
        T1 Integralmax;
        T1 outputmax;
        T1 outputmin;
    }
}

template <typename T1,typename T2>
class Pid_basetemplate_t
{
    public:
        Pid_basetemplate_t(){};
        ~Pid_basetemplate_t(){};
        Pid_basetemplate_t(T2 Kp,T2 Ki,T2 Kd);
        Pid_basetemplate_t(T2 Kp,T2 Ki,T2 Kd,T1 Integralmax,T1 outputmax,T1 outputmin);
        //等待后续开发的构造函数
        Pid_basetemplate_t(Pidparam_t<T,T2> param):Kp(param.Kp),Ki(param.Ki),Kd(param.Kd),Integralmax(param.Integralmax),outputmax(param.outputmax),outputmin(param.outputmin)
        {
            _PrevError = 0;
            _LastError = 0;
            _Error = 0;
            _DError = 0;
        }

        void outputLimit(T1 outputmax,T1 outputmin);
        T1 pidCalc(T1 Target_val,T1 Actual_val);





        T2 _Kp;
        T2 _Ki;
        T2 _Kd;
        T1 _Integralmax;
        T1 _outputmax;
        T1 _outputmin;
    private:
        T1 _PrevError;
        T1 _LastError;
        T1 _Error;
        T1 _DError;

}


template <typename T1,typename T2>
Pid_basetemplate_t<T1,T2>::outputLimit(T1 outputmax,T1 outputmin)
{
    _outputmax = outputmax;
    _outputmin = outputmin;
}
