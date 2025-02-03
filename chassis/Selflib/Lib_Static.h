/*
 * @Author: Nagisa 2964793117@qq.com
 * @Date: 2025-02-02 22:43:14
 * @LastEditors: Nagisa 2964793117@qq.com
 * @LastEditTime: 2025-02-03 13:51:12
 * @FilePath: \MDK-ARMf:\project\git\my_chassis\chassis\Selflib\Lib_Static.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __LIB_STATIC_H
#define __LIB_STATIC_H
#include <cstddef> //size_t
#include <utility> //std::forward
#include <new> //new函数需要
#include <tuple> //std::tuple

namespace Static
{
    template<typename type_name, size_t capacity_max>//size_t是无符号整数类型,可以填在数组括号表示大小
    class Static_t
    {
        public:
            Static_t()=default;
            ~Static_t(){};

            template<typename... ArgsTuples>
            Static_t(ArgsTuples&&... args_tuples) : _size(sizeof...(ArgsTuples)) 
            {
                _construct_impl<0>(std::forward<ArgsTuples>(args_tuples)...);
            }

            type_name _static[capacity_max];
            size_t _size = 0;

        private:
            // 递归展开参数元组的实现
            template<size_t Index, typename Tuple, typename... Rest>
            void _construct_impl(Tuple&& tuple, Rest&&... rest)
            {
                _construct_element(Index, std::forward<Tuple>(tuple));
                _construct_impl<Index + 1>(std::forward<Rest>(rest)...);
            }

            // 递归重载终止条件
            template<size_t Index>
            void _construct_impl() {}

            // 元组展开辅助函数
            template<typename Tuple, size_t... Is>
            void _construct_from_tuple(size_t index, Tuple&& tuple, std::index_sequence<Is...>)
            {
                new (&_static[index]) type_name(std::forward<typename std::tuple_element<Is, Tuple>::type>(std::get<Is>(std::forward<Tuple>(tuple)))...);
            }                                                         //类型萃取模板                        //元组的元素，目的是完美转发到构造函数

            // 构造单个元素的入口
            template<typename Tuple>
            void _construct_element(size_t index, Tuple&& tuple)
            {
                using Indices = std::make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>;
                _construct_from_tuple(index, std::forward<Tuple>(tuple), Indices{});
            }
    };
}
#endif