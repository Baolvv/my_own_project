#ifndef __SCPP_ASSERT_HPP_INCLUDED__
#define __SCPP_ASSERT_HPP_INCLUDED__

#include <sstream> // std::stringstream

#ifdef SCPP_THROW_EXCEPTIONS_ON_BUG
#include <exception>

namespace scpp
{
// 当下面所定义的安全检查失败
// 并且 #ifdef SCPP_THROW_EXCEPTIONS_ON_BUG 时抛出这个异常
class ScppAssertFailedException : public std::exception
{
public:
    ScppAssertFailedException(const char* file_name, unsigned line_number, const char* message);
    virtual const char* what() const throw() { return what_.c_str(); }
    virtual ~ScppAssertFailedException() throw() {}
private:
    std::string what_;
};
} // namespace scpp
#endif

void SCPP_AssertErrorHandler(const char* file_name, unsigned line_number, const char* message);

// 永久性安全检查宏
#define SCPP_ASSERT(condition, msg)                 \
    if (!(condition)) {                             \
        std::ostringstream s;                       \
        s << msg;                                   \
        SCPP_AssertErrorHandler(                    \
            __FILE__, __LINE__, s.str().c_str());   \
    }

#ifdef _DEBUG
#define SCPP_TEST_ASSERT_ON
#endif

// 临时性（只用于测试）安全检查宏
#ifdef SCPP_TEST_ASSERT_ON
#define SCPP_TEST_ASSERT(condition, msg) SCPP_ASSERT(condition, msg)
#else
#define SCPP_TEST_ASSERT(condition, msg) // 不执行任何操作
#endif

#endif // __SCPP_ASSERT_HPP_INCLUDED__