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

TEST_CASE( "Test FindDeterminant" ) {
    SECTION("1 by 1 Matrix"){
        std::vector<std::vector<double>> a = {{1}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == 1);
    }

    SECTION("2 by 2 Matrix 1"){
        std::vector<std::vector<double>> a = {{2,7},{8,3}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == -50);
    }

    SECTION("2 by 2 Matrix 2"){
        std::vector<std::vector<double>> a = {{1,3},{-5,7}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == 22);
    }

    SECTION("3 by 3 Matrix 1"){
        std::vector<std::vector<double>> a = {{3,1,5},{5,4,5},{1,2,3}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == 26);
    }

    SECTION("3 by 3 Matrix 2"){
        std::vector<std::vector<double>> a = {{5,7,2},{3,4,8},{9,4,0}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == 296);
    }

    SECTION("6 by 6 Matrix 1"){
        std::vector<std::vector<double>> a = {{9,5,3,2,5,1},{0,-1,4,-2,9,10},{1,2,3,4,5,6},{0,0,3,2,1,6},{-1,0,1,9,8,7},{0,6,5,2,1,4}};
        Matrix A(a);
        REQUIRE(A.FindDeterminant() == 2710);
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
        std::cout << A <<std::endl;
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
        std::cout << A <<std::endl;
        REQUIRE(A == B);
    }
}