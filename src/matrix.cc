#include "matrix.hpp"

size_t maxvalue_sizet = std::numeric_limits<size_t>::max();
Matrix::Matrix(){
  height_ = 1;
  width_ = 1;
  
  std::vector<std::vector<Fraction>> unit = {{Fraction(1)}};
  entries = unit;
}

Matrix::Matrix(size_t n){
  height_ = n;
  width_ = n;
  std::vector<std::vector<Fraction>> identity;
  for(size_t i = 0; i < height_; i ++){
    std::vector<Fraction> tmp;
    for(size_t j = 0; j < width_; j ++){
      if(i == j){
        tmp.push_back(Fraction(1.0));
      }else{
        tmp.push_back(Fraction(0.0));
      }
    }
    identity.push_back(tmp);
  }
  entries = identity;
}

Matrix::Matrix(size_t n, size_t i, size_t j, Fraction value){
  Matrix tmpI(n);
  std::vector<std::vector<Fraction>> entries_tmp = tmpI.GetEntries();
  entries_tmp[i][j] = value;
  entries = entries_tmp;
  height_ = n;
  width_ = n;
}

Matrix::Matrix(std::vector<std::vector<Fraction>>& entries_input){
  initialize(entries_input);
}

Matrix::Matrix(std::vector<std::vector<double>>& entries_input){
  std::vector<std::vector<Fraction>> entries;
  for(size_t i = 0; i < entries_input.size(); i++){
    std::vector<Fraction> e;
    for(size_t j = 0; j < entries_input[0].size(); j++){
      e.push_back(Fraction(entries_input[i][j]));
    }
    entries.push_back(e);
  }
  initialize(entries);
}

void Matrix::initialize(std::vector<std::vector<Fraction>>& entries_input){
  height_ = entries_input.size();
  width_ = entries_input[0].size();
  entries = entries_input;
}


size_t Matrix::GetHeight() const{
  return height_;
}

size_t Matrix::GetWidth() const{
  return width_;
}

Fraction Matrix::GetEntry(size_t row, size_t column) const{
  if(row < 0 || row >= height_){
    throw std::runtime_error("row not in correct range");
  }

  if(column < 0 || column >= width_){
    throw std::runtime_error("column not in correct range");
  }

  return entries[row][column];
}

std::vector<std::vector<Fraction>>& Matrix::GetEntriesReference(){
  return entries;
}

std::vector<std::vector<Fraction>> Matrix::GetEntries() const{
  return entries;
}

std::vector<Fraction>& Matrix::GetRowReference(size_t row_idx){
  return entries[row_idx];
}

std::vector<Fraction> Matrix::GetRow(size_t row_idx){
  return entries[row_idx];
}

Matrix Matrix::operator+ (const Matrix& m){
  if(height_ != m.GetHeight() || width_ != m.GetWidth()){
    throw std::runtime_error("height or width is not the same");
  }
  std::vector<std::vector<Fraction>> sum;
  for(size_t i = 0; i < height_; i++){
    std::vector<Fraction> s;
    for(size_t j = 0; j < width_; j++){
      s.push_back(GetEntry(i,j) + m.GetEntry(i,j));
    }
    sum.push_back(s);
  }
  Matrix Sum(sum);
  return Sum;
}

Matrix Matrix::operator- (const Matrix& m){
  if(height_ != m.GetHeight() || width_ != m.GetWidth()){
    throw std::runtime_error("height or width is not the same");
  }
  std::vector<std::vector<Fraction>> difference;
  for(size_t i = 0; i < height_; i++){
    std::vector<Fraction> d;
    for(size_t j = 0; j < width_; j++){
      d.push_back(GetEntry(i,j) - m.GetEntry(i,j));
    }
    difference.push_back(d);
  }
  Matrix Difference(difference);
  return Difference;
}

Matrix Matrix::operator * (double scalar){
  return (*this) * Fraction(scalar);
}

Matrix Matrix::operator* (Fraction scalar){
  std::vector<std::vector<Fraction>> product;
  for(size_t i = 0; i < height_; i++){
    std::vector<Fraction> p;
    for(size_t j = 0; j < width_; j++){
      p.push_back(GetEntry(i,j)*scalar);
    }
    product.push_back(p);
  }
  Matrix Product(product);
  return Product;
}

Matrix Matrix::operator* (const Matrix& m){
  if(GetWidth() != m.GetHeight()){
    throw std::runtime_error("width of first matrix does not match the height of the second matrix");
  }
  std::vector<std::vector<Fraction>> product;
  for(size_t i = 0; i < GetHeight(); i++){
    std::vector<Fraction> p;
    for(size_t j = 0; j < m.GetWidth(); j++){
      Fraction sum = 0;
      for(size_t k = 0; k < GetWidth(); k++){
        sum = sum + GetEntry(i,k) * m.GetEntry(k,j);
        //std::cout << GetEntry(i,k) * m.GetEntry(k,j) << " + ";
      }
      //std::cout << "||";
      p.push_back(sum);
    }
    //std::cout << std::endl;
    product.push_back(p);
  }
  Matrix Product(product);
  return Product;
}

