#include <gtest/gtest.h>

#include <iostream>

#include "s21_matrix_oop.h"

/*=========== FUNCTIONS TESTS ===========*/

TEST(test_function, eq_Matrix_1_false) {
  S21Matrix a(3, 3), b(3, 3);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 5;
      b(i, j) = 5;
    }
  }
  a(1, 2) = 23;
  EXPECT_FALSE(b.EqMatrix(a));
}

TEST(test_function, eq_Matrix_2_true) {
  S21Matrix a(3, 3), b(3, 3);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 5;
      b(i, j) = 5;
    }
  }
  EXPECT_TRUE(b.EqMatrix(a));
}

TEST(test_function, eq_Matrix_3_throw) {
  S21Matrix a(3, 2), b(3, 3);
  EXPECT_FALSE(b.EqMatrix(a));
}

TEST(test_function, mul_Number_1_true) {
  S21Matrix a(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 12.500000;
      a(i, j) = 5;
    }
  }
  a.MulNumber(2.5);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_function, mul_Number_2_true) {
  S21Matrix a(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 0;
      a(i, j) = 2.12;
    }
  }
  a.MulNumber(0);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_function, mul_Number_3_true) {
  S21Matrix a(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 2.12;
      a(i, j) = -2.12;
    }
  }
  a.MulNumber(-1);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_function, sum_Matrix_1_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 0;
      a(i, j) = 1.23;
      b(i, j) = -1.23;
    }
  }
  a.SumMatrix(b);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, TEST_SEGA) {
  S21Matrix matrix_check;
  EXPECT_EQ(matrix_check.GetRows(), 0);
  EXPECT_EQ(matrix_check.GetCols(), 0);

  S21Matrix matrix_test{matrix_check};
  EXPECT_EQ(matrix_test.GetRows(), 0);
  EXPECT_EQ(matrix_test.GetCols(), 0);

  S21Matrix matrix_check1;
  S21Matrix matrix_check2;
  S21Matrix matrix_check3(4, 4);

  matrix_check1* matrix_check2;
  matrix_check1 + matrix_check2;
  matrix_check1 += matrix_check2;
  matrix_check1 = matrix_check2;
  S21Matrix new_m;
  new_m = matrix_check1;
  S21Matrix new_m_1(10, 10);
  new_m_1 = matrix_check3;
  S21Matrix a(3, 3);
  S21Matrix c = a;
}

TEST(test_function, sum_Matrix_2_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 23.46;
      a(i, j) = 12.03;
      b(i, j) = 11.43;
    }
  }
  a.SumMatrix(b);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_function, sum_Matrix_3_throw) {
  S21Matrix a(3, 2), b(2, 3);
  EXPECT_THROW(a.SumMatrix(b), std::logic_error);
}

TEST(test_function, sub_Matrix_1_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 2.46;
      a(i, j) = 1.23;
      b(i, j) = -1.23;
    }
  }
  a.SubMatrix(b);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_function, sub_Matrix_2_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = -16;
      a(i, j) = -17.23;
      b(i, j) = -1.23;
    }
  }
  a.SubMatrix(b);
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_function, sub_Matrix_3_throw) {
  S21Matrix a(3, 3), b(2, 3);
  EXPECT_THROW(a.SubMatrix(b), std::logic_error);
}

TEST(test_function, mul_Matrix_1_true) {
  S21Matrix a(4, 3), b(3, 3), res(4, 3);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 12;
    }
  }
  for (int i = 0; i < b.GetRows(); i++) {
    for (int j = 0; j < b.GetCols(); j++) {
      b(i, j) = 3;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      res(i, j) = 108;
    }
  }
  a.MulMatrix(b);

  EXPECT_TRUE(a.EqMatrix(res));
}

