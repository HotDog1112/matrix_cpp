#ifndef S21_MATRIX_OOP_H__
#define S21_MATRIX_OOP_H__

#include <iostream>
#include <cstring>
#include <cmath>

class S21Matrix {
    private:
        /* Attributes - свойства */
        int rows_, cols_;
        double **matrix_;
        double edge_ = 0.0000001;

        /* private functions to create, copy and remove matrix */
        void Create();
        void Copy(const S21Matrix& o);
        void Clean(S21Matrix& o) noexcept;

    public:
        /* Constructors */
        S21Matrix() noexcept;
        S21Matrix(int rows, int cols);
        S21Matrix(const S21Matrix& other);
        S21Matrix(S21Matrix&& other);
        ~S21Matrix();

        /* Methods */
        void SumMatrix(const S21Matrix& other);
        bool EqMatrix(const S21Matrix& other) const;
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num);
        void MulMatrix(const S21Matrix& other); 

        S21Matrix InverseMatrix();
        S21Matrix Transpose();
        S21Matrix CalcComplements();
        double Determinant();
        S21Matrix Minor(int r, int c);

        int countRowsAndCols(const S21Matrix& o) const;
        bool checkRowsAndCols();
    
        /* operators */
        S21Matrix operator+(const S21Matrix& x) const;
        S21Matrix operator-(const S21Matrix& x) const;
        S21Matrix operator*(const S21Matrix& x) const;
        bool operator==(const S21Matrix& x) const;
        S21Matrix& operator+=(const S21Matrix& x);
        S21Matrix& operator-=(const S21Matrix& x);
        S21Matrix& operator*=(const S21Matrix& x) const;
        S21Matrix& operator*=(double x);
        S21Matrix operator*(double x);
        double& operator()(const int i, const int j);
        S21Matrix& operator=(S21Matrix&& x);

        /* get-set - mutators, incapsulation example */
        int getRows() noexcept;
        int getCols() noexcept;
        void setRows(int rows_count);
        void setCols(int cols_count);
};

#endif

// https://ionian-haddock-769.notion.site/C-b1fd479eae9a4a638088d089f7d1bff9