std::ostream& operator << (std::ostream& os, Matrix& m){
  os << m.GetHeight() << " row(s)" << std::endl;
  os << m.GetWidth() << " column(s)" << std::endl;
  for(size_t i = 0; i < m.GetHeight(); i++){
    for(size_t j = 0; j< m.GetWidth(); j++){
      os << m.GetEntry_toString(i,j) << " ";
    }
    os << std::endl;
  }
  return os;
}

std::string Matrix::GetEntry_toString(size_t row, size_t column) const{
  return (GetEntry(row,column).toString());
}

bool Matrix::IsIdentity(){
   if(GetHeight() != GetWidth()){
     return false;
   }
   for(size_t i = 0; i < GetHeight(); i++){
     if(GetEntry(i,i) != 1.0){
       return false;
     }
   }
   return true;
 }

Fraction Matrix::FindDeterminant(){
  return FindDeterminant(*this);
}

Fraction Matrix::FindDeterminant(const Matrix& m){
  if(m.GetHeight() != m.GetWidth()){
    throw std::runtime_error("Determinant is undefined for non-square matrices");
  }

  //Base case 
  if(m.GetHeight() == 1 && m.GetWidth() == 1){
    return m.GetEntry(0,0);
  }

  //Find the determinant base on Laplace expansion: https://en.wikipedia.org/wiki/Laplace_expansion
  Fraction determinant;
  for(size_t i = 0; i < m.GetWidth(); i++){
    Fraction coefficient = m.GetEntry(0,i);
    if(i % 2 == 1){
      coefficient = coefficient * (-1);
    }
    Matrix tmp = removeRowColumn(m,0,i);
    Fraction sub_determinant = coefficient * FindDeterminant(tmp);
    determinant = determinant + sub_determinant;
  }
  return determinant;
}

Matrix Matrix::removeRowColumn(const Matrix& m, size_t row, size_t col){
  std::vector<std::vector<Fraction>> new_entries;
  for(size_t i = 0; i < m.GetHeight(); i++){
    if(i != row){
      std::vector<Fraction> tmp;
      for(size_t j = 0; j < m.GetWidth(); j++){
        if(j != col){
          tmp.push_back(m.GetEntry(i,j));
        }
      }
      new_entries.push_back(tmp);
    }
  }
  Matrix new_matrix(new_entries);
  return new_matrix;
}

void Matrix::row_swap(std::vector<Fraction>& v1,std::vector<Fraction>& v2){
  if(v1 == v2){
    return;
  }

  std::vector<Fraction> tmp = v1;
  v1 = v2;
  v2 = tmp;
}

size_t Matrix::FindMatrixBestPivot(size_t col){
  return FindBestPivotrow(GetEntriesReference(), col);
}

Matrix Matrix::FindRREF(){
  std::vector <std::vector<Fraction>>& m_entries  = GetEntriesReference();
  for(size_t j = 0; j < GetWidth(); j++){
    size_t row = FindMatrixBestPivot(j);
    if(row == maxvalue_sizet){
      break;
    }
    row_swap(m_entries[j],m_entries[row]);
    for(size_t i = 0; i < GetHeight(); i++){
      if(i != row && m_entries[row][j] != 0){
          Fraction factor = m_entries[i][j] / m_entries[row][j];
          factor = factor * (-1);
          m_entries[i] = m_entries[i] + m_entries[row] * factor;
      }  
    }
    std::cout << std::endl;
  }

  //Turn pivot position 
  for(size_t i = 0; i < GetHeight(); i++){
    size_t j = 0;
    while(m_entries[i][j] == 0){
      j++;
    }
    Fraction factor = 1 / m_entries[i][j];
    m_entries[i] = m_entries[i] * factor;
  }
  return *this;
}

Matrix Matrix::FindTranspose(){
  std::vector<std::vector<Fraction>> result;
  for(size_t i = 0; i < GetWidth(); i++){
    std::vector<Fraction> tmp;
    for(size_t j = 0; j < GetHeight(); j++){
      tmp.push_back(GetEntry(j,i));
    }
    result.push_back(tmp);
  }
  Matrix M(result);
  return M;
}

Matrix Matrix::FindL(){
  std::pair<Matrix,Matrix> LU = FindLU();
  return LU.first;
}

Matrix Matrix::FindU(){
  std::pair<Matrix,Matrix> LU = FindLU();
  return LU.second;
}

/*
  Swap Count used for calculating determinant
  Theoren: If B is the matrix obtained by interchange any two ros of A, then detB = -detA
  So, if swap_count%2 == 1, we need to multiply the det of U to get the correct det of A
  */ 
