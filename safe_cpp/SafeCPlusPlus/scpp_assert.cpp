#include "scpp_assert.hpp"

#include <iostream>          // cerr, endl, flush
#include <stdlib.h>         // exit()

using namespace std;

#ifdef SCPP_THROW_EXCEPTIONS_ON_BUG
namespcae scpp 
{
    ScppAssertFailedException::ScppAssertFailedException(const char* file_name, unsigned line_number, const char* message)
    {
        ostringstream s;
        s << "SCPP assertion failed with message '" << message << "' in file " << file_name << " #" << line_number;
        
        what_ = s.str();
    }
}

#endif

void SCPP_AssertErrorHandler(const char* file_name, unsigned line_number, const char* message)
{
    // 此处适合插入断点：
    // 在适当的情况下还可以向一个日志文件写入相同的信息

#ifdef SCPP_THROW_EXCEPTIONS_ON_BUG
    throw scpp::ScppAssertFailedException(file_name, line_number, message);

#else
    cerr << message << "in file " << file_name << " #" << line_number << endl << flush;
    // Terminate application
    exit(1);
#endif
}