#include "matrix.hpp"

size_t maxvalue_sizet = std::numeric_limits<size_t>::max();
Matrix::Matrix(){
  height_ = 1;
  width_ = 1;
  std::vector<std::vector<double>> unit = {{1}};
  entries = unit;
}

Matrix::Matrix(size_t n){
  height_ = n;
  width_ = n;
  std::vector<std::vector<double>> identity;
  for(size_t i = 0; i < height_; i ++){
    std::vector<double> tmp;
    for(size_t j = 0; j < width_; j ++){
      if(i == j){
        tmp.push_back(1.0);
      }else{
        tmp.push_back(0.0);
      }
    }
    identity.push_back(tmp);
  }
  entries = identity;
}

Matrix::Matrix(int n, int i, int j, double value){
  Matrix tmpI(n);
  std::vector<std::vector<double>> entries_tmp = tmpI.GetEntries();
  entries_tmp[i][j] = value;
  entries = entries_tmp;
  height_ = n;
  width_ = n;
}

Matrix::Matrix(std::vector<std::vector<double>>& entries_input){
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

double Matrix::GetEntry(size_t row, size_t column) const{
  if(row < 0 || row >= height_){
    throw std::runtime_error("row not in correct range");
  }

  if(column < 0 || column >= width_){
    throw std::runtime_error("column not in correct range");
  }

  return entries[row][column];
}

std::vector<std::vector<double>>& Matrix::GetEntriesReference(){
  return entries;
}

std::vector<std::vector<double>> Matrix::GetEntries() const{
  return entries;
}

Matrix Matrix::operator+ (const Matrix& m){
  if(height_ != m.GetHeight() || width_ != m.GetWidth()){
    throw std::runtime_error("height or width is not the same");
  }
  std::vector<std::vector<double>> sum;
  for(size_t i = 0; i < height_; i++){
    std::vector<double> s;
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
  std::vector<std::vector<double>> difference;
  for(size_t i = 0; i < height_; i++){
    std::vector<double> d;
    for(size_t j = 0; j < width_; j++){
      d.push_back(GetEntry(i,j) - m.GetEntry(i,j));
    }
    difference.push_back(d);
  }
  Matrix Difference(difference);
  return Difference;
}

Matrix Matrix::operator * (double scalar){
  std::vector<std::vector<double>> product;
  for(size_t i = 0; i < height_; i++){
    std::vector<double> p;
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
  std::vector<std::vector<double>> product;
  for(size_t i = 0; i < GetHeight(); i++){
    std::vector<double> p;
    for(size_t j = 0; j < m.GetWidth(); j++){
      double sum = 0;
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
      os << m.GetEntry(i,j) << " ";
    }
    os << std::endl;
  }
  return os;
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

double Matrix::FindDeterminant(){
  return FindDeterminant(*this);
}

double Matrix::FindDeterminant(const Matrix& m){
  if(m.GetHeight() != m.GetWidth()){
    throw std::runtime_error("Determinant is undefined for non-square matrices");
  }

  //Base case 
  if(m.GetHeight() == 1 && m.GetWidth() == 1){
    return m.GetEntry(0,0);
  }

  //Find the determinant base on Laplace expansion: https://en.wikipedia.org/wiki/Laplace_expansion
  double determinant = 0;
  for(size_t i = 0; i < m.GetWidth(); i++){
    double coefficient = m.GetEntry(0,i);
    if(i % 2 == 1){
      coefficient = coefficient * (-1);
    }
    Matrix tmp = removeRowColumn(m,0,i);
    double sub_determinant = coefficient * FindDeterminant(tmp);
    determinant = determinant + sub_determinant;
  }
  return determinant;
}

Matrix Matrix::removeRowColumn(const Matrix& m, size_t row, size_t col){
  std::vector<std::vector<double>> new_entries;
  for(size_t i = 0; i < m.GetHeight(); i++){
    if(i != row){
      std::vector<double> tmp;
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

void Matrix::row_swap(std::vector<double>& v1,std::vector<double>& v2){
  std::vector<double>& tmp = v1;
  v1 = v2;
  v2 = tmp;
}

size_t Matrix::FindBestPivot(size_t col){
  for(size_t i = 0; i < GetHeight(); i ++){
    size_t j = 0;
    while(true){
      if(j == col){
        //std::cout << "i: " << i <<std::endl;
        return i;
      }

      if(GetEntry(i,j) != 0){
        break;
      }
      j++;
    }
  }
  return maxvalue_sizet;
}

Matrix Matrix::FindRREF(){
  std::vector <std::vector<double>>& m_entries  = GetEntriesReference();
  for(size_t j = 0; j < GetWidth(); j++){
    size_t row = FindBestPivot(j);
    if(row == maxvalue_sizet){
      break;
    }
    row_swap(m_entries[j],m_entries[row]);
    for(size_t i = 0; i < GetHeight(); i++){
      if(i != row && m_entries[row][j] != 0){
          double factor = m_entries[i][j] / m_entries[row][j];
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
    double factor = 1 / m_entries[i][j];
    m_entries[i] = m_entries[i] * factor;
  }
  return *this;
}

Matrix Matrix::FindInverse(){
  Matrix I = Matrix(GetHeight());
  std::vector <std::vector<double>> m_entries  = GetEntries();
  std::vector<std::vector<double>>& I_entries = I.GetEntriesReference();
  for(size_t i = 1; i < GetHeight(); i ++){
    for(size_t j = 0; j < i; j ++){
      if(m_entries[i][j] != 0){
        double factor = (-1) * m_entries[i][j] / m_entries[j][j];
        m_entries[i] = m_entries[i] + (m_entries[j] * factor);
        I_entries[i] = I_entries[i] + (I_entries[j] * factor);
      }
    }
  }

  for(size_t i = GetHeight() - 2; i < GetHeight() ; i--){
    for(size_t j = i + 1; j < GetHeight(); j++){
      if(m_entries[i][j] != 0){
        std::cout << *this <<std::endl;
        std::cout << I << std::endl;
        double factor = (-1) * m_entries[i][j] / m_entries[j][j];
        m_entries[i] = m_entries[i] + (m_entries[j] * factor);
        I_entries[i] = I_entries[i] + (I_entries[j] * factor);
      }
    }
  }
  
  for(size_t i = 0; i < GetHeight(); i ++){
    double factor = 1.0 / m_entries[i][i];
    m_entries[i] = m_entries[i] * factor;
    I_entries[i] = I_entries[i] * factor;
  }

  return I;
}

Matrix Matrix::FindTranspose(){
  std::vector<std::vector<double>> result;
  for(size_t i = 0; i < GetWidth(); i++){
    std::vector<double> tmp;
    for(size_t j = 0; j < GetHeight(); j++){
      tmp.push_back(GetEntry(j,i));
    }
    result.push_back(tmp);
  }
  Matrix M(result);
  return M;
}

std::vector<Matrix> Matrix::FindElementaryMatrics(){
  std::vector<Matrix> result;
  std::vector <std::vector<double>> m_entries  = GetEntries();
  for(size_t i = 1; i < GetHeight(); i ++){
    for(size_t j = 0; j < i; j ++){
      if(m_entries[i][j] != 0){
        double factor = (-1) * m_entries[i][j] / m_entries[j][j];
        m_entries[i] = m_entries[i] + (m_entries[j] * factor);
        Matrix e(GetHeight(),i,j,factor);
        result.push_back(e);
      }
    }
  }
  return result;
}

Matrix Matrix::FindL(){
  std::vector<Matrix> Matrices = FindElementaryMatrics();
  Matrix result(GetHeight());
  for(size_t i = 0; i < Matrices.size(); i ++){
    Matrix tmp = Matrices[i].FindInverseElementary();
    result = result * tmp;
  }
  return result;
}

Matrix Matrix::FindU(){
  std::vector <std::vector<double>> m_entries  = GetEntries();
  for(size_t i = 1; i < GetHeight(); i ++){
    for(size_t j = 0; j < i; j ++){
      if(m_entries[i][j] != 0){
        double factor = (-1) * m_entries[i][j] / m_entries[j][j];
        m_entries[i] = m_entries[i] + (m_entries[j] * factor);
      }
    }
  }
  Matrix M(m_entries);
  return M;
}

std::pair<Matrix,Matrix> Matrix::FindLU(){
  Matrix L = FindL();
  Matrix U = FindU();
  std::pair<Matrix,Matrix> result;
  result.first = L;
  result.second = U;
  return result;
}

Matrix Matrix::FindInverseElementary(){
  std::vector<std::vector<double>> result = GetEntries();
  for(size_t i = 0; i < GetHeight(); i++){
    for(size_t j = 0; j < i; j ++){
      if(GetEntry(i,j) != 0){
        result[i][j] = (-1) * GetEntry(i,j);
      }
    }
  } 
  Matrix tmp(result);
  return tmp;
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

std::vector<double> operator * (std::vector<double> row, double scaler){
  std::vector<double> result;
  for(size_t i = 0; i < row.size(); i++){
    result.push_back(row[i] * scaler);
  }
  return result;
}

std::vector<double> operator + (std::vector<double> row1, std::vector<double> row2){
  std::vector<double> result;
  for(size_t i = 0; i < row1.size(); i++){
    double tmp = row1[i] + row2[i];
    result.push_back(tmp);
  }
  return result;
}

std::ostream& operator << (std::ostream& os, std::vector<double> row){
  for(size_t i = 0; i < row.size(); i ++){
    os << row[i] << " ";
  }
  return os;
}