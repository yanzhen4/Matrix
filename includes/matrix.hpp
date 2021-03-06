#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <limits>

#include "fraction.hpp"

class Matrix {
  public:
    /**
     * @brief Construct a new Matrix object
     * 1 *1 matrix with value 0
     */
    Matrix();
    /**
    * @brief Construct a new identity Matrix
    * 
    * @param n the size of the Matrix
    */
    Matrix(size_t n);

    /**
     * @brief Construct a new Matrix object using a vector of doubles
     * @param entries_input a two-dimensional vector containing all the values in the matrix
     */

    Matrix(std::vector<std::vector<double>>& entries_input);

    /**
     * @brief Construct a new Matrix objectusing a vector of Fractions
     * 
     * @param entries_input vector of Fractions
     */
    Matrix(std::vector<std::vector<Fraction>>& entries_input);

    /**
     * @brief Construct a new Elementary Matrix object
     * @param n the size of the matrix
     * @param i the row number of value
     * @param j the column number of value
     * @param value the value 
     */
    Matrix(size_t n, size_t i, size_t j, Fraction value);

    /**
     * @brief addition operator + 
     * Add two matrix of the same width and height together 
     * @param m matrix added to this matrix
     * @return Matrix after addition
     */
    Matrix operator+ (const Matrix& m); 

    /**
     * @brief subtraciton operator -
     * this matrix as the minuend
     * @param m the subtrahend
     * @return the difference of two matrix 
     */
    Matrix operator- (const Matrix& m);

    /**
     * @brief scalar operator
     * @param scalar factor of scaling
     * @return Matrix after scaling
     */
    Matrix operator* (double scalar);

    /**
     * @brief scalar product using scalaer
     * 
     * @param scalar a scalar as a fraction 
     * @return Matrix 
     */
    Matrix operator* (Fraction scalar);

    /**
     * @brief matrix multiplication operator
     * @param m the multiplicand
     * @return Matrix The product
     */
    Matrix operator* (const Matrix& m);

    /**
     * @brief insertion operator
     * @param os an ostream object
     * @param m a matrix to print
     * @return ostream& the ostrema object after inserting the matrix 
     */
    friend std::ostream& operator << (std::ostream& os, Matrix& m);

    /**
     * @brief Get the Height of this matrix
     * @return Height of this matrix
     */
    size_t GetHeight() const;

    /**
     * @brief Get the Width of this matrix
     * @return Width of this matrix 
     */
    size_t GetWidth() const;

    /**
      *The places in the matrix where the numbers are called entries
      * @param row the row number of the wanted entry
      * @param column the column number of the wanted entry
      * @return the Fraction at that entry 
      */
    Fraction GetEntry(size_t row, size_t column) const;

    /**
     * @brief Get the Entries of the matrix
     * 
     * @return std::vector<std::vector<Fraction>> 
     */
    std::vector<std::vector<Fraction>> GetEntries() const;

    /**
     * @brief Get the Entries of matrix, pass by reference
     * @return entries of the matrix, pass by reference 
     */
    std::vector<std::vector<Fraction>>& GetEntriesReference();

    /**
     * @brief Get a specific row of the index by reference
     * 
     * @param row_idx 
     * @return std::vector<Fraction> 
     */
    std::vector<Fraction>& GetRowReference(size_t row_idx);

     /**
     * @brief Get a specific row of the index
     * 
     * @param row_idx 
     * @return std::vector<Fraction> 
     */
    std::vector<Fraction> GetRow(size_t row_idx);

    /**
      * A identity matrix is a n * n matrix that has 1s on its pivot (main diagonal) and zeros else where 
      * @return whether this matrix is a identity matrix
      */
    bool IsIdentity(); 

    /**
     * @brief Find the list of the elementary matrices required to get the current matrix into REF from
     * 
     * @return std::vector<Matrix> 
     */
    std::vector<Matrix> FindElementaryMatrics();

    /**
     * @brief Find L U in A = LU
     * 
     * @return std::pair<Matrix,Matrix> L, U
     */
    std::pair<Matrix,Matrix> FindLU();

    /**
     * @brief Find L in A = LU
     * 
     * @return Matrix L
     */
    Matrix FindL();

    /**
     * @brief Find U in A = LU
     * 
     * @return Matrix U
     */
    Matrix FindU();

    /**
     * @brief Solve the system
     * 
     * @param b b in Ax = b
     * @return solution Matrix
     */
    Matrix FindMatrixSolution(Matrix B);

    /**
     * @brief Find the Elimination Matrices required to convert A to REF Form
     * @return std::vector<Matrix> the elimination matrices 
     */
    std::vector<Matrix> EliminationMatrices();
    
    /**
     * @brief pring out the description for the row operation for the matrix 
     * @param m the elimination matrix
     * @return std::string the description, for example:  3 * r1 + r4 
     */
    std::string EliminationMatrixtoString(const Matrix& m);

    /**
     * @brief Furthur divide U into U = DU'
     * where D diagonal matrix containing the matrix and U is an upper tirangular matrix with 1 at pivot position
     * @return std::vector<Matrix> 
     */
    std::vector<Matrix> FactorizationLDU();

