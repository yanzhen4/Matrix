#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

#include "matrix.hpp"
#include "fraction.hpp"
/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

TEST_CASE( "Test Constructor and Reduction" ) {
   SECTION("Reduction needed"){
       Fraction f(10,40);
       REQUIRE( ((f.numerator == 1) && (f.denominator == 4)));
   }

   SECTION("Reduction needed"){
       Fraction f(49,21);
       REQUIRE( ((f.numerator == 7) && (f.denominator == 3)));
    }

    SECTION("Reduction Not needed"){
       Fraction f(37,51);
       REQUIRE( ((f.numerator == 37) && (f.denominator == 51)));
    }
}

TEST_CASE( "FindInverse" ) {
   SECTION("Inverse 1"){
       Fraction f(3,10);
       f = f.FindInverse();
       REQUIRE( ((f.numerator == 10) && (f.denominator == 3)) );
   }

   SECTION("Inverse 2"){
       Fraction f(49,21);
       f = f.FindInverse();
       REQUIRE( ((f.numerator == 3) && (f.denominator == 7)));
    }
}

TEST_CASE( "Addition and Subtraction" ) {
   SECTION("Simple Addition"){
       Fraction f1(3,10);
       Fraction f2(4,10);
       Fraction f = f1 + f2;
       REQUIRE( ((f.numerator == 7) && (f.denominator == 10)) );
   }

   SECTION("Addition"){
       Fraction f1(1,6);
       Fraction f2(1,3);
       Fraction f = f1 + f2;
       REQUIRE( ((f.numerator == 1) && (f.denominator == 2)) );
    }

    SECTION("Simple Subtraction"){
       Fraction f1(3,10);
       Fraction f2(4,10);
       Fraction f = f2 - f1;
       REQUIRE( ((f.numerator == 1) && (f.denominator == 10)) );
   }

   SECTION("Addition"){
       Fraction f1(1,6);
       Fraction f2(1,2);
       Fraction f = f2 - f1;
       REQUIRE( ((f.numerator == 1) && (f.denominator == 3)) );
    }
}

TEST_CASE( "Test FindDeterminant" ) {
    SECTION("1 by 1 Matrix"){
        Fraction f(1);
        std::vector<std::vector<double>> a = {{1}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == Fraction(1));
    }

    SECTION("2 by 2 Matrix 1"){
        std::vector<std::vector<double>> a = {{2,7},{8,3}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == Fraction(-50));
    }

    SECTION("2 by 2 Matrix 2"){
        std::vector<std::vector<double>> a = {{1,3},{-5,7}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == Fraction(22));
    }

    SECTION("3 by 3 Matrix 1"){
        std::vector<std::vector<double>> a = {{3,1,5},{5,4,5},{1,2,3}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == Fraction(26));
    }

    SECTION("3 by 3 Matrix 2"){
        std::vector<std::vector<double>> a = {{5,7,2},{3,4,8},{9,4,0}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == Fraction(296));
    }

    SECTION("6 by 6 Matrix 1"){
        std::vector<std::vector<double>> a = {{9,5,3,2,5,1},{0,-1,4,-2,9,10},{1,2,3,4,5,6},{0,0,3,2,1,6},{-1,0,1,9,8,7},{0,6,5,2,1,4}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == Fraction(2710));
    }
}

TEST_CASE("Find RREF"){
    SECTION("1 by 1 Matirx"){
        std::vector<std::vector<double>> a = {{1}};
        std::vector<std::vector<double>> b = {{1}};
        Matrix A(a);
        Matrix B(b);
        A = A.FindRREF();
        REQUIRE(A == B);
    }

    SECTION("2 by 2 Matrix 1"){
        std::vector<std::vector<double>> a = {{1,2},{3,4}};
        std::vector<std::vector<double>> b = {{1,0},{0,1}};
        Matrix A(a);
        Matrix B(b);
        A = A.FindRREF();
        REQUIRE(A == B);
    }

    SECTION("3 by 4 Matrix"){
        //Test Find RREF 3 by 4 matrix
        std::vector<std::vector<double>> a = {{4,5,6,0},{3,5,1,7},{-1,0,9,0}};
        Matrix A(a);
        A = A.FindRREF();
        //std::cout << A <<std::endl;
        REQUIRE(A.GetEntry(0,0) == 1);
        REQUIRE(A.GetEntry(1,1) == 1);
        REQUIRE(A.GetEntry(2,2) == 1);
    }

    SECTION("4 by 3 matrix"){
        //Test find RREF 4 by 3 matrix
        std::vector<std::vector<double>> a = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
        std::vector<std::vector<double>> b = {{1,0,-1},{0,1,2},{0,0,0},{0,0,0}};
        Matrix A(a);
        Matrix B(b);
        A = A.FindRREF();
        //std::cout << A <<std::endl;
        REQUIRE(A == B);
    }
}

TEST_CASE("Matrix LU Decomposition"){
    SECTION("3 * 3 matrix"){
        std::vector<std::vector<double>> a = {{5,12,-6},{-3,10,6},{-3,-12,8}};
        Matrix A(a);
        std::pair<Matrix,Matrix> LU = A.FindLU();
        //std::cout << LU.first <<std::endl;
        //std::cout << LU.second <<std::endl;
        std::vector<std::vector<Fraction>> l = {{Fraction(1),Fraction(0),Fraction(0)},{Fraction(-3,5),Fraction(1),Fraction(0)},{Fraction(-3,5),Fraction(-12,43),Fraction(1)}};
        std::vector<std::vector<Fraction>> u= {{Fraction(5),Fraction(12),Fraction(-6)},{Fraction(0),Fraction(86,5),Fraction(12,5)},{Fraction(0),Fraction(0),Fraction(218,43)}};
        Matrix L_expected(l);
        Matrix U_expected(u);
        REQUIRE(LU.first == L_expected);
        REQUIRE(LU.second == U_expected);
    }
}

TEST_CASE("FindSolution"){
    SECTION("3*3 Simple"){
        std::vector<std::vector<double>> a = {{2,0,-3},
                                              {-2,-1,5},
                                              {-2,-1,6}};
        std::vector<std::vector<double>> b = {{2},{3},{-1}};
        std::vector<std::vector<double>> x_expected = {{-5},{-13},{-4}};
        Matrix A(a);
        Matrix B(b);
        Matrix X = A.FindSolution(B);
        Matrix Xexpected(x_expected);
        REQUIRE(X == Xexpected);
    }
}