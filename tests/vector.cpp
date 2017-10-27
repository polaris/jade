#include "catch.hpp"

#include "../include/vector.h"

TEST_CASE("construct a new vector", "[vector]") {
    jade::vector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
}

TEST_CASE("copy construct a new vector", "[vector]") {
    jade::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    jade::vector<int> v2(v1);

    REQUIRE(v2.size() == 3);
    REQUIRE(v2.capacity() == 4);

    int k = 1;
    for (const auto& i : v2) {
        REQUIRE(k++ == i);
    }
}

TEST_CASE("assignement operator", "[vector]") {
    jade::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    REQUIRE(v1.size() == 2);
    REQUIRE(v1.capacity() == 2);

    jade::vector<int> v2;
    v2.push_back(3);
    v2.push_back(4);
    v2.push_back(5);

    REQUIRE(v2.size() == 3);
    REQUIRE(v2.capacity() == 4);

    v2 = v1;

    REQUIRE(v2.size() == 2);
    REQUIRE(v2.capacity() == 2);

    int k = 1;
    for (const auto& i : v2) {
        REQUIRE(k++ == i);
    }
}

TEST_CASE("move assignement operator", "[vector]") {
    jade::vector<int> v1{1,2,3};
    REQUIRE(v1.size() == 3);
    REQUIRE(v1.capacity() == 3);

    jade::vector<int> v2{4,5,6,7,8};
    REQUIRE(v2.size() == 5);
    REQUIRE(v2.capacity() == 5);

    v1 = std::move(v2);
    REQUIRE(v1.size() == 5);
    REQUIRE(v1.capacity() == 5);
    REQUIRE(v2.size() == 0);
    REQUIRE(v2.capacity() == 0);
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

TEST_CASE("constructor with initializer list", "[vector]") {
    jade::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    REQUIRE(v.capacity() == 9);
    REQUIRE(v.size() == 9);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 4);
    REQUIRE(v[4] == 5);
    REQUIRE(v[5] == 6);
    REQUIRE(v[6] == 7);
    REQUIRE(v[7] == 8);
    REQUIRE(v[8] == 9);
}

TEST_CASE("vector can be constructed with a number copies of elements with a certain value", "[vector]") {
    SECTION("default-inserted instances of T", "[vector]") {
        jade::vector<int> v1(50);
        REQUIRE(v1.capacity() == 50);
        REQUIRE(v1.size() == 50);
        for (const auto i : v1) {
            REQUIRE(i == 0);
        }
    }
    SECTION("copies of provided value", "[vector]") {
        jade::vector<int> v1(50, 123);
        REQUIRE(v1.capacity() == 50);
        REQUIRE(v1.size() == 50);
        for (const auto i : v1) {
            REQUIRE(i == 123);
        }
    }
}

TEST_CASE("move constructor", "[vector]") {
    jade::vector<int> v1 = { 1, 2, 3 };
    REQUIRE(v1.size() == 3);
    REQUIRE(v1.capacity() == 3);

    jade::vector<int> v2{std::move(v1)};
    REQUIRE(v1.size() == 0);
    REQUIRE(v1.capacity() == 0);
    REQUIRE(v2.size() == 3);
    REQUIRE(v2.capacity() == 3);
}

TEST_CASE("a vector is resizable", "[vector]") {
    jade::vector<int> v;
    v.resize(16);
    REQUIRE(v.capacity() == 16);
    REQUIRE(v.size() == 0);
}

TEST_CASE("a new vector is resizable to zero", "[vector]") {
    jade::vector<int> v;
    v.resize(0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.size() == 0);
}

TEST_CASE("resizing a vector keeps it consistent", "[vector]") {
    jade::vector<int> v;
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.size() == 0);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    REQUIRE(v.capacity() == 4);
    REQUIRE(v.size() == 3);

    v.resize(16);
    REQUIRE(v.capacity() == 16);
    REQUIRE(v.size() == 3);

    v.resize(0);
    REQUIRE(v.capacity() == 0);
    REQUIRE(v.size() == 0);

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    REQUIRE(v.capacity() == 4);
    REQUIRE(v.size() == 3);

    v.resize(16);
    REQUIRE(v.capacity() == 16);
    REQUIRE(v.size() == 3);
}

TEST_CASE("at method checks bounds of vector", "[vector]") {
    jade::vector<int> v = { 1, 2, 3, 4, 5 };
    REQUIRE_THROWS_AS(v.at(-1), std::out_of_range);
    REQUIRE_NOTHROW(v.at(0));
    REQUIRE_NOTHROW(v.at(2));
    REQUIRE_NOTHROW(v.at(4));
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
}
