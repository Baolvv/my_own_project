#ifndef __SCPP_VECTOR_HPP_INCLUDED__
#define __SCPP_VECTOR_HPP_INCLUDED__
#include "scpp_assert.hpp"
#include <vector>

namespace scpp
{
// std::vector的包装器，在操作符[]中提供了临时的安全检查
template <typename T>
class vector : public std::vector<T> {
public:
    typedef unsigned size_type;
    
    // 大多数常用的构造函数：
    explicit vector(size_type n = 0) : std::vector<T>(n) {}

    vector(size_type n, const T& value) : std::vector<T>(n, value) {}

    template <class InputIterator> vector(InputIterator first, InputIterator last) : std::vector<T>(first, last) {}
    
    // 注意： 我们并没有提供拷贝构造函数和赋值操作符，
    // 我们依赖编译器所提供的这些方法的默认版本。

    T& operator[](size_type index) {
        SCPP_TEST_ASSERT(index < std::vector<T>::size(),
            "index " << index << " must be less than "
            << std::vector<T>::size();
        return std::vector<T>::operator[](index));
    }
};
} // namespace scpp

template <typename T>
inline
std::ostream& operator << (std::ostream& os, const scpp::vector<T>& v) {
    for(unsigned i=0; i<v.size(); ++i) {
        os << v[i];
        if(i + 1 < v.size())
            os << " ";
    }
    return os;
}

#endif // __SCPP_VECTOR_HPP_INCLUDED__