#include "s21_matrix_oop.h"

/*============ сonstructors ===========*/

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (!CheckRowsAndCols()) {
    throw std::out_of_range("Size error.");
  }
  Create();
}

S21Matrix::S21Matrix(S21Matrix &&other) : rows_(0), cols_(0), matrix_(nullptr) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  Copy(other);
}

S21Matrix::~S21Matrix() { Clean(); }

/*=========== private functions ===========*/

void S21Matrix::Create() {
  matrix_ = new double *[rows_];
  for (int i(0); i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_];
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

void S21Matrix::Copy(const S21Matrix &other) {
  cols_ = other.cols_;
  rows_ = other.rows_;
  Create();
  for (int i(0); i < rows_; i++) {
    for (int j(0); j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::Clean() noexcept {
  if (matrix_) {
    for (int i(0); i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

/*=========== public functions ===========*/

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (CountRowsAndCols(other) == false || !CheckRowsAndCols()) {
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
  if (CountRowsAndCols(other) == false || !CheckRowsAndCols()) {
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
  S21Matrix res(rows_, other.cols_);
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "Size error: different sizes of a.column and b.rows");
  } else {
    for (int i(0); i < rows_; i++) {
      for (int j(0); j < other.cols_; j++) {
        res.matrix_[i][j] = 0;
        for (int k(0); k < cols_; k++) {
          res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
  }
  *this = std::move(res);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool res = true;
  if (CountRowsAndCols(other) == false) {
    return false;
  } else {
    for (int i(0); i < rows_; i++) {
      for (int j(0); j < cols_; j++) {
        double res_num = matrix_[i][j] - other.matrix_[i][j];
        if (std::abs(res_num) >= EDGE) {
          return false;
        }
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix res(cols_, rows_);
  for (int i(0); i < rows_; i++) {
    for (int j(0); j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

double S21Matrix::Determinant() const {
  double res = 0, flag = 0, res_tmp = 0;
  if (cols_ != rows_) {
    throw std::out_of_range("Size error. Rows and cols aren\'t equal");
  } else {
    if (rows_ == 1) {
      res = matrix_[0][0];
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

S21Matrix S21Matrix::Minor(int rows, int columns) const {
  int minor_col = 0, minor_row = 0, flag = 0;
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i(0); i < rows_; i++) {
    for (int j(0); j < cols_; j++) {
      if (i != rows && j != columns) {
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
  if (cols_ != rows_) {
    throw std::out_of_range("Size error. Rows and cols aren\'t equal");
  } else {
    if (rows_ == 1) {
      res.matrix_[0][0] = matrix_[0][0];  // 1-1 = 0, нельзя создать
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

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix res(rows_, cols_);
  double d = Determinant();
  if (std::fabs(d) < EDGE) {
    throw std::out_of_range("Error. Determinant is 0.");
  }
  if (cols_ == 1 && rows_ == 1) {
    res.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    res = Transpose();
    res = res.CalcComplements();
    res.MulNumber(1.0 / d);
  }
  return res;
}

/*=========== operators ===========*/

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

double &S21Matrix::operator()(const int rows, const int cols) {
  if ((rows < 0 || cols < 0) || (rows_ <= rows || cols_ <= cols)) {
    throw std::out_of_range("Error. Index out of range");
  }
  return matrix_[rows][cols];
}

const double &S21Matrix::operator()(const int rows, const int cols) const {
  if ((rows < 0 || cols < 0) || (rows_ <= rows || cols_ <= cols)) {
    throw std::out_of_range("Error. Index out of range");
  }
  return matrix_[rows][cols];
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    Clean();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &other) {
  if (this != &other) {
    Clean();
    Copy(other);
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator*=(double other) {
  MulNumber(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

/*=========== get-Set (accessor-mutator) ===========*/

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetCols(int cols_count) {
  if (cols_count < 0) {
    throw std::out_of_range(
        "Error. Column\'s number can\'t be negative or zero value");
  } else if (cols_count != cols_) {
    Rebuild(cols_count, 0);
  }
  cols_ = cols_count;
}

void S21Matrix::SetRows(int rows_count) {
  if (rows_count < 0) {
    throw std::out_of_range(
        "Error. Column\'s number can\'t be negative or zero value");
  }
  if (rows_count != rows_) {
    Rebuild(rows_count, 1);
  }
  rows_ = rows_count;
}

void S21Matrix::Rebuild(int counter, const int type) {
  int j_counter = 0, i_counter = 0;
  int flag = 0;
  if (type == 1) {
    i_counter = counter;
    j_counter = cols_;
  } else {
    i_counter = rows_;
    j_counter = counter;
    flag = 1;
  }
  S21Matrix tmp(i_counter, j_counter);
  for (int i(0); i < i_counter; i++) {
    for (int j(0); j < j_counter; j++) {
      if (flag == 1) {
        if (j < cols_) {
          tmp.matrix_[i][j] = matrix_[i][j];
        } else {
          tmp.matrix_[i][j] = 0;
        }
      } else {
        if (i < rows_) {
          tmp.matrix_[i][j] = matrix_[i][j];
        } else {
          tmp.matrix_[i][j] = 0;
        }
      }
    }
  }
  *this = std::move(tmp);
}

/*=========== for me ===========*/

bool S21Matrix::CountRowsAndCols(const S21Matrix &other) const {
  return (other.rows_ == rows_ && other.cols_ == cols_) ? true : false;
}

bool S21Matrix::CheckRowsAndCols() {
  return (rows_ >= 0 && cols_ >= 0) ? true : false;
}

void S21Matrix::Printer() const {
  for (int i(0); i < rows_; i++) {
    for (int j(0); j < cols_; j++) {
      printf("%lf ", matrix_[i][j]);
    }
    printf("\n");
  }
  printf("%d %d\n", rows_, cols_);
}
