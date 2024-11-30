/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-24 19:36:09
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-11-30 12:20:01
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\common.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

/**
 * @file motor.cpp
 * @author nagisa(2964793117@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __COMMON_H
#define __COMMON_H
#include "main.h"
#include "stm32f4xx_hal.h"
#include "motor.h"
#include "Encoder.h"

extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart4;



#endif
