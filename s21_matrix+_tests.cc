#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>

#include "s21_matrix_oop.h"

/*=========== FUNCTIONS TESTS ===========*/

TEST(test, eq_Matrix_1_false) {
    S21Matrix a(3,3), b(3,3);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            a(i,j) = 5;
            b(i,j) = 5;
        }
    }
    a(1,2) = 23;
    EXPECT_FALSE(b.EqMatrix(a));
}

TEST(test, eq_Matrix_2_true) {
    S21Matrix a(3,3), b(3,3);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            a(i,j) = 5;
            b(i,j) = 5;
        }
    }
    EXPECT_TRUE(b.EqMatrix(a));
}

TEST(test, eq_Matrix_3_throw) {
    S21Matrix a(3,2), b(3,3);
    EXPECT_THROW(b.EqMatrix(a),std::logic_error);
}

TEST(test, mul_Number_1_true) {
    S21Matrix a(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 12.500000;
            a(i,j) = 5;
        }
    }
    a.MulNumber(2.5);
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, mul_Number_2_true) {
    S21Matrix a(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 0;
            a(i,j) = 2.12;
        }
    }
    a.MulNumber(0);
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, mul_Number_3_true) {
    S21Matrix a(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 2.12;
            a(i,j) = -2.12;
        }
    }
    a.MulNumber(-1);
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, sum_Matrix_1_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 0;
            a(i,j) = 1.23;
            b(i,j) = -1.23;
        }
    }
    a.SumMatrix(b);
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, sum_Matrix_2_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 23.46;
            a(i,j) = 12.03;
            b(i,j) = 11.43;
        }
    }
    a.SumMatrix(b);
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, sum_Matrix_3_throw) {
    S21Matrix a(3,2), b(2,3);
    EXPECT_THROW(a.SumMatrix(b),std::logic_error);
}


TEST(test, sub_Matrix_1_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 2.46;
            a(i,j) = 1.23;
            b(i,j) = -1.23;
        }
    }
    a.SubMatrix(b);
    EXPECT_TRUE(res.EqMatrix(a));
}


TEST(test, sub_Matrix_2_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = -16;
            a(i,j) = -17.23;
            b(i,j) = -1.23;
        }
    }
    a.SubMatrix(b);
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, sub_Matrix_3_throw) {
    S21Matrix a(3,3), b(2,3);
    EXPECT_THROW(a.SubMatrix(b),std::logic_error);
}

TEST(test, mul_Matrix_1_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 4;
            a(i,j) = 1;
            b(i,j) = 2;
        }
    }
    a.MulMatrix(b);
    EXPECT_TRUE(res.EqMatrix(a));
}

// TEST(test, mul_Matrix_2_true) {
//     S21Matrix a(2,3), b(3,2), res(2,2);
//     for (int i = 0; i < a.getRows(); i++) {
//         for (int j = 0; j < a.getCols(); j++) {
//             a(i,j) = 1;
//         }
//     }

//     for (int i = 0; i < b.getRows(); i++) {
//         for (int j = 0; j < b.getCols(); j++) {
//             b(i,j) = 2;
//         }
//     }
//     res(0,0) = 6;
//     res(0,1) = 6;
//     res(1,0) = 6;
//     res(1,1) = 6;
//     S21Matrix to_check(2,2);
//     a.MulMatrix(b);
//     to_check = a;
//         for (int i = 0; i < a.getRows(); i++) {
//         for (int j = 0; j < a.getCols(); j++) {
//             printf("%lf",  a(i,j));

//         }
//     }
//     EXPECT_TRUE(res.EqMatrix(to_check));
// }

TEST(test, transpose_1) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(j,i) = j;
            a(i,j) = j;
        }
    }
    a = a.Transpose();
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, transpose_2) {
    S21Matrix a(2,3), b(2,3), res(3,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(j,i) = j; 
            a(i,j) = j;
        }
    }
    a = a.Transpose();
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, determinant_1) {
    S21Matrix a(3,3);
    double res = 0;
    a(0,0) = 12;
    a(0,1) = 21;
    a(0,2) = -11;
    a(1,0) = -39;
    a(1,1) = 7;
    a(1,2) = 4;
    a(2,0) = 11;
    a(2,1) = 4;
    a(2,2) = 5;
    res = a.Determinant();
    ASSERT_EQ(res, 7810);
}

TEST(test, determinant_2) {
    S21Matrix a(2,2);
    double res = 0;
    a(0,0) = 12;
    a(0,1) = 21;
    a(1,0) = -39;
    a(1,1) = 4;
    res = a.Determinant();
    ASSERT_EQ(res, 867);
}

