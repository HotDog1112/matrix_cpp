#ifndef S21_MATRIX_OOP_SRC_S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_SRC_S21_MATRIX_OOP_H_

static const double EDGE = 0.0000001;

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

  void Create();
  void Copy(const S21Matrix &other);
  void Clean() noexcept;
  void Rebuild(int counter, const int type);
  bool CountRowsAndCols(const S21Matrix &other) const;
  bool CheckRowsAndCols();

 public:
  /* Constructors */
  S21Matrix() noexcept;
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
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
  S21Matrix Minor(int rows, int cols) const;

  /* operators */
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  S21Matrix operator*(double num) const;
  double &operator()(const int rows, const int cols);
  const double &operator()(const int rows, const int cols) const;
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator=(S21Matrix &other);

  friend S21Matrix operator*(const double num, const S21Matrix &other);

  /* get-set - mutator and assessor */
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int rows_count);
  void SetCols(int cols_count);

  void Printer() const;
};

#endif
