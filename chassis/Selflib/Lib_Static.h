/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-02 22:43:14
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-02 23:33:47
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Selflib\Lib_Static.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __LIB_STATIC_H
#define __LIB_STATIC_H
#include <cstddef> //size_t
#include <utility> //std::forward
#include <new> //new函数需要

namespace Static
{
    template<typename type_name, size_t capacity_max>//size_t是无符号整数类型,可以填在数组括号表示大小
    class Static_t
    {
        public:
            Static_t()=default;
            ~Static_t(){};

            template<typename... Args>
            Static_t(size_t n, Args&&... args) : _size(n) 
            {
                for(size_t i = 0; i < n; ++i) {
                    new(&_static[i]) type_name(std::forward<Args>(args)...); //原地构造
                }
            }

            type_name _static[capacity_max];
            size_t _size = 0;
    };
}
#endif