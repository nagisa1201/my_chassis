/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-24 19:36:08
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-01 00:52:07
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Core\Inc\maincpp.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MAINCPP_H
#define __MAINCPP_H

#ifdef __cplusplus
#include "common.h"
extern "C" {
#endif

void main_cpp(void);
void OnceMain(void);
void Serial_Printf(char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
