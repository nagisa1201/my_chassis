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

#ifndef __PID_H
#define __PID_H

template <typename T, typename T2>
struct PidBaseConfig_T
{
    T2 kp = 0;
    T2 ki = 0;
    T2 kd = 0;
    T out_min = 0;
    T out_max = 0;
    T integral_max = 25;
};

template <typename T, typename T2>
class pid_base_template_t
{
public:
    // 构造函数
    pid_base_template_t() {}; // 默认构造函数
    pid_base_template_t(T2 kp, T2 ki, T2 kd);//带3参构造函数
    pid_base_template_t(T2 kp, T2 ki, T2 kd, T out_min, T out_max);//带5参构造函数
    pid_base_template_t(PidBaseConfig_T<T, T2> config) : pid_base_template_t(config.kp, config.ki, config.kd, config.out_min, config.out_max);
    T target_;
    T2 kp_;         // 比例系数
    T2 ki_;         // 积分系数
    T2 kd_;         // 微分系数
    T last_output_; // 上一次输出值

    T update(T contrl);                                     // 更新输出，在有target情况下
    T cal(T target, T contrl, bool clear_integral = false); // 计算
    void reset(void);                                       // 重置pid控制器
    void target_update(T target, bool clear_integral = false);
    void pid_update(T2 kp, T2 ki, T2 kd); // 更新pid
    void out_limit(T out_min, T out_max); // 设置限幅
    void reset_integral(void);            // 重置积分
    T output_limit(T output);             // 输出限幅
protected:
    T error;              // 误差
    T error_sum;          // 累计误差
    T error_sum_max = 25; // 积分上限;

    T error_delta; // 误差微分
    T error_last;  // 上一次的误差

    T error_pre; // 前次的误差

    T out_min_; // 输出下限
    T out_max_; // 输出上限
};



template <typename T, typename T2>
pid_base_template_t<T, T2>::pid_base_template_t(T2 kp, T2 ki, T2 kd)
{
    reset();                // 初始化控制器
    pid_update(kp, ki, kd); // 更新PID参数
}


template <typename T, typename T2>
pid_base_template_t<T, T2>::pid_base_template_t(T2 kp, T2 ki, T2 kd, T out_min, T out_max)
{
    pid_update(kp, ki, kd); // 更新PID参数
    out_limit(out_min, out_max);
}

template <typename T, typename T2>
pid_base_template_t<T, T2>::pid_base_template_t(PidBaseConfig_T<T, T2> config) : pid_base_template_t(config.kp, config.ki, config.kd, config.out_min, config.out_max)
{
    error_sum_max = config.integral_max;//初始化积分上限，这个参数在前面并未传入
};//委托构造函数，调用上面的构造函数，PidBaseConfig_T<T, T2> config传入结构体参数，并借助上述带5参的构造函数赋值，相当于一个带结构体参数的带参构造函数


template <typename T, typename T2>
void pid_base_template_t<T, T2>::reset(void)
{
    last_output_ = 0.0f; // 上一次的控制输出值
    target_ = 0.0f;      // 控制目标值
    out_min_ = 0.0f;     // 控制输出最小值
    out_max_ = 0.0f;     // 控制输出最大值

    kp_ = 0.0;
    ki_ = 0.0;
    kd_ = 0.0;

    error = 0.0;
    error_delta = 0.0;
    error_last = 0.0;
    error_sum = 0.0;
    error_pre = 0.0;
}


template <typename T, typename T2>
void pid_base_template_t<T, T2>::pid_update(T2 kp, T2 ki, T2 kd)
{
    reset();
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
}

template <typename T, typename T2>
void pid_base_template_t<T, T2>::out_limit(T out_min, T out_max)
{
    out_min_ = out_min;
    out_max_ = out_max;
}


template <typename T, typename T2>
void pid_base_template_t<T, T2>::target_update(T target, bool clear_integral)
{
    target_ = target;
    if (clear_integral)
    {
        error_sum = 0;
    }
}

template <typename T, typename T2>
T pid_base_template_t<T, T2>::update(T contrl)
{
    error = target_ - contrl;
    error_sum += error;
    error_delta = error_last - error;
    error_last = error;
    //实现上述公式

    if (error_sum > error_sum_max)
    {
        error_sum = error_sum_max;
    }
    //积分项正限幅
    if (error_sum < -error_sum_max)
    {
        error_sum = -error_sum_max;
    }
    //积分项负限幅
    T output = kp_ * error + ki_ * error_sum + kd_ * error_delta;
    //输出值最大最小值限幅
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


template <typename T, typename T2>
void pid_base_template_t<T, T2>::reset_integral(void)
{
    error_sum = 0;
}

template <typename T, typename T2>
T pid_base_template_t<T, T2>::cal(T target, T contrl, bool clear_integral)
{
    target_update(target, clear_integral);
    return update(contrl);
    //返回update中的output
}

template <typename T, typename T2>
T pid_base_template_t<T, T2>::output_limit(T output)
{
    if (output > out_max_)
    {
        output = out_max_;
    }
    else if (output < out_min_)
    {
        output = out_min_;
    }
    return output;
}

#endif // PID_H

