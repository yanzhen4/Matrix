#include "matrix.hpp"
//aware of const
std::vector<std::vector<double>> a = {{2,7},{8,3}};
int main(){
  std::vector<std::vector<double>> a = {{1}};
  std::vector<std::vector<double>> b = {{1}};
  Matrix A(a);
  Matrix B(b);
  A = A.FindRREF();
  if(A == B){
    std::cout << "A and B are equal" <<std::endl;
  }else{
    std::cout << "A and B are not equal" <<std::endl;
  }
  /*
  //Test FindU
  Matrix M(m);
  Matrix U = M.FindU();
  std::cout << U <<std::endl;
  std::cout << "1" <<std::endl;
  */
  /*
  //Test theorem L^(-1) U^(-1) = A^(-1)
  std::vector<std::vector<double>> m = {{2,1,1},{4,-6,0},{-2,7,2}};
  std::vector<std::vector<double>> linverse = {{1,0,0},{-2,1,0},{-1,1,1}};
  std::vector<std::vector<double>> u = {{2,1,1},{0,-8,-2},{0,0,1}};
  Matrix LInverse (linverse);
  Matrix U (u);
  Matrix M (m);
  Matrix MInverse = M.FindInverse();
  Matrix UInverse = U.FindInverse();
  Matrix L = LInverse.FindInverse();
  std::cout << "L Inverse: " << LInverse <<std::endl;
  std::cout << "U Inverse: " << UInverse <<std::endl;
  Matrix MInverse2 = UInverse * LInverse;
  std::cout << "M Invsere1: "<< MInverse <<std::endl;
  std::cout << "M Inverse2" << MInverse2 <<std::endl; 
  */

  /*
  //Test FindL
  std::vector<std::vector<double>> m = {{2,1,1},{4,-6,0},{-2,7,2}};
  Matrix M(m);
  Matrix L = M.FindL();
  std::cout << L <<std::endl;
  */

  /*
  //Test FindElementary Matrices
  std::vector<std::vector<double>> m = {{2,1,1},{4,-6,0},{-2,7,2}};
  Matrix M(m);
  std::vector<Matrix> Matrices = M.FindElementaryMatrics();
  for(size_t i = 0; i < Matrices.size(); i ++){
    std::cout << Matrices[i] <<std::endl;
  }
  */

  /*
  //Test FindInverseElementary
  std::vector<std::vector<double>> e = {{1,0,0},{2,1,0},{0,0,1}};
  Matrix E(e);
  Matrix EInverse = E.FindInverseElementary();
  std::cout << EInverse <<std::endl;  
  */

  /*
  //Test FindTranpose 
  Matrix A(a);
  Matrix AInverse = A.FindInverse();
  Matrix ATranspose = A.FindTranspose();
  std::cout << "Transpose of A " << ATranspose <<std::endl;
  */

  /*
  //Test Product  
  Matrix A(a);
  Matrix M(m);
  Matrix AMProduct = A * M;
  std::cout << AMProdut <<std::endl;
  */
  return 0;
}

//clang++ -std=c++20 -O0 -Wall -Wextra -Werror -pedantic  -Iincludes -o ./bin/exec ./src/main.cc ./src/matrix.cc