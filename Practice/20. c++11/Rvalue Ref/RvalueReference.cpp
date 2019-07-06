#include <iostream>
#include <cstring>

#if 0
class String
{
public:
    String(const char* str = "")
    {
        if (nullptr == str)
        {
            str = "";
        }    
        str_ = new char[strlen(str) + 1];

        strcpy(str_, str);

        std::cout << "构造" << std::endl;
    }

    String (const String& str)
        :str_(new char[strlen(str.str_) + 1])
    {
        strcpy(str_, str.str_);
        std::cout << "Copy 构造" << std::endl;
    }

    String (String&& str)
        :str_(str.str_)
    {
        str.str_ = nullptr;
        std::cout << "右值拷贝" << std::endl;
    }

    String& operator=(const String& str)
    {
        if (str_ != str.str_)
        {
            if (str_)
            {
                delete[] str_;
            }

            str_ = new char[strlen(str.str_) + 1];
            strcpy(str_, str.str_);

            std::cout << "Copy Assign" << std::endl;

            return *this;
        }
    }

    ~String ()
    {
        if (str_)
        {
            delete[] str_;
        }
    }
private:
    char* str_;
};

String GetString(const char* str)
{
    String tmp(str);
    return tmp;
}

int main(void)
{
    String str = GetString("Hello");
    String str2(str);
    String str3(std::move(str));

    return 0;
}
#endif

using namespace std;

void Fun(int &x) { cout << "lvalue ref" << endl; }
void Fun(int &&x) { cout << "rvalue ref" << endl; }
void Fun(const int &x) { cout << "const lvalue ref" << endl; }
void Fun(const int &&x) { cout << "const rvalue ref" << endl; }
template <typename T>
void PerfectForward(T &&t) { Fun(std::forward<T>(t)); }

int main()
{
    PerfectForward(10); // rvalue ref
    int a;
    PerfectForward(a);            // lvalue ref
    PerfectForward(std::move(a)); // rvalue ref
    const int b = 8;
    PerfectForward(b);            // const lvalue ref
    PerfectForward(std::move(b)); // const rvalue ref
    return 0;
}