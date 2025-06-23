// 对象的应用优化
#include <iostream>
using namespace std;

class Test
{
public:
    Test(int a=10):ma(a) 
    {cout<<"Test()"<<endl;}
    ~Test() 
    {cout<<"~Test()"<<endl;}
    Test(const Test &t):ma(t.ma) 
    {cout<<"Test(const Test &t)"<<endl;}
    Test& operator=(const Test &t) {
        cout << "operator=" << endl;
        ma = t.ma;
        return *this;
    }

private:
    int ma;
};

int main()
{
    Test t1;
    Test t2(t1);
    Test t3 = t1;
    // Test(20) 显式生成临时对象，调用拷贝构造函数 生存周期：所在的语句
    // C++编译器对于对象构造的优化： 用临时对象生成新对象的时候，临时对象就不产生了，直接构造新对象就可以了
    Test t4 = Test(20); // 和 Test t4(20); 没有区别

    cout << "-------------------------------------" << endl;

    return 0;
}