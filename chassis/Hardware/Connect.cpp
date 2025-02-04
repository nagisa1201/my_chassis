#include "Connect.h"
using namespace Connect;
void Connect::Serial_Printf(UART_HandleTypeDef *huart, char *fmt, ...)
{
    char buf[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    HAL_UART_Transmit(huart, (uint8_t *)buf, strlen(buf), 0xffff);
    va_end(args);
}