/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-09 15:31:14
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-01 00:08:39
 * @FilePath: \MDK-ARMf:\project\cubemax\chassis\Hardware\pid.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __PID_H
#define __PID_H
#include "common.h"

template <typename T1,typename T2>
struct Pidparam_t
{
    T2 Kp;
    T2 Ki;
    T2 Kd;
    T1 Integralmax;
    T1 outputmax;
    T1 outputmin;
};


template <typename T1,typename T2>
class Pid_basetemplate_t
{
    public:
        Pid_basetemplate_t(){};
        ~Pid_basetemplate_t(){};
        Pid_basetemplate_t(T2 Kp,T2 Ki,T2 Kd);
         Pid_basetemplate_t(T2 Kp,T2 Ki,T2 Kd,T1 outputmax,T1 outputmin)
        {
            _Kp = Kp;
            _Ki = Ki;
            _Kd = Kd;
            _outputmax = outputmax;
            _outputmin = outputmin;
        };
        //等待后续开发的构造函数
        Pid_basetemplate_t(Pidparam_t<T1,T2> param):Pid_basetemplate_t(param.Kp,param.Ki,param.Kd,param.outputmax,param.outputmin)
        { 
            _Integralmax = param.Integralmax;
            _LastError = 0;
            _Error = 0;
            _DError = 0;
            _output = 0;
        };


        void outputLimit(T1 outputmax,T1 outputmin);
        T1 pidCalc(T1 Actual_val);
        void targetUpdate(T1 target, bool clear_integral = false);

        T2 _Kp;
        T2 _Ki;
        T2 _Kd;
        T1 _Integralmax;
        T1 _outputmax;
        T1 _outputmin;
        T1 _output ;
        T1 _target;


    protected:
        T1 _LastError;
        T1 _Error;
        T1 _DError;
        T1 _SumError;
};


template <typename T1,typename T2>
void Pid_basetemplate_t<T1,T2>::outputLimit(T1 outputmax,T1 outputmin)
{
    _outputmax = outputmax;
    _outputmin = outputmin;
}


template <typename T1,typename T2>
T1 Pid_basetemplate_t<T1,T2>::pidCalc(T1 Actual_val)
{
    _Error = _target - Actual_val;
    _SumError += _Error;
    _DError = _Error - _LastError;
    _LastError = _Error;
    if(_SumError > _Integralmax)
    {
        _SumError = _Integralmax;
    }
    else if(_SumError < -_Integralmax)
    {
        _SumError = -_Integralmax;
    }
    _output = _Kp*_Error + _Ki*_SumError + _Kd*_DError;
    return _output;
}

template <typename T1, typename T2>
void Pid_basetemplate_t<T1, T2>::targetUpdate(T1 target, bool clear_integral) 
{
    _target = target;
    if (clear_integral) 
    {
        _SumError = 0;
    }
}



template <typename T1,typename T2>
class Pid_Incremental_template_t : public Pid_basetemplate_t<T1,T2>
{
    public:
        Pid_Incremental_template_t(Pidparam_t<T1, T2> config):Pid_basetemplate_t<T1, T2>(config) 
        {
            this->_PrevError = 0;
        }
        T1 pidIncrementalCalc(T1 Actual_val);

    private:
        T1 _PrevError;
};

template <typename T1,typename T2>
T1 Pid_Incremental_template_t<T1,T2>::pidIncrementalCalc(T1 Actual_val)
{
    this->_Error = this->_target - Actual_val;
    //模板类protected成员变量一定要加this->，否则会报错
    this->_output += this->_Kp*(this->_Error - this->_LastError) + this->_Ki*this->_Error + this->_Kd*(this->_Error - 2*this->_PrevError + this->_LastError);
    this->_PrevError = this->_LastError;
    this->_LastError = this->_Error;
    if(this->_output > this->_outputmax)
    {
        this->_output =this->_outputmax;
    }
    else if(this->_output < this->_outputmin)
    {
        this->_output =this->_outputmin;
    }
    return this->_output;
}

#endif
//1.target - actual若为正证明要加速，若为负证明要减速而不是反过来
//2.当构造函数为列表初始化时，不能通过{}来传入模板结构体
//你尝试使用 {} 列表初始化来传递 Pidparam_t 结构体给构造函数，但遇到的问题是：在模板类中，初始化列表和构造函数的匹配可能会因为类型推导问题而失败。
//3.模板类的protected成员变量一定要加this->，否则会报错
