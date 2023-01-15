#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <iostream>
#include <cstring>
#include <cmath>

#define EDGE 0.0000001

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

  void Create();
  void Copy(const S21Matrix &o);
  S21Matrix& Clean() noexcept;
  void Rebuild(int counter, const int type);
  bool CountRowsAndCols(const S21Matrix &o) const;
  bool CheckRowsAndCols();

 public:
  /* Constructors */
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  /* Methods */
  void SumMatrix(const S21Matrix &other);
  bool EqMatrix(const S21Matrix &other) const;
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);

  S21Matrix InverseMatrix() const;
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix Minor(int r, int c) const;

  /* operators */
  S21Matrix operator+(const S21Matrix &x) const;
  S21Matrix operator-(const S21Matrix &x) const;
  S21Matrix operator*(const S21Matrix &x) const;
  bool operator==(const S21Matrix &x) const;
  S21Matrix &operator+=(const S21Matrix &x);
  S21Matrix &operator-=(const S21Matrix &x);
  S21Matrix &operator*=(const S21Matrix &x);
  S21Matrix &operator*=(double x);
  S21Matrix operator*(double x);
  double &operator()(const int i, const int j);
  const double &operator()(const int i,
                           const int j) const;
  S21Matrix &operator=(S21Matrix &&x);
  S21Matrix &operator=(S21Matrix &x);

  /* get-set - mutator and assessor */
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows_count);
  void SetCols(int cols_count);

  void Printer() const;
};

#endif

// добавить перегрузку умножения числа на матрицу