    /**
     * @brief Find determinant of this matrix
     * 
     * @return double 
     */
    Fraction FindDeterminant();

    /**
     * @brief Find Determinant of matrix m
     * 
     */
    Fraction FindDeterminant(const Matrix& m);

    /**
     * @brief Find the RREF form of the matrix
     * 
     * @return Matrix in RREF Form
     */
    Matrix FindRREF();

    /**
     * @brief Find the Inverse of the matrix 
     * 
     * @return THe Inverse Matrix 
     */
    Matrix FindInverse();

    /**
     * @brief Simple Case: find the inverse matrix for an elementary matrix 
     * 
     * @return Inverse matrix of elementary Matrix 
     */
    Matrix FindInverseElementary();

    /**
     * @brief Find transpose of a matrix 
     * 
     * @return transpose of a matrix 
     */
    Matrix FindTranspose();

    /**
     * @brief Find the nullspace of the matrix
     * 
     * @return Matrix 
     */
    Matrix FindNullSpaceMatrix();

  private:
    /** the height of the matrix (the number of rows)*/
    size_t height_;

    /** the width_ of the matrix(the number of columns)*/
    size_t width_; 

    /** the entries of the matrix, the content of the matrix*/
    std::vector<std::vector<Fraction>> entries;

    /**
     * @brief initialize a new matrix, helper function of Matrix Constructor
     * 
     * @param entries_input 
     */
    void initialize(std::vector<std::vector<Fraction>>& entries_input);

    /**
     * @brief Helper function for FindDeterminant, return the matrix with ith row
     * and jth column removed 
     * @param m, the original matrix
     * @param i the row to be removed
     * @param j the column to be removed 
     * @return the new matrix 
     */
    Matrix removeRowColumn(const Matrix& m, size_t row, size_t col);

    /**
     * @brief Private function for FindRREF, find the best pivot row for column col
     * @param col which column
     * @return the best row 
     */
    size_t FindMatrixBestPivot(size_t col);
  
    /**
     * @brief return the Fraction in string, helper function of <<operator of the matrix class 
     * 
     * @param row 
     * @param column 
     * @return std::string 
     */
    std::string GetEntry_toString(size_t row, size_t column) const;

};

Matrix FindSolution(Matrix A, Matrix B);

/**
 * @brief Helpher function of FindSolution, find specific solution given U and c (Ux = c)
 * 
 * @param a_entries 
 * @param c_entries 
 * @return std::vector<Fraction> 
 */
std::vector<Fraction> FindSpecificSolution(std::vector<std::vector<Fraction>>& a_entries, std::vector<std::vector<Fraction>>& c_entries);

/**
 * @brief Helper function of FindSolution, check if the system is consistent
 * 
 * @param a_entries 
 * @param c_entries 
 * @return a bool value indicating whether the system is conistent
 */
bool CheckConsistent(std::vector<std::vector<Fraction>>& a_entries, std::vector<std::vector<Fraction>>& c_entries);

/**
  * @brief Store the specific solution and the general solution in a two dimensional vector
  * 
  * @param B 
  * @return std::vector<std::vector<Fraction>> 
  */
Matrix FindSolution(Matrix A, Matrix B);

/**
 * @brief Find the null space of a give null space A
 * 
 * @param A 
 * @return Matrix 
 */
Matrix FindNullSpace(Matrix A);

/**
 * @brief Swap two rows
 * 
 * @param entries1 
 * @param entries2 
 */
void rowSwap(std::vector<Fraction>& entries1, std::vector<Fraction>& entries2);

/**
 * @brief Find the upper most pivot row of the Matrix m with entries 
 * 
 * @param entries 
 * @param col 
 * @return size_t 
 */
size_t FindBestPivotrow(std::vector<std::vector<Fraction>>& entries, size_t col);

/**
  * @brief Equality operator
  * @param m other matrix to be checked
  * @return true if two matrix are identical
  * @return false if two matrix are not identitcal
  */
bool operator== (const Matrix& m1, const Matrix& m2);

/**
 * 
 * @brief Overload addition operator for vector : adding two vectors together 
 * 
 * @param row1 the first matrix 
 * @param row2 the second matrix 
 * @return std::vector<double> the sum of two matrices 
 */
std::vector<Fraction> operator + (std::vector<Fraction> row1, std::vector<Fraction> row2);

/**
 * @brief Overload insertion operator 
 * 
 * @param os 
 * @param row the vector that is inserted 
 * @return std::ostream& 
 */
std::ostream& operator << (std::ostream& os, std::vector<Fraction> row);

/**
 * @brief multiplication operator 
 * 
 * @param row the vector that was multiplied 
 * @param scaler the scalar 
 * @return std::vector<double> 
 */
std::vector<Fraction> operator * (std::vector<Fraction> row, Fraction scaler); 

/**
 * @brief multiplication operator 
 * 
 * @param row the vector that was multiplied 
 * @param scaler the scalar 
 * @return std::vector<double> 
 */
std::vector<Fraction> operator * (Fraction scaler,std::vector<Fraction> row); 