TEST(test, determinant_3) {
    S21Matrix a(4,4);
    double res = 0;
    a(0,0) = 1;
    a(0,1) = 2;
    a(0,2) = -3;
    a(0,3) = 4;
    a(1,0) = 5;
    a(1,1) = 6;
    a(1,2) = 7;
    a(1,3) = 8;
    a(2,0) = 9;
    a(2,1) = -10;
    a(2,2) = 11;
    a(2,3) = 12;
    a(3,0) = 13;
    a(3,1) = 14;
    a(3,2) = 15;
    a(3,3) = 16;
    res = a.Determinant();
    ASSERT_EQ(res, -2880);
}

TEST(test, determinant_4_throw) {
    S21Matrix a(4,2);
    EXPECT_THROW(a.Determinant(), std::logic_error);
}


/*=========== OPERATOR TESTS ===========*/

TEST(test, op_sum_Matrix_1_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 0;
            a(i,j) = 1.23;
            b(i,j) = -1.23;
        }
    }
    a = a + b;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_sum_Matrix_2_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 1.87;
            a(i,j) = 0.87;
            b(i,j) = 1;
        }
    }
    a = a + b;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_sum_Matrix_3_throw) {
    S21Matrix a(3,2), b(2,3);
    EXPECT_THROW(a + b, std::logic_error);
}

TEST(test, op_sub_Matrix_1_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 2.46;
            a(i,j) = 1.23;
            b(i,j) = -1.23;
        }
    }
    a = a - b;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_sub_Matrix_2_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 1.87;
            a(i,j) = 0.87;
            b(i,j) = -1;
        }
    }
    a = a - b;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_sub_Matrix_3_throw) {
    S21Matrix a(3,1), b(2,3);
    EXPECT_THROW(a - b, std::logic_error);
}

TEST(test, op_brackets_Matrix_1_true) {
    S21Matrix a(3,3);
    a(1,2) = 3.3;
    ASSERT_EQ(3.3, a(1, 2));
}

TEST(test, op_brackets_Matrix_2_throw) {
    S21Matrix a(3,3);
    EXPECT_THROW(a(1,4), std::logic_error);
}

TEST(test, op_brackets_Matrix_3_throw) {
    S21Matrix a(3,3);
    EXPECT_THROW(a(1,-1), std::logic_error);
}

TEST(test, op_mul_Number_1_true) {
    S21Matrix a(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 12.500000;
            a(i,j) = 5;
        }
    }
    a = a * 2.5;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_mul_Number_2_true) {
    S21Matrix a(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 0;
            a(i,j) = 2.12;
        }
    }
    a = a * 0;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_eq_Matrix_1) {
    S21Matrix a(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 1;
            a(i,j) = 1;
        }
    }
    EXPECT_TRUE(a == res);
}

TEST(test, op_eq_Matrix_2) {
    S21Matrix a(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 2;
            a(i,j) = 1;
        }
    }
    EXPECT_FALSE(a == res);
}

TEST(test, op_eq_Matrix_3_throw) {
    S21Matrix a(2,3), res(3,2);
    EXPECT_THROW(a == res, std::logic_error);
}

TEST(test, op_eqAndMul_Number_1) {
    S21Matrix a(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 12.500000;
            a(i,j) = 5;
        }
    }
    a *= 2.5;
    EXPECT_TRUE(res.EqMatrix(a));
}


TEST(test, op_eqAndSum_Matrix_1) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 1.87;
            a(i,j) = 0.87;
            b(i,j) = 1;
        }
    }
    a += b;
    EXPECT_TRUE(res.EqMatrix(a));
}


TEST(test, op_eqAndSum_Matrix_2) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 0;
            a(i,j) = 1.23;
            b(i,j) = -1.23;
        }
    }
    a += b;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_eqAndSub_Matrix_1_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 2.46;
            a(i,j) = 1.23;
            b(i,j) = -1.23;
        }
    }
    a -= b;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_eqAndSub_Matrix_2_true) {
    S21Matrix a(2,2), b(2,2), res(2,2);
    for (int i = 0; i < a.getRows(); i++) {
        for (int j = 0; j < a.getCols(); j++) {
            res(i,j) = 1.87;
            a(i,j) = 0.87;
            b(i,j) = -1;
        }
    }
    a -= b;
    EXPECT_TRUE(res.EqMatrix(a));
}

TEST(test, op_eqAndSub_Matrix_3_throw) {
    S21Matrix a(3,1), b(2,3);
    EXPECT_THROW(a -= b, std::logic_error);
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}