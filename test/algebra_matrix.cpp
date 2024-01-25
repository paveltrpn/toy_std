
import toy_std.algebra;
import toy_std.array;

#include <format>
#include <boost/test/unit_test.hpp>

// #define BROKEN_EXCLUDE

#ifdef BROKEN_EXCLUDE
void testDeclarations() {
    toy::algebra::matrix<float, 0, 0> mtrx0x0{};
    toy::algebra::matrix<float, 5, 0> mtrx5x0{};
    toy::algebra::matrix<float, 0, 5> mtrx0x5{};
    toy::algebra::matrix<int *, 6, 5> mtrx6x5{};
}
#endif

BOOST_AUTO_TEST_SUITE(matrix)

namespace utf = boost::unit_test;

toy::algebra::matrix2f zero2{ 0, 0, 0, 0 };
toy::algebra::matrix2f idtt2{ 1, 0, 0, 1 };
toy::algebra::matrix2f fibo2{ 0, 1, 1, 2 };
toy::algebra::matrix2f fibo2_tr{ 0, 1, 1, 2 };

toy::algebra::matrix3f zero3{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
toy::algebra::matrix3f idtt3{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };
toy::algebra::matrix3f fibo3{ 0, 1, 1, 2, 3, 5, 8, 13, 21 };
toy::algebra::matrix3f fibo3_tr{ 0, 2, 8, 1, 3, 13, 1, 5, 21 };
// fibo3_tr * fibo3
toy::algebra::matrix3f mult3_tr{ 2, 8, 34, 8, 38, 160, 34, 160, 674 };

toy::algebra::matrix4f zero4{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
toy::algebra::matrix4f idtt4{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
toy::algebra::matrix4f fibo4{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
toy::algebra::matrix4f fibo4_tr{ 0, 3, 21, 144, 1, 5, 34, 233, 1, 8, 55, 377, 2, 13, 89, 610 };

BOOST_AUTO_TEST_CASE(matrix2_case_construct_idtt_zero, *utf::tolerance(0.00001)) {
    toy::algebra::matrix2f one;

    one.set_idtt();

    for (auto i = 0; i < 2; ++i)
        for (auto j = 0; j < 2; ++j) {
            auto foo = one[i, j];
            auto bar = idtt4[i, j];
            BOOST_TEST(foo == bar);
        }

    one.set_zero();

    for (auto i = 0; i < 2; ++i)
        for (auto j = 0; j < 2; ++j) {
            auto foo = one[i, j];
            auto bar = zero4[i, j];
            BOOST_TEST(foo == bar);
        }
}

BOOST_AUTO_TEST_CASE(matrix2_case_transpose, *utf::tolerance(0.00001)) {
    auto one = fibo2;
    
    one.transpose_self();

    for (auto i = 0; i < 2; ++i)
        for (auto j = 0; j < 2; ++j) {
            auto foo = one[i, j];
            auto bar = fibo2_tr[i, j];
            BOOST_TEST(foo == bar);
        }

    one.transpose_self();
    
    auto tr = one.transpose();

    for (auto i = 0; i < 2; ++i)
        for (auto j = 0; j < 2; ++j) {
            auto foo = tr[i, j];
            auto bar = fibo2_tr[i, j];
            BOOST_TEST(foo == bar);
        }
}

BOOST_AUTO_TEST_CASE(matrix3_case_construct_idtt_zero, *utf::tolerance(0.00001)) {
    toy::algebra::matrix3f one;

    one.set_idtt();

    for (auto i = 0; i < 3; ++i)
        for (auto j = 0; j < 3; ++j) {
            auto foo = one[i, j];
            auto bar = idtt4[i, j];
            BOOST_TEST(foo == bar);
        }

    one.set_zero();

    for (auto i = 0; i < 3; ++i)
        for (auto j = 0; j < 3; ++j) {
            auto foo = one[i, j];
            auto bar = zero4[i, j];
            BOOST_TEST(foo == bar);
        }
}

BOOST_AUTO_TEST_CASE(matrix3_case_transpose, *utf::tolerance(0.00001)) {
    auto one = fibo3;
    /*
    one.transpose_self();

    for (auto i = 0; i < 4; ++i)
        for (auto j = 0; j < 4; ++j) {
            auto foo = one[i, j];
            auto bar = fibo4_tr[i, j];
            BOOST_TEST(foo == bar);
        }

    one.transpose_self();
    */
    auto tr = one.transpose();

    for (auto i = 0; i < 3; ++i)
        for (auto j = 0; j < 3; ++j) {
            auto foo = tr[i, j];
            auto bar = fibo3_tr[i, j];
            BOOST_TEST(foo == bar);
        }
}

BOOST_AUTO_TEST_CASE(matrix3_case_mult, *utf::tolerance(0.00001)) {
    auto one = fibo3_tr.mult(fibo3);

    for (auto i = 0; i < 3; ++i)
        for (auto j = 0; j < 3; ++j) {
            auto foo = one[i, j];
            auto bar = mult3_tr[i, j];
            BOOST_TEST(foo == bar);
        }
}

BOOST_AUTO_TEST_CASE(matrix3_case_mult_operator, *utf::tolerance(0.00001)) {
    auto one = fibo3_tr * fibo3;

    for (auto i = 0; i < 3; ++i)
        for (auto j = 0; j < 3; ++j) {
            auto foo = one[i, j];
            auto bar = mult3_tr[i, j];
            BOOST_TEST(foo == bar);
        }
}

BOOST_AUTO_TEST_CASE(matrix3_case_sub_det_lu, *utf::tolerance(0.00001)) {
    auto A = fibo3;
    /* A =
     * 0  1  1
     * 2  3  5
     * 8  13 31
     */
    A[8] = 31;
    
    auto one = A.sub(mult3_tr);
    /* one =
     * -2   -7   -33
     * -6   -35  -155
     * -26  -147 -643
     */

    auto det = one.det_lu();

    BOOST_TEST(det == 280);
}

BOOST_AUTO_TEST_CASE(matrix4_case_construct_idtt_zero, *utf::tolerance(0.00001)) {
    toy::algebra::matrix4f one;

    one.set_idtt();

    for (auto i = 0; i < 4; ++i)
        for (auto j = 0; j < 4; ++j) {
            auto foo = one[i, j];
            auto bar = idtt4[i, j];
            BOOST_TEST(foo == bar);
        }

    one.set_zero();

    for (auto i = 0; i < 4; ++i)
        for (auto j = 0; j < 4; ++j) {
            auto foo = one[i, j];
            auto bar = zero4[i, j];
            BOOST_TEST(foo == bar);
        }
}

BOOST_AUTO_TEST_CASE(matrix4_case_transpose, *utf::tolerance(0.00001)) {
    auto one = fibo4;

    one.transpose_self();

    for (auto i = 0; i < 4; ++i)
        for (auto j = 0; j < 4; ++j) {
            auto foo = one[i, j];
            auto bar = fibo4_tr[i, j];
            BOOST_TEST(foo == bar);
        }

    one.transpose_self();
    auto tr = one.transpose();

    for (auto i = 0; i < 4; ++i)
        for (auto j = 0; j < 4; ++j) {
            auto foo = tr[i, j];
            auto bar = fibo4_tr[i, j];
            BOOST_TEST(foo == bar);
        }
}

BOOST_AUTO_TEST_SUITE_END()