TEST(test_function, mul_Matrix_4_true) {
  S21Matrix a(2, 3), b(3, 2), res(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(1, 0) = 1;
  a(1, 1) = 2;
  a(1, 2) = 3;
  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;
  b(2, 0) = 5;
  b(2, 1) = 6;
  res(0, 0) = 22;
  res(0, 1) = 28;
  res(1, 0) = 22;
  res(1, 1) = 28;
  a.MulMatrix(b);
  EXPECT_TRUE(a.EqMatrix(res));
}

TEST(test_function, mul_Matrix_2_throw) {
  S21Matrix a(2, 4), b(7, 2);
  EXPECT_THROW(a.MulMatrix(b), std::logic_error);
}

TEST(test_function, transpose_1) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(j, i) = j;
      a(i, j) = j;
    }
  }
  a = a.Transpose();
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_function, transpose_2) {
  S21Matrix a(2, 3), b(2, 3), res(3, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(j, i) = j;
      a(i, j) = j;
    }
  }
  a = a.Transpose();
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_function, determinant_1) {
  S21Matrix a(3, 3);
  double res = 0;
  a(0, 0) = 12;
  a(0, 1) = 21;
  a(0, 2) = -11;
  a(1, 0) = -39;
  a(1, 1) = 7;
  a(1, 2) = 4;
  a(2, 0) = 11;
  a(2, 1) = 4;
  a(2, 2) = 5;
  res = a.Determinant();
  ASSERT_EQ(res, 7810);
}

TEST(test_function, determinant_2) {
  S21Matrix a(2, 2);
  double res = 0;
  a(0, 0) = 12;
  a(0, 1) = 21;
  a(1, 0) = -39;
  a(1, 1) = 4;
  res = a.Determinant();
  ASSERT_EQ(res, 867);
}

TEST(test_function, determinant_3) {
  S21Matrix a(4, 4);
  double res = 0;
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = -3;
  a(0, 3) = 4;
  a(1, 0) = 5;
  a(1, 1) = 6;
  a(1, 2) = 7;
  a(1, 3) = 8;
  a(2, 0) = 9;
  a(2, 1) = -10;
  a(2, 2) = 11;
  a(2, 3) = 12;
  a(3, 0) = 13;
  a(3, 1) = 14;
  a(3, 2) = 15;
  a(3, 3) = 16;
  res = a.Determinant();
  ASSERT_EQ(res, -2880);
}

TEST(test_function, determinant_4_throw) {
  S21Matrix a(4, 2);
  EXPECT_THROW(a.Determinant(), std::logic_error);
}

TEST(test_function, calc_comp_1) {
  S21Matrix a(3, 3), res(3, 3), b(3, 3);
  res(0, 0) = 0, res(0, 1) = 90, res(0, 2) = -75, res(1, 0) = -222,
         res(1, 1) = -9, res(1, 2) = 137, res(2, 0) = 111, res(2, 1) = -18,
         res(2, 2) = 89;
  a(0, 0) = 1;
  a(0, 1) = 21;
  a(0, 2) = 3;
  a(1, 0) = -4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(2, 0) = 7;
  a(2, 1) = 10;
  a(2, 2) = 12;
  b = a.CalcComplements();
  ASSERT_EQ(res, b);
}

TEST(test_function, calc_comp_2) {
  S21Matrix a(4, 4), res(4, 4), b(4, 4);
  res(0, 0) = 1426, res(0, 1) = -238, res(0, 2) = -116, res(0, 3) = -690,
         res(1, 0) = -1301, res(1, 1) = -217, res(1, 2) = 111, res(1, 3) = 1105,
         res(2, 0) = -2000, res(2, 1) = -90, res(2, 2) = 80;
  res(2, 3) = 730, res(3, 0) = -3441, res(3, 1) = -387, res(3, 2) = 1081;
  res(3, 3) = 1665;
  a(0, 0) = 1;
  a(0, 1) = 21;
  a(0, 2) = 3;
  a(0, 3) = 5;
  a(1, 0) = -4;
  a(1, 1) = 5;
  a(1, 2) = 6;
  a(1, 3) = -11;
  a(2, 0) = 7;
  a(2, 1) = 10;
  a(2, 2) = 12;
  a(2, 3) = 9;
  a(3, 0) = 0;
  a(3, 1) = 1;
  a(3, 2) = -8;
  a(3, 3) = 1;
  b = a.CalcComplements();
  ASSERT_EQ(res, b);
}

TEST(test_function, calc_comp_3) {
  S21Matrix a(2, 2), res(2, 2), b(2, 2);
  res(0, 0) = 2, res(0, 1) = 3, res(1, 0) = 5, res(1, 1) = -1;
  a(0, 0) = -1;
  a(0, 1) = -5;
  a(1, 0) = -3;
  a(1, 1) = 2;
  b = a.CalcComplements();
  ASSERT_EQ(res, b);
}

TEST(test_function, calc_comp_4) {
  S21Matrix a(2, 5);
  EXPECT_THROW(a.CalcComplements(), std::logic_error);
}

