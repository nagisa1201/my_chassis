/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-29 23:02:27
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-14 21:32:58
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Core\Src\maincpp.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-29 23:02:27
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-04 12:30:26
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Core\Src\maincpp.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "maincpp.h"
#include "motor.h"
#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include "Lib_Static.h"
#include "Kinematic.h"
#include "Control.h"

void OnceMain();
void main_cpp();
void Serial_Printf(char *format, ...);

Control::Control_t control(Control::HalfCloseLoop);

#if DEBUG
vel_t debug_target = {0, 0, 0};
#endif  

void main_cpp()
{                                     
    control.initMotor();
    control.setTarget({20, 20, 20}); 

}

void OnceMain()
{
    control.controlLoop();
    #if DEBUG
    // control.setTarget({debug_target.vx,debug_target.vy,debug_target.w});
    control.debugSingleMotor();
    #endif  
    // Serial_Printf("vx:%f,vy:%f,w:%f\n", control._kinematic._current_xyw.vx, control._kinematic._current_xyw.vy, control._kinematic._current_xyw.w);
    // HAL_Delay(5);                                                                                                        
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


