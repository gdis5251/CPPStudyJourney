#include "Code.h"

int main(void)
{
    // 会打印 GameLog()
    // 因为在 kill 类构造的过程中
    // 虚函数表并没有生成
    // 编译器只能调用当前作用域内的同名函数
    Kill a;

    return 0;
}
