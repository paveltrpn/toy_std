
#include <gtest/gtest.h>

import toy_std.array;

TEST( array, instatiation ) {
    toy::array<int, 3> first{ 0 };

    EXPECT_EQ( first[1], 0 );

    first[0] = 10;
    EXPECT_EQ( first[0], 10 );

    first[2] = 30;
    EXPECT_EQ( first[2], 30 );
}

TEST( array, copy_create ) {
    toy::array<int, 3> first{ 0 };

    first[0] = 10;
    first[2] = 30;

    toy::array<int, 3> second{ first };

    EXPECT_EQ( second[0], 10 );
    EXPECT_EQ( second[1], 0 );
    EXPECT_EQ( second[2], 30 );
}

TEST( array, assign ) {
    toy::array<int, 3> first{ 0 };
    toy::array<int, 3> second{ 0 };

    first[0] = 10;
    first[2] = 30;

    second = first;

    EXPECT_EQ( second[0], 10 );
    EXPECT_EQ( second[1], 0 );
    EXPECT_EQ( second[2], 30 );
}

TEST( array, at ) {
    toy::array<int, 3> first{ 0 };

    EXPECT_NO_THROW( first.at( 2 ) );
    EXPECT_THROW( first.at( 4 ), std::invalid_argument );
}

TEST( array, case_c_style_pointer_get ) {
    toy::array<int, 3> first{ 0, 1, 2, 3, 4, 5, 6, 7 };

    auto ptr = first.data();

    EXPECT_EQ( ptr[0], 0 );
    EXPECT_EQ( ptr[1], 1 );
    EXPECT_EQ( ptr[2], 2 );
}

TEST( array, iterator ) {
    toy::array<int, 8> first{ 0, 1, 2, 3, 4, 5, 6, 7 };

    for ( size_t i = 0; auto& elem : first ) {
        EXPECT_EQ( elem, i );
        ++i;
    }
}
