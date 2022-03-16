#include <iostream>

#include "matrix.hpp"

//aware of const
std::vector<std::vector<double>> a = {{0,0,0,1},{0,0,2,0},{0,3,0,0},{4,0,0,0}};
int main(){
    Matrix A(a);
    Matrix B = A.FindInverse();
    std::cout << B <<std::endl;
}
/*
clang++ -std=c++20 -O0 -Wall -Wextra -Werror -pedantic  -Iincludes -o ./bin/exec ./src/testprepare.cc ./src/matrix.cc
*/