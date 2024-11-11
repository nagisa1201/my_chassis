/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2024-11-11 16:36:46
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2024-11-11 16:50:28
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Hardware\encoder.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/**
 * @file encoder.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __ENCODER_H
#define __ENCODER_H
#include "common.h"
namespace Motor
{
     class EncoderInterface_t
    {
    public:
        void EncoderInit(TIM_HandleTypeDef *htimx)
        {
            _htim = htimx;
            HAL_TIM_Encoder_Start(_htim, TIM_CHANNEL_ALL);  // 启动编码器
        }

        int32_t Get_once_Count()
        {
            encoder_count =__HAL_TIM_GET_COUNTER(_htim);  // 获取编码器计数值
            __HAL_TIM_SET_COUNTER(_htim, 0); // 重置计数器
            return encoder_count;          
        }

    private:
        TIM_HandleTypeDef *_htim;  // 定时器句柄
        uint32_t encoder_count;         
    };
}
#endif