/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-29 23:02:27
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-02 23:37:07
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Core\Src\maincpp.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "maincpp.h"
#include "motor.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include "Lib_Static.h"

void OnceMain();
void main_cpp();
void Serial_Printf(char *format, ...);

Motor::Motorcommon_t motor(&htim8,&htim1,TIM_CHANNEL_1,IN1_GPIO_Port,IN1_Pin,IN2_Pin);
// Static::Static_t<Motor::Motorcommon_t, 4> motors(4,&htim8,&htim1,TIM_CHANNEL_1,IN1_GPIO_Port,IN1_Pin,IN2_Pin);

float v = 0;
void main_cpp()
{                                     
    // Motor::Motorcommon_t motor(&htim8,&htim1,TIM_CHANNEL_1,IN1_GPIO_Port,IN1_Pin);
    motor.initMotor();
}

void OnceMain()
{
    motor.setSpeed(3);
    v=motor.getLinearspeed();
    motor.update();                                                                                                             

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


