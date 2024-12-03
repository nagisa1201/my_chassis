/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-29 23:02:27
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-12-02 16:13:20
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Core\Src\maincpp.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "maincpp.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"

Motor::MotorInterface_t motor(&htim8 , TIM_CHANNEL_1, &htim1 ,10000,5);
void OnceMain();
void Serial_Printf(char *format, ...);
float pulse_v = 0;
float proportion = 0;
float v = 0;
int main_cpp()
{ 
    motor._encoder.EncoderpinInit();
    motor.MotorpinInit();
    return 0;
}

void OnceMain()
{
    motor.pidControlV(5);
    motor.Motor_start();
    pulse_v = motor._output_pulse_v;
    proportion =motor._actual_proportion;
    v = motor._encoder._velocity;
}

void Serial_Printf(char *format, ...)
{
    char String[100];              // 定义字符数组
    va_list arg;                   // 定义可变参数列表数据类型的变量arg
    va_start(arg, format);         // 从format开始，接收参数列表到arg变量
    vsprintf(String, format, arg); // 使用vsprintf打印格式化字符串和参数列表到字符数组中
    va_end(arg);                   // 结束变量arg
    // Serial_SendString(String);     // 串口发送字符数组（字符串）
    HAL_UART_Transmit(&huart4, (uint8_t *)String, strlen(String), 0xffff);
}


