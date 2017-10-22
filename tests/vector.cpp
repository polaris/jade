#include "catch.hpp"

#include "../include/vector.h"

TEST_CASE("construct a new vector", "[vector]") {
    jade::vector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
}

TEST_CASE("capacity doubles everytime the size increases to the current max. capacity", "[vector]") {
    jade::vector<int> v;
    v.push_back(1);
    REQUIRE(v.size() == 1);
    REQUIRE(v.capacity() == 1);
    v.push_back(2);
    REQUIRE(v.size() == 2);
    REQUIRE(v.capacity() == 2);
    v.push_back(3);
    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() == 4);
    v.push_back(4);
    REQUIRE(v.size() == 4);
    REQUIRE(v.capacity() == 4);
    v.push_back(5);
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 8);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    REQUIRE(v.size() == 8);
    REQUIRE(v.capacity() == 8);
    v.push_back(9);
    REQUIRE(v.size() == 9);
    REQUIRE(v.capacity() == 16);
}
