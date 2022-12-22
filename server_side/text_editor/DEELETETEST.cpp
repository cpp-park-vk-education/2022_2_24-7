#include "WorkWithData.hpp"

int main() {
    WorkWithData a;
    a.userFirst(0,0);
    a.addFile("");

    std::cout << a.operationWithData("i:a:0") << std::endl;
    a.operationWithData("i:b:1");
    a.operationWithData("i:\n:1");
    std::cout << a.operationWithData("i:4|0|x:1|0:2|0:3", 1) << std::endl;

    a.operationWithData("d:0");
    a.getFileWithDataDricetory();

    return 0;
}