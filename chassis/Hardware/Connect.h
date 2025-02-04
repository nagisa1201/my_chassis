/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-04 22:44:25
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-04 22:46:20
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\Connect.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __CONNECT_H
#define __CONNECT_H
#include "main.h"
#include "stdio.h"
#include <stdarg.h>
#include "string.h"

namespace Connect
{
    void Serial_Printf(UART_HandleTypeDef *huart, char *fmt, ...);

}
#endif //__CONNECT_H

