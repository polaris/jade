#include "catch.hpp"

#include "../include/array.h"

TEST_CASE("construct a new array for 10 integers", "[array]") {
    jade::array<int, 10> a;
    REQUIRE(a.size() == 10);
}

TEST_CASE("construct a new array for 10 floats", "[array]") {
    jade::array<float, 10> a;
    REQUIRE(a.size() == 10);
}

TEST_CASE("radom access with index operator works", "[array]") {
    jade::array<int, 10> a;
    int counter = 1;
    for (auto& f : a) {
        f = counter++;
    }
    counter = 1;
    for (const auto& f : a) {
        REQUIRE(f == counter++);
    }
}

TEST_CASE("at method checks bounds", "[array]") {
    jade::array<int, 10> a;
    REQUIRE_THROWS_AS(a.at(10), std::out_of_range);
    REQUIRE_THROWS_AS(a.at(-1), std::out_of_range);
}