TEST(test_function, calc_comp_5) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1), res(1, 1);
  a(0, 0) = 543.3231;
  res(0, 0) = 543.3231;
  b = a.CalcComplements();
  ASSERT_EQ(res, b);
}

TEST(test_function, inverse_1) {
  S21Matrix a(3, 3), res(3, 3), b(3, 3);
  res(0, 0) = -0.4, res(0, 1) = 0.2, res(0, 2) = 0.6, res(1, 0) = -0.2,
         res(1, 1) = 0.6, res(1, 2) = -0.2, res(2, 0) = 0.5, res(2, 1) = -0.5,
         res(2, 2) = 0;
  a(0, 0) = 1;
  a(0, 1) = 3;
  a(0, 2) = 4;
  a(1, 0) = 1;
  a(1, 1) = 3;
  a(1, 2) = 2;
  a(2, 0) = 2;
  a(2, 1) = 1;
  a(2, 2) = 2;

  b = a.InverseMatrix();
  ASSERT_EQ(res, b);
}

TEST(test_function, inverse_2) {
  S21Matrix a(2, 2), res(2, 2), b(2, 2);
  res(0, 0) = 0.5, res(0, 1) = -1, res(1, 0) = -0.5, res(1, 1) = 1.5;
  a(0, 0) = 6;
  a(0, 1) = 4;
  a(1, 0) = 2;
  a(1, 1) = 2;

  b = a.InverseMatrix();
  ASSERT_EQ(res, b);
}

TEST(test_function, inverse_3) {
  S21Matrix a(1, 1), res(1, 1), b(1, 1);
  res(0, 0) = 0.5;
  a(0, 0) = 2;
  b = a.InverseMatrix();
  ASSERT_EQ(res, b);
}

/*=========== OPERATOR TESTS ===========*/

TEST(test_op, op_sum_Matrix_1_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 0;
      a(i, j) = 1.23;
      b(i, j) = -1.23;
    }
  }
  a = a + b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_sum_Matrix_2_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 1.87;
      a(i, j) = 0.87;
      b(i, j) = 1;
    }
  }
  a = a + b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_sum_Matrix_3_throw) {
  S21Matrix a(3, 2), b(2, 3);
  EXPECT_THROW(a + b, std::logic_error);
}

TEST(test_op, op_sub_Matrix_1_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 2.46;
      a(i, j) = 1.23;
      b(i, j) = -1.23;
    }
  }
  a = a - b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_sub_Matrix_2_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 1.87;
      a(i, j) = 0.87;
      b(i, j) = -1;
    }
  }
  a = a - b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_sub_Matrix_3_throw) {
  S21Matrix a(3, 1), b(2, 3);
  EXPECT_THROW(a - b, std::logic_error);
}

TEST(test_op, op_brackets_Matrix_1_true) {
  S21Matrix a(3, 3);
  a(1, 2) = 3.3;
  ASSERT_EQ(3.3, a(1, 2));
  S21Matrix b(2, 2), c(2, 2);
  b = c;
  // S21Matrix a(3, 3);
  // S21Matrix c = a;
  // ASSERT_EQ(b,c);
}

TEST(test_op, op_brackets_Matrix_2_throw) {
  S21Matrix a(3, 3);
  EXPECT_THROW(a(1, 4), std::logic_error);
}

TEST(test_op, op_brackets_Matrix_3_throw) {
  S21Matrix a(3, 3);
  EXPECT_THROW(a(1, -1), std::logic_error);
}

TEST(test_op, op_mul_Number_1_true) {
  S21Matrix a(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 12.500000;
      a(i, j) = 5;
    }
  }
  a = a * 2.5;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_mul_Number_2_true) {
  S21Matrix a(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 0;
      a(i, j) = 2.12;
    }
  }
  a = a * 0;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_mul_Matrix_1_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 4;
      a(i, j) = 1;
      b(i, j) = 2;
    }
  }
  a = a * b;
  EXPECT_TRUE(a.EqMatrix(res));
}

TEST(test_op, op_mul_Matrix_2_throw) {
  S21Matrix a(2, 4), b(7, 2);
  EXPECT_THROW(a = a * b, std::logic_error);
}

TEST(test_op, op_mul_eq_Matrix_1_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 4;
      a(i, j) = 1;
      b(i, j) = 2;
    }
  }
  a *= b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_mul_eq_Matrix_2_throw) {
  S21Matrix a(2, 4), b(7, 2);
  EXPECT_THROW(a *= b, std::logic_error);
}