std::pair<Matrix,Matrix> Matrix::FindLU(){
  std::vector <std::vector<Fraction>> m_entries  = GetEntriesReference();
  Matrix L(m_entries.size());
  std::vector <std::vector<Fraction>>& l_entries  = L.GetEntriesReference();

  int swap_count = 0;
  for(size_t j = 0; j < GetWidth(); j++){
    size_t row = FindBestPivotrow(m_entries, j);
    if(row == maxvalue_sizet){
      continue; // The column is free
    } 
    if(j != row){
      row_swap(m_entries[j],m_entries[row]);
      row_swap(l_entries[j],l_entries[row]);
      swap_count ++;
    }
    for(size_t i = j + 1; i < GetHeight(); i++){
      if(m_entries[i][j] != 0){
          Fraction factor = m_entries[i][j] / m_entries[j][j];
          factor = factor * (-1);
          m_entries[i] = m_entries[i] + m_entries[j] * factor;
          l_entries[i][j] = factor * (-1);
      }
    }
  } 
  std::cout << "Swap row " << swap_count << " times " <<std::endl;

  std::pair<Matrix,Matrix> LU;
  LU.first = L;
  LU.second = Matrix(m_entries);
  return LU;
}

//Current Cannot handle case when this matrix do not have an inverse 
Matrix Matrix::FindSolution(Matrix B){
  std::vector<Fraction> x;
  Matrix Inverse = FindInverse();
  Matrix solution = Inverse * B;
  return solution;
}

Matrix Matrix::FindInverse(){
  std::vector <std::vector<Fraction>> m_entries  = GetEntriesReference();
  Matrix Inverse(m_entries.size());
  std::vector <std::vector<Fraction>>& i_entries  = Inverse.GetEntriesReference();

  int swap_count = 0;
  for(size_t j = 0; j < GetWidth(); j++){
    size_t row = FindMatrixBestPivot(j);
    if(row == maxvalue_sizet){
      continue; // The column is free
    } 
    if(j != row){
      row_swap(m_entries[j],m_entries[row]);
      row_swap(i_entries[j],i_entries[row]);
      swap_count ++;
    }
    for(size_t i = j + 1; i < GetHeight(); i++){
      if(m_entries[i][j] != 0){
          Fraction factor = m_entries[i][j] / m_entries[j][j];
          factor = factor * (-1);
          m_entries[i] = m_entries[i] + m_entries[j] * factor;
          i_entries[i] = i_entries[i] + i_entries[j] * factor;
      }
    }
  } 
  Matrix U(m_entries);
  for(size_t col = GetWidth() - 1; col < GetWidth() && col >=0; col--){
    size_t pivot_col = col;
    Fraction pivot_val = m_entries[col][col]; 
    for(size_t row = 0; row < col; row++){
       Fraction factor = m_entries[row][col] / pivot_val;
       factor = factor * (-1);
       m_entries[row] = m_entries[row] + factor * m_entries[pivot_col];
       i_entries[row] = i_entries[row] + factor * i_entries[pivot_col];
    }
  }

  for(size_t row = 0; row < GetHeight(); row++){
    Fraction factor = Fraction(1) / m_entries[row][row];
    m_entries[row][row] = 1;
    //m_entries[row][row] = m_entries[row][row] * factor;
    i_entries[row] = i_entries[row] * factor;
  }

  return Inverse;
}

size_t FindBestPivotrow(std::vector<std::vector<Fraction>>& entries, size_t col){
  for(size_t i = col; i < entries.size(); i ++){
     if(entries[i][col].numerator != 0){
       return i;
     }
  }
  return maxvalue_sizet;
}

void rowSwap_operation(size_t row1, size_t row2, Matrix L){
  std::vector<Fraction> tmp = L.GetEntriesReference()[row1];
  L.GetEntriesReference()[row1] = L.GetEntriesReference()[row2];
  L.GetEntriesReference()[row2] = tmp;
}

bool operator == (const Matrix& m1, const Matrix& m2){
  if(m1.GetHeight() != m2.GetHeight() || m1.GetWidth() != m2.GetWidth()){
    return false;
  }
  for(size_t i = 0; i < m1.GetHeight(); i++){
    for(size_t j = 0; j< m1.GetWidth(); j++){
      if(m1.GetEntry(i,j) != m2.GetEntry(i,j)){
        return false;
      }
    }
  }
  return true;
}

std::vector<Fraction> operator * (std::vector<Fraction> row, Fraction scaler){
  std::vector<Fraction> result;
  for(size_t i = 0; i < row.size(); i++){
    result.push_back(row[i] * scaler);
  }
  return result;
}

std::vector<Fraction> operator * (Fraction scaler,std::vector<Fraction> row){
  std::vector<Fraction> result;
  for(size_t i = 0; i < row.size(); i++){
    result.push_back(row[i] * scaler);
  }
  return result;
}

std::vector<Fraction> operator + (std::vector<Fraction> row1, std::vector<Fraction> row2){
  std::vector<Fraction> result;
  for(size_t i = 0; i < row1.size(); i++){
    Fraction tmp = row1[i] + row2[i];
    result.push_back(tmp);
  }
  return result;
}

std::ostream& operator << (std::ostream& os, std::vector<Fraction> row){
  for(size_t i = 0; i < row.size(); i ++){
    os << row[i].toString() << " ";
  }
  return os;
}