#ifndef __PID_COPY_H
#define __PID_COPY_H

typedef struct PID
{
    float Kp;
    float Ki;
    float Kd;

    float prev_error;
    float last_error;
    float error;
    float error_delta;
    float error_sum;

    float output;

    float integral_limit;
    float output_limit;
}PID;
//==================位置式PID==================
float limitIntegral(float value, float limit)
{
    if(value > limit)
    {
        return limit;
    }
    else if(value < -limit)
    {
        return -limit;
    }
    else
    {
        return value;
    }
}
float limitOutput(float value, float limit)
{
    if(value > limit)
    {
        return limit;
    }
    else if(value < -limit)
    {
        return -limit;
    }
    else
    {
        return value;
    }
}

float pidPosisionCalc(PID *pid, float target_val, float current_val)
{
    pid->error = target_val - current_val;
    pid->error_sum += pid->error;
    // pid->error_sum = limitIntegral(pid->error_sum, pid->integral_limit);
    pid->error_delta = pid->error - pid->last_error;

    pid->output = pid->Kp * pid->error + pid->Ki * pid->error_sum + pid->Kd * pid->error_delta;
    pid->output = limitOutput(pid->output, pid->output_limit);


    return pid->output;
}

void pidInitPosition(PID *pid, float Kp, float Ki, float Kd, float integral_limit, float output_limit)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->integral_limit = integral_limit;
    pid->output_limit = output_limit;
}
//==================位置式PID==================

//==================增量式PID==================
float pidIncrementCalc(PID *pid, float target_val, float current_val)
{
    pid->error = target_val - current_val;




    pid->output = pid->Kp * (pid->error - pid->last_error) + pid->Ki * pid->error + pid->Kd * (pid->error - 2 * pid->last_error + pid->prev_error);
    pid->output = limitIntegral(pid->output, pid->output_limit);

    pid->prev_error = pid->last_error;
    pid->last_error = pid->error;
    if(pid->output > pid->output_limit)
    {
        pid->output = pid->output_limit;
    }
    else if(pid->output < -pid->output_limit)
    {
        pid->output = -pid->output_limit;
    }

    return pid->output;
}
void pidInitIncrement(PID *pid, float Kp, float Ki, float Kd, float integral_limit, float output_limit)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;

    pid->prev_error=pid->last_error=pid->error=0;
    pid->output_limit =integral_limit= output_limit;
}

#endif