TEST(test_op, op_eq_Matrix_1) {
  S21Matrix a(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 1;
      a(i, j) = 1;
    }
  }
  EXPECT_TRUE(a == res);
}

TEST(test_op, op_eq_Matrix_2) {
  S21Matrix a(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 2;
      a(i, j) = 1;
    }
  }
  EXPECT_FALSE(a == res);
}

TEST(test_op, op_eq_Matrix_3_throw) {
  S21Matrix a(2, 3), res(3, 2);
  EXPECT_FALSE(a == res);
}

TEST(test_op, op_eqAndMul_Number_1) {
  S21Matrix a(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 12.500000;
      a(i, j) = 5;
    }
  }
  a *= 2.5;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_eqAndSum_Matrix_1) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 1.87;
      a(i, j) = 0.87;
      b(i, j) = 1;
    }
  }
  a += b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_eqAndSum_Matrix_2) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 0;
      a(i, j) = 1.23;
      b(i, j) = -1.23;
    }
  }
  a += b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_eqAndSub_Matrix_1_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 2.46;
      a(i, j) = 1.23;
      b(i, j) = -1.23;
    }
  }
  a -= b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_eqAndSub_Matrix_2_true) {
  S21Matrix a(2, 2), b(2, 2), res(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      res(i, j) = 1.87;
      a(i, j) = 0.87;
      b(i, j) = -1;
    }
  }
  a -= b;
  EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test_op, op_eqAndSub_Matrix_3_throw) {
  S21Matrix a(3, 1), b(2, 3);
  EXPECT_THROW(a -= b, std::logic_error);
}

TEST(test_op, test_op_brackets_min) {
  S21Matrix a(3, 3);
  EXPECT_THROW(a(-1, 2), std::logic_error);
}

/*=========== Get-Set TESTS ===========*/

TEST(test_GetSet, Get_1) {
  S21Matrix a(3, 2);
  int res_1 = a.GetCols();
  ASSERT_EQ(2, res_1);
}

TEST(test_GetSet, Get_2) {
  S21Matrix a(3, 2);
  int res_1 = a.GetRows();
  ASSERT_EQ(3, res_1);
}

TEST(test_GetSet, Set_1_rows) {
  S21Matrix a(3, 2);
  a.SetRows(4);
  int res_1 = a.GetRows();
  ASSERT_EQ(4, res_1);
}

TEST(test_GetSet, Set_2_rows) {
  S21Matrix a(3, 2);
  a.SetRows(3);
  int res_1 = a.GetRows();
  ASSERT_EQ(3, res_1);
}

TEST(test_GetSet, Set_3_rows) {
  S21Matrix a(3, 2);
  EXPECT_THROW(a.SetRows(-1), std::logic_error);
}

TEST(test_GetSet, Set_1_cols) {
  S21Matrix a(3, 2);
  a.SetCols(2);
  int res_1 = a.GetCols();
  ASSERT_EQ(2, res_1);
}

TEST(test_GetSet, Set_2_cols) {
  S21Matrix a(3, 2);
  a.SetCols(5);
  int res_1 = a.GetCols();
  ASSERT_EQ(5, res_1);
}

TEST(test_GetSet, Set_3_cols) {
  S21Matrix a(3, 3);
  EXPECT_THROW(a.SetCols(-1), std::logic_error);
}

TEST(test, constructor) {
  S21Matrix a;
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_EQ(a.GetRows(), 0);
  a.SetCols(2);
  a.SetCols(2);
  S21Matrix b(3, 3), c(b);
  EXPECT_EQ(c.GetRows(), 3);
  S21Matrix d(std::move(b));
  EXPECT_EQ(b.GetCols(), 0);
  EXPECT_EQ(b.GetRows(), 0);
  EXPECT_EQ(d.GetRows(), 3);
  EXPECT_EQ(d.GetCols(), 3);
  EXPECT_THROW(S21Matrix g(3, -2), std::logic_error);
}

TEST(test_GetSet, Set_4_cols) {
  S21Matrix a(3, 5);
  a.SetCols(2);
  int res_1 = a.GetCols();
  ASSERT_EQ(2, res_1);
}

TEST(test, Printer) {
  S21Matrix a(2, 2);
  for (int i = 0; i < a.GetRows(); i++) {
    for (int j = 0; j < a.GetCols(); j++) {
      a(i, j) = 0.87;
    }
  }
  a.Printer();
  ASSERT_EQ(a(1, 1), 0.87);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}