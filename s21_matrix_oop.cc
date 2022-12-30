#include "s21_matrix_oop.h"

/*============ сonstructors ===========*/

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (!this->checkRowsAndCols()) {
    throw std::out_of_range("Size error.");
  } else {
    Create();
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_) {
  Copy(other);
  Clean(other);
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {      //почиатть хабр move constructor
  Copy(other);
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    Clean(*this);
  }
}

/*=========== private functions ===========*/

void S21Matrix::Create() {
  matrix_ = new double *[rows_]();
  for (int i(0); i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_]();
    } catch (...) {
      int j(0);
      while (j < i) {
        delete[] matrix_[j];
        j++;
      }
      delete[] matrix_;
      throw;
    }
  }
}

void S21Matrix::Copy(const S21Matrix &o) {
  if (o.cols_ > 0 && o.rows_ > 0) {
    cols_ = o.cols_;
    rows_ = o.rows_;
    Create();
    for (int i(0); i < rows_; i++) {
      for (int j(0); j < cols_; j++) {
        matrix_[i][j] = o.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::Clean(S21Matrix &o) noexcept {
  for (int i(0); i < o.rows_; i++) {
    delete[] o.matrix_[i];
  }
  delete[] o.matrix_;
}

/*=========== public functions ===========*/

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->countRowsAndCols(other) == 1) {
    throw std::out_of_range("Size error: sizes are not equal.");
  } else {
    for (int i(0); i < rows_; i++) {
      for (int j(0); j < cols_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->countRowsAndCols(other) == 1) {
    throw std::out_of_range("Size error: sizes are not equal.");
  } else {
    for (int i(0); i < rows_; i++) {
      for (int j(0); j < cols_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i(0); i < rows_; i++) {
    for (int j(0); j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  S21Matrix res(other.rows_, cols_);
  if (this->cols_ != other.rows_) {
    throw std::out_of_range(
        "Size error: different sizes of a.column and b.rows");
  } else {
    for (int i(0); i < rows_; i++) {
      for (int j(0); j < other.cols_; j++) {
        res(i, j) = 0;
        for (int k = 0; k < cols_; k++) {
          res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
  }
  Clean(*this);
  this->Copy(res);  // clean a matrix and copy res
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool res = true;
  if (this->countRowsAndCols(other) == 1) {
    throw std::out_of_range("Matrices are not equal: different size");
  } else {
    for (int i(0); i < rows_; i++) {
      for (int j(0); j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= edge_) {
          res = false;
          break;
        }
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i(0); i < rows_; i++) {
    for (int j(0); j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

double S21Matrix::Determinant() const {  // для 4*4 неправильно считает
  double res = 0, flag = 0, res_tmp = 0;
  if (this->cols_ != this->rows_) {
    throw std::out_of_range("Size error. Rows and cols aren\'t equal");
  } else {
    if (rows_ == 1) {
      res = this->matrix_[0][0];
    } else if (rows_ == 2) {
      res = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
    } else {
      double sign = 1;
      for (int j(0); j < cols_; j++) {
        S21Matrix tmp = Minor(0, j);
        flag = tmp.Determinant();
        sign = pow((-1), j + 2);
        res_tmp += sign * matrix_[0][j] * flag;
      }
      res = res_tmp;
    }
  }
  return res;
}

S21Matrix S21Matrix::Minor(int r, int c) const {
  int minor_col = 0, minor_row = 0, flag = 0;
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i(0); i < rows_; i++) {
    for (int j(0); j < cols_; j++) {
      if (i != r && j != c) {
        minor.matrix_[minor_row][minor_col] = matrix_[i][j];
        minor_col++;
        flag = 1;
      }
    }
    if (flag == 1) {
      minor_row++;
      minor_col = 0;
      flag = 0;
    }
  }
  return minor;
}

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix res(rows_, cols_);
  double res_minor = 0;
  if (this->cols_ != this->rows_) {
    throw std::out_of_range("Size error. Rows and cols aren\'t equal");
  } else {
    if (this->rows_ == 1) {
      res.matrix_[0][0] == this->matrix_[0][0];
    } else {
      for (int i(0); i < rows_; i++) {
        for (int j(0); j < cols_; j++) {
          S21Matrix minor = Minor(i, j);
          res_minor = minor.Determinant();
          int sign = pow((-1), j + i);
          res.matrix_[i][j] = sign * res_minor;
        }
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix res(rows_, cols_);
  double d = this->Determinant();
  if (std::fabs(d) < this->edge_) {  //?
    throw std::out_of_range("Error. Determinant is 0.");
  }
  if (cols_ == 1 && rows_ == 1) {
    res.matrix_[0][0] = 1 / this->matrix_[0][0];
  } else {
    // if (cols_ == 1 || rows_ == 1) {
    // 	res.Copy(*this);
    // } else {
    res = Transpose();
    res = res.CalcComplements();
    // }
    res.MulNumber(1.0 / d);
  }
  return res;
}

/*=========== operators ===========*/

S21Matrix S21Matrix::operator+(const S21Matrix &x) const {
  S21Matrix res(*this);
  res.SumMatrix(x);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &x) const {
  S21Matrix res(*this);
  res.SubMatrix(x);
  return res;
}

double &S21Matrix::operator()(const int i, const int j) {
  if ((i < 0 || j < 0) || (rows_ <= i || cols_ <= j)) {
    throw std::out_of_range("Error. Index out of range");
  }
  return matrix_[i][j];  // index matrix(i,j)
}

// const double &S21Matrix::operator()(const int i, const int j) const {
//   if ((i < 0 || j < 0) || (rows_ <= i || cols_ <= j)) {
//     throw std::out_of_range("Error. Index out of range");
//   }
//   return matrix_[i][j];
// }

S21Matrix S21Matrix::operator*(double x) {
  S21Matrix res(*this);
  res.MulNumber(x);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &x) const {
  S21Matrix res(*this);
  res.MulMatrix(x);
  return res;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&x) {
  Clean(*this);
  rows_ = x.rows_;
  cols_ = x.cols_;
  matrix_ = x.matrix_;

  x.cols_ = 0;
  x.rows_ = 0;
  x.matrix_ = nullptr;

  return *this;
}

bool S21Matrix::operator==(const S21Matrix &x) const {
  return this->EqMatrix(x);
}

S21Matrix &S21Matrix::operator*=(double x) {
  this->MulNumber(x);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &x) {
  this->MulMatrix(x);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &x) {
  this->SubMatrix(x);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &x) {
  this->SumMatrix(x);
  return *this;
}

/*=========== get-set (accessor-mutator) ===========*/

int S21Matrix::getRows() noexcept { return this->rows_; } //const

int S21Matrix::getCols() noexcept { return this->cols_; }

void S21Matrix::setCols(int cols_count) {
  if (cols_count <= 0) {
    throw std::out_of_range(
        "Error. Column\'s number can\'t be negative or zero value");
  } else if (cols_count != this->cols_) {
    Rebuild(cols_count, 0);
  }
  this->cols_ = cols_count;
}

void S21Matrix::setRows(int rows_count) {
  if (rows_count <= 0) {
    throw std::out_of_range(
        "Error. Column\'s number can\'t be negative or zero value");
  } else if (rows_count != this->cols_) {
    Rebuild(rows_count, 1);  // new should be zeros
  }
  this->rows_ = rows_count;
}

void S21Matrix::Rebuild(int counter, const int type) {
  int j_counter = 0, i_counter = 0;
  int flag = 0;
  if (type == 1) {
    i_counter = counter;
    j_counter = this->cols_;
  } else {
    i_counter = this->rows_;
    j_counter = counter;
    flag = 1;
  }
  double **tmp = new double *[counter];
  for (int i(0); i < i_counter; i++) {
    tmp[i] = new double[j_counter];
    for (int j(0); j < j_counter; j++) {
      if (flag == 1) {
        if (j < cols_) {
          tmp[i][j] = this->matrix_[i][j];
        } else {
          tmp[i][j] = 0;
        }
      } else {
        if (i < rows_) {
          tmp[i][j] = this->matrix_[i][j];
        } else {
          tmp[i][j] = 0;
        }
      }
    }
  }
  Clean(*this);
  this->matrix_ = tmp;
}

/*=========== for me ===========*/

int S21Matrix::countRowsAndCols(const S21Matrix &o) const {
  return (o.rows_ == rows_ && o.cols_ == cols_) ? 0 : 1;
}

bool S21Matrix::checkRowsAndCols() {
  return (rows_ > 0 && cols_ > 0) ? true : false;
}

void S21Matrix::printer() const {
  for (int i(0); i < rows_; i++) {
    for (int j(0); j < cols_; j++) {
      printf("%lf ", matrix_[i][j]);
    }
    printf("\n");
  }
}
