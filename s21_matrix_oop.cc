#include "s21_matrix_oop.h"

/*============ сonstructors ===========*/

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}    // init func, не выбрасывает исключение

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (!this->checkRowsAndCols()) {
        throw std::out_of_range("Size error.");
    } else {
        Create();
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.rows_), cols_(other.cols_) {
    Copy(other);
    Clean(other);
    other.cols_ = 0;
    other.rows_ = 0;
    // other.matrix_ = nullptr;
}

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    Copy(other);
}

S21Matrix::~S21Matrix() {
    if (matrix_) {
        Clean(*this);
    }
}

/*=========== private functions ===========*/

void S21Matrix::Create() {
    matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) {
        try {
            matrix_[i] = new double[cols_]();
        } catch (...) {     // при любом исключении чистим память, которая успела выделиться
            int j = 0;
            while (j < i) {
                delete[] matrix_[j];
                j++;
            }
            delete[] matrix_;
            throw;
        }
    }
}


void S21Matrix::Copy(const S21Matrix& o) {
    if (o.cols_ > 0 && o.rows_ > 0) {
        cols_ = o.cols_;
        rows_ = o.rows_;
        Create();
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] = o.matrix_[i][j];
            }
        }
    }
}

void S21Matrix::Clean(S21Matrix& o) noexcept {
    for (int i = 0; i < o.rows_; i++) {
        delete[] o.matrix_[i];
    }
    delete[] o.matrix_;
}

int S21Matrix::countRowsAndCols(const S21Matrix& o) const {
    return (o.rows_ == rows_ && o.cols_ == cols_) ? 0 : 1;
}

bool S21Matrix::checkRowsAndCols() {
    return (rows_ > 0 && cols_ > 0) ? true : false;
}

/*=========== public functions ===========*/

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (this->countRowsAndCols(other) == 1) {
        throw std::out_of_range("Size error: sizes are not equal.");
    } else {
        for (int i = 0; i< rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] += other.matrix_[i][j];
            }
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (this->countRowsAndCols(other) == 1) {
        throw std::out_of_range("Size error: sizes are not equal.");
    } else {
        for (int i = 0; i< rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                matrix_[i][j] -= other.matrix_[i][j];
            }
        }
    }
}

void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    S21Matrix res(other.rows_, cols_);
    if (this->cols_ != other.rows_) {
        throw std::out_of_range("Size error: different sizes of a.column and b.rows");
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < other.cols_; j++) {
                res(i,j) = 0;
                for (int k = 0; k < cols_; k++) {
                    res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
                }
            }
        }
    }
    Clean(*this);
    this->Copy(res);    // clean a matrix and copy res
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
    bool res = true;
    if (this->countRowsAndCols(other) == 1) {
        throw std::out_of_range("Matrices are not equal: different size");
    } else {
        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
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
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            res.matrix_[j][i] = matrix_[i][j];
        }
    }
    return res;
}

double S21Matrix::Determinant() {       // для 4*4 неправильно считает
    double res = 0, flag = 0, res_tmp = 0;
    if (this->cols_ != this->rows_) {
        throw std::out_of_range("Size error. Rows and cols aren\'t equal");
    } else {
        if (rows_ == 1) {
            res = this->matrix_[0][0];
        } else if (rows_ == 2) {
            res = matrix_[0][0] * matrix_[1][1] - 
                  matrix_[1][0] * matrix_[0][1];
        } else {
            double sign = 1;
            for (int j = 0; j < cols_; j++) {
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

S21Matrix S21Matrix::Minor(int r, int c) {
    int minor_col = 0, minor_row = 0, flag = 0;
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
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


/*=========== operators ===========*/

S21Matrix S21Matrix::operator+(const S21Matrix& x) const {
    S21Matrix res(*this);
    res.SumMatrix(x);
    return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& x) const {
    S21Matrix res(*this);
    res.SubMatrix(x);
    return res;
}

double& S21Matrix::operator()(const int i, const int j) {
    if ((i < 0 || j < 0) || (rows_ <= i || cols_ <= j)) {
        throw std::out_of_range("Error. Index out of range");
    }
    return matrix_[i][j];   // index matrix(i,j)
}

S21Matrix S21Matrix::operator*(double x) {
    S21Matrix res(*this);
    res.MulNumber(x);
    return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& x) const {
    S21Matrix res(*this);
    res.MulMatrix(x);
    return res;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& x) {
    Clean(*this);
    rows_ = x.rows_;
    cols_ = x.cols_;
    matrix_ = x.matrix_;

    x.cols_ = 0;
    x.rows_ = 0;
    x.matrix_ = nullptr;

    return *this;
}

bool S21Matrix::operator==(const S21Matrix& x) const {
    return this->EqMatrix(x);
}

S21Matrix& S21Matrix::operator*=(double x) {
    this->MulNumber(x);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& x) {
    this->SubMatrix(x);
    return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& x) {
    this->SumMatrix(x);
    return *this;
}


/*=========== get-set (accessor-mutator) ===========*/

int S21Matrix::getRows() noexcept {
    return this->rows_;
}

int S21Matrix::getCols() noexcept {
    return this->cols_;
}

void S21Matrix::setCols(int cols_count) {   // if another value - ???
    if (cols_count <= 0) {
        throw std::out_of_range("Error. Column\'s number can\'t be negative or zero value");
    }
    this->cols_ = cols_count;
}

void S21Matrix::setRows(int rows_count) {
    if (rows_count <= 0) {
        throw std::out_of_range("Error. Column\'s number can\'t be negative or zero value");
    }
    this->rows_ = rows_count;
}



// int main() {
//     S21Matrix a(4,4), b(2,2);
//     a(0,0) = 1;
//     a(0,1) = 2;
//     a(0,2) = -3;
//     a(0,3) = 4;
//     a(1,0) = 5;
//     a(1,1) = 6;
//     a(1,2) = 7;
//     a(1,3) = 8;
//     a(2,0) = 9;
//     a(2,1) = -10;
//     a(2,2) = 11;
//     a(2,3) = 12;
//     a(3,0) = 13;
//     a(3,1) = 14;
//     a(3,2) = 15;
//     a(3,3) = 16;
//     // b(0,0) = 2;
//     // b(0,1) = 2;
//     // b(1,0) = 2;
//     // b(1,1) = 2;
//     // b(2,0) = 2;
//     // b(2,1) = 2;
//     // a.MulMatrix(b);
//     // printf("%lf %lf %lf\n%lf %lf %lf\n%lf %lf %lf", a(0,0), a(0,1), a(0,2),a(1,0), a(1,1), a(1,2), a(2,0), a(2,1), a(2,2));
//     // a.setCols(5);
//     // printf("%d, %d, %lf", a.getRows(), a.getCols(), a(1, 1));
//     printf("%lf", a.Determinant());
//     return 0;
// }

