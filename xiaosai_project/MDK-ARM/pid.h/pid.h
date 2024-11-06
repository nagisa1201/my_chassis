/**
 * @file pid.h
 * @author nagisa (2964793117@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef PID_H
#define PID_H

template<typename T1,typename T2>
class Pid_sw_param
{
public:
    Pid_sw_param(T1 kp_,T1 ki_,T1 kd_):kp(kp_),ki(ki_),kd(kd_){}
    Pid_sw_param(){}
protected:
    T1 kp;
    T1 ki;
    T1 kd;

};

template<typename T1,typename T2>
class Pid_func : public Pid_sw_param<T1,T2>
{
public:
    Pid_func(T1 kp_,T1 ki_,T1 kd_):Pid_sw_param<T1,T2>(kp_,ki_,kd_){}
    Pid_func(){}

    // void reset_param();
    T2 reset_error(T2 error_sum);

    T2 limit_output(T2 output_min,T2 output_max);
    T2 update(T2 current_value);
    void set_target(T2 target);

protected:
    T2 error;
    T2 error_last;
    T2 error_delta;
    T2 error_sum;
    T2 output;
    T2 output_min;
    T2 output_max;
    T2 last_out;
    T2 target;
};

template <typename T1, typename T2>
void Pid_func<T1,T2>::reset_param()
{   
    kp=0;
    ki=0;
    kd=0;
    error = 0;
    error_last = 0;
    error_delta=0
    error_sum = 0;
    output = 0;
}

template <typename T1, typename T2>
 T2 reset_error(T2 error_sum)
 {
        error_sum = 0;
        return error_sum;
 }
 

template <typename T1, typename T2>
T2 limit_output(T2 output_min,T2 output_max)
{
    if(output > output_max)
    {
        output = output_max;
    }
    else if(output < output_min)
    {
        output = output_min;
    }
    return output;
}
 
 
template <typename T1, typename T2>
T2 Pid_func<T1,T2>::update(T2 current_value)
{
    error = this->target_ - current_value;
    error_sum += error;
    error_delta = error_last - error;
    error_last = error;
    if(output > output_max)
    {
        output = output_max;
    }
    else if(output < output_min)
    {
        output = output_min;
    }
    T2 output= kp*error + ki*error_sum + kd*error_delta;
    if (output > out_max_)
    {
        output = out_max_;
    }
    else if (output < out_min_)
    {
        output = out_min_;
    }

    last_output_ = output;
    return output;
}

#endif // PID_H

