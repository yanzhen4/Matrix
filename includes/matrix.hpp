#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <limits>

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
     * @brief Construct a new Matrix object
     * @param entries_input a two-dimensional vector containing all the values in the matrix
     */

    Matrix(std::vector<std::vector<double>>& entries_input);
    /**
     * @brief Construct a new Elementary Matrix object
     * @param n the size of the matrix
     * @param i the row number of value
     * @param j the column number of value
     * @param value the value 
     */
    Matrix(int n, int i, int j, double value);

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
      * @return the value at that entry 
      */
    double GetEntry(size_t row, size_t column) const;

    /**
     * @brief Get the Entries of matrix, pass by reference
     * @return entries of the matrix, pass by reference 
     */
    std::vector<std::vector<double>>& GetEntriesReference();


    std::vector<std::vector<double>> GetEntries() const;

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
     * @brief Find L U in A = LU
     * 
     * @return std::pair<Matrix,Matrix> L, U
     */
    std::pair<Matrix,Matrix> FindLU();

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
     * @brief Base on A = LU, get unique LU base on A
     * L is an lower tirangle matrix, U is an upper triangle matrix (after forward elimination)
     * @return std::pair<Matrix,Matrix> 
     */
    std::pair<Matrix,Matrix> FactorizationLU();

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
    double FindDeterminant();


    /**
     * @brief Find Determinant of matrix m
     * 
     */
    double FindDeterminant(const Matrix& m);

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

  private:
    /** the height of the matrix (the number of rows)*/
    size_t height_;

    /** the width_ of the matrix(the number of columns)*/
    size_t width_; 

    /** the entries of the matrix, the content of the matrix*/
    std::vector<std::vector<double>> entries;

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
    size_t FindBestPivot(size_t col);
    
    /**
     * @brief swap two vectors v1 and v2
     * 
     * @param v1 first vector
     * @param v2 second vector
     */
    void row_swap(std::vector<double>& v1, std::vector<double>& v2);
};

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
std::vector<double> operator + (std::vector<double> row1, std::vector<double> row2);

/**
 * @brief Overload insertion operator 
 * 
 * @param os the stream to insert into 
 * @param row the vector that is inserted 
 * @return std::ostream& 
 */
std::ostream& operator << (std::ostream& os, std::vector<double> row);

/**
 * @brief multiplication operator 
 * 
 * @param row the vector that was multiplied 
 * @param scaler the scalar 
 * @return std::vector<double> 
 */
std::vector<double> operator * (std::vector<double> row, double scaler); 