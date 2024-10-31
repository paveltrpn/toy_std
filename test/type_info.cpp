
#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "type_info/type_name.h"
#include "type_info/type_index.h"
#include "type_info/registry.h"

#include "memory.h"
#include <source_location>
#include <print>

TEST( type_name, get_type_name ) {
    const auto unique_ptrName = toy::type_name<toy::unique_ptr<int>>();
    const auto shared_ptrName = toy::type_name<toy::shared_ptr<int>>();
    EXPECT_EQ( "toy::unique_ptr<int>", unique_ptrName );
    EXPECT_EQ( "toy::shared_ptr<int>", shared_ptrName );

#define TEST_TYPE std::vector<std::string>
    const auto arbitaryName = toy::type_name<TEST_TYPE>();
    const auto functionName = toy::__detail::wrapped_type_name<TEST_TYPE>();
    const auto voidName = toy::__detail::wrapped_type_name<void>();

    std::println( " std::vector<std::string> name: {}", arbitaryName );
    std::println( "                 function name: {}", functionName );
    std::println( "                     void name: {}", voidName );
}

TEST( type_index, next_value ) {
    EXPECT_EQ( 0, toy::__detail::type_index::next() );
    EXPECT_EQ( 1, toy::__detail::type_index::next() );
    EXPECT_EQ( 2, toy::__detail::type_index::next() );
    EXPECT_EQ( 3, toy::__detail::type_index::next() );
    EXPECT_EQ( 4, toy::__detail::type_index::next() );
}

TEST( type_index, type_index ) {
    // NOTE: because of next_value test count start from "5"
    EXPECT_EQ( 5, toy::type_index<int>::value() );
    EXPECT_EQ( 6, toy::type_index<float>::value() );
    EXPECT_EQ( 7, toy::type_index<double>::value() );
    EXPECT_EQ( 8, toy::type_index<toy::shared_ptr<int>>::value() );
    EXPECT_EQ( 9, toy::type_index<toy::unique_ptr<int>>::value() );

    EXPECT_NE( 0, toy::type_index<toy::shared_ptr<int>>::value() );
    EXPECT_EQ( 9, toy::type_index<toy::unique_ptr<int>>::value() );
}

struct T {
    int ta{ 12 };
    int tb{ 13 };
    int tc{ 14 };
};

struct B : public T {
    int a{ 0 };
    int b{ 0 };
};

struct C {
    int a{};
};

using CAlias = C;
using BAlias = B;

TEST( registry, last ) {
    toy::registry registry;

    auto bv = B{ { 12, 13, 14 }, 0, 0 };
    auto tv = T{ 3, 4, 5 };

    registry.emplace( B{ { 12, 13, 14 }, 0, 0 } );
    registry.emplace<T>( 1, 2, 3 );
    registry.emplace<T>( 3, 4, 5 );

    const auto &lt = registry.last<T>();
    EXPECT_EQ( lt.ta, tv.ta );
    EXPECT_EQ( lt.tb, tv.tb );
    EXPECT_EQ( lt.tc, tv.tc );

    const auto &lb = registry.last<B>();
    EXPECT_EQ( lb.ta, bv.ta );
    EXPECT_EQ( lb.tb, bv.tb );
    EXPECT_EQ( lb.tc, bv.tc );
    EXPECT_EQ( lb.a, bv.a );
    EXPECT_EQ( lb.b, bv.b );

    const auto &[bref, tref] = registry.last<B, T>();
    EXPECT_EQ( tref.ta, tv.ta );
    EXPECT_EQ( tref.tb, tv.tb );
    EXPECT_EQ( tref.tc, tv.tc );

    EXPECT_EQ( bref.ta, bv.ta );
    EXPECT_EQ( bref.tb, bv.tb );
    EXPECT_EQ( bref.tc, bv.tc );
    EXPECT_EQ( bref.a, bv.a );
    EXPECT_EQ( bref.b, bv.b );
}

TEST( registry, all_of_any_of ) {
    toy::registry registry;

    registry.emplace( B{} );
    registry.emplace( T{ .ta = 1, .tb = 2, .tc = 3 } );
    registry.emplace<T>( 3, 4, 5 );

    EXPECT_TRUE( registry.all_of<T>() );
    EXPECT_TRUE( registry.any_of<B>() );
    EXPECT_FALSE( registry.any_of<C>() );

    EXPECT_TRUE( ( registry.any_of<C, B>() ) );
    EXPECT_TRUE( ( registry.any_of<CAlias, BAlias>() ) );
    EXPECT_FALSE( ( registry.all_of<C, B>() ) );

    EXPECT_TRUE( ( registry.any_of<C, B, T>() ) );
    EXPECT_FALSE( ( registry.all_of<C, B, T>() ) );

    EXPECT_TRUE( ( registry.all_of<>() ) );
    EXPECT_FALSE( ( registry.any_of<>() ) );
}

TEST( registry, all ) {
    toy::registry registry;

    registry.emplace<T>( 1, 2, 3 );
    registry.emplace<T>( 3, 4, 5 );

    const auto &all_ts = registry.all<T>();
    std::unordered_map<std::size_t, T> tst = { { 0, T{ 1, 2, 3 } },
                                               { 1, T{ 3, 4, 5 } } };
    for ( auto i = 0; i < 1; ++i ) {
        auto one = tst.at( i );
        auto two = all_ts.at( i );
        EXPECT_EQ( one.ta, two.ta );
        EXPECT_EQ( one.tb, two.tb );
        EXPECT_EQ( one.tc, two.tc );
    }

    // ASSERT_THAT( all_ts, testing::ElementsAre( tvo, tvt ) );
}
