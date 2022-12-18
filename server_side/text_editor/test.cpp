 #include "include/TextEditor.hpp"
#include "include/Command.hpp"
#include "src/Command.cpp"
#include "include/TextEditor.hpp"
#include "src/TextEditor.cpp"
 #include "include/WorkWithData.hpp"
#include "src/WorkWithData.cpp"

#include <iostream>
#include <fstream>

void EXPECT_EQ(char a, char b) {
    if (a != b) {
        std::cout << a << '|' << b << std::endl;
    }
}

#include <iostream>
int main() {
    WorkWithData work;

    work.userFirst();

    work.operationWithData("i:a:0");
    work.operationWithData("i:b:0");
    work.operationWithData("i:c:0");
    work.operationWithData("i:\n:0");
    
    std::cout << work.getLine(0);
    std::cout << work.getLine(1);
    std::cout <<"SSS\n";
    
    work.operationWithData("d:1|0", 1);
    std::cout << work.getLine(0);
    std::cout << work.getLine(1);
    std::cout <<"SSS\n";

    work.operationWithData("d:0");
    std::cout << work.getLine(0);
    std::cout <<"SSS\n";

    // std::ofstream out("D:\\hello.txt");
    // if (out.is_open())
    // {
    //     out << "Welcome to CPP" << std::endl;
    // }
    // out.close(); 
    // out.open("D:\\hello.txt", std::ios::app);
    // if (out.is_open())
    // {
    //     out << "Welcome to CPP1" << std::endl;
    // }
    // out.close();

    // std::string line;
 
    // std::ifstream in("D:\\hello.txt"); // окрываем файл для чтения
    // if (in.is_open())
    // {
    //     while (getline(in, line))
    //     {
    //         std::cout << line << std::endl;
    //     }
    // }
    // in.close();


    return 0;
}