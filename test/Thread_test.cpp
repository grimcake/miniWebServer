#include <iostream>
#include "../tools/Thread.h"

int main() {
    std::cout << CurrentThread::getCurrentTid() << std::endl;
    return 0;
}