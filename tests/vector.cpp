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

TEST_CASE("a vector can be constructed using a pair of iterators") {
    int arr[5] = {1,2,3,4,5};
    jade::vector<int> v{arr, arr+5};
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 5);
}

TEST_CASE("assignment operator", "[vector]") {
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

TEST_CASE("move assignment operator", "[vector]") {
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

TEST_CASE("initializer list assginment operator") {
    jade::vector<int> v{1,2,3};
    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);

    v = {4,5,6,7};
    REQUIRE(v.size() == 4);
    REQUIRE(v.capacity() == 4);
    REQUIRE(v[0] == 4);
    REQUIRE(v[1] == 5);
    REQUIRE(v[2] == 6);
    REQUIRE(v[3] == 7);

    v = {};
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
}

TEST_CASE("assign replaces contents with a number of values") {
    jade::vector<int> v{1,2,3};
    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() == 3);

    v.assign(5, 123);
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 5);
    for (const auto i : v) {
        REQUIRE(i == 123);
    }
}

TEST_CASE("a vector can be assigned using a pair of iterators") {
    jade::vector<int> v{1,2,3};
    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() == 3);

    int arr[5] = {1,2,3,4,5};
    v.assign(arr, arr+5);
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 5);
}

TEST_CASE("a vector can be assigned using an initializer list") {
    jade::vector<int> v{1,2,3};
    REQUIRE(v.size() == 3);
    REQUIRE(v.capacity() == 3);

    v.assign({1,2,3,4,5});
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() == 5);
}

TEST_CASE("at method checks bounds of vector", "[vector]") {
    jade::vector<int> v = { 1, 2, 3, 4, 5 };
    REQUIRE_THROWS_AS(v.at(-1), std::out_of_range);
    REQUIRE_NOTHROW(v.at(0));
    REQUIRE_NOTHROW(v.at(2));
    REQUIRE_NOTHROW(v.at(4));
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
}

TEST_CASE("References to an element at a specified location is returned by the index operator", "[vector]") {
    jade::vector<int> v{0,1,2,3,4,5,6,7,8,9};
    REQUIRE(v.size() == 10);
    REQUIRE(v.capacity() == 10);
    jade::vector<int>::size_type i = 0;
    for (; i < v.size(); ++i) {
        REQUIRE(i == v[i]);
    }
}

TEST_CASE("front returns a reference to the first element in the container") {
    jade::vector<int> v1{123};
    REQUIRE(v1.front() == 123);

    jade::vector<int> v2{9,8,7,6,5,4,3,2,1,0};
    REQUIRE(v2.front() == 9);
}

TEST_CASE("back returns a reference to the last element in the container") {
    jade::vector<int> v1{123};
    REQUIRE(v1.back() == 123);

    jade::vector<int> v2{9,8,7,6,5,4,3,2,1,0};
    REQUIRE(v2.back() == 0);
}

TEST_CASE("data returns pointer to the underlying array serving as element storage", "[vector]") {
    jade::vector<int> v{0,1,2,3,4,5,6,7,8,9};
    REQUIRE(v.size() == 10);
    REQUIRE(v.capacity() == 10);
    const auto data = v.data();
    jade::vector<int>::size_type i = 0;
    for (; i < v.size(); ++i) {
        REQUIRE(i == data[i]);
    }
}

TEST_CASE("begin returns an iterator to the first element of the container; end returns an iterator to the element after the last element of the container", "[vector]") {
    SECTION("non-const begin and end", "[vector]") {
        jade::vector<int> v{0,1,2,3,4,5,6,7,8,9};
        jade::vector<int>::size_type i = 0;
        for (auto it = v.begin(); it != v.end(); ++it) {
            REQUIRE(*it == v[i++]);
        }
    }
    SECTION("const begin and end", "[vector]") {
        const jade::vector<int> v{0,1,2,3,4,5,6,7,8,9};
        jade::vector<int>::size_type i = 0;
        for (auto it = v.begin(); it != v.end(); ++it) {
            REQUIRE(*it == v[i++]);
        }
    }
    SECTION("cbegin and cend", "[vector]") {
        const jade::vector<int> v{0,1,2,3,4,5,6,7,8,9};
        jade::vector<int>::size_type i = 0;
        for (auto it = v.cbegin(); it != v.cend(); ++it) {
            REQUIRE(*it == v[i++]);
        }
    }
}

TEST_CASE("rbegin returns an iterator to the last element of the container; rend returns an iterator to the element before the first element of the container", "[vector]") {
    SECTION("non-const rbegin and rend", "[vector]") {
        jade::vector<int> v{0,1,2,3,4,5,6,7,8,9};
        jade::vector<int>::size_type i = 9;
        for (auto it = v.rbegin(); it != v.rend(); ++it) {
            REQUIRE(*it == v[i--]);
        }
    }
    SECTION("const rbegin and rend", "[vector]") {
        const jade::vector<int> v{0,1,2,3,4,5,6,7,8,9};
        jade::vector<int>::size_type i = 9;
        for (auto it = v.rbegin(); it != v.rend(); ++it) {
            REQUIRE(*it == v[i--]);
        }
    }
    SECTION("crbegin and crend", "[vector]") {
        const jade::vector<int> v{0,1,2,3,4,5,6,7,8,9};
        jade::vector<int>::size_type i = 9;
        for (auto it = v.crbegin(); it != v.crend(); ++it) {
            REQUIRE(*it == v[i--]);
        }
    }
}

TEST_CASE("empty() signals whether the container is empty or not", "[vector]") {
    jade::vector<int> v;
    REQUIRE(v.empty() == true);

    v.resize(10);
    REQUIRE(v.empty() == true);

    v.push_back(123);
    REQUIRE(v.empty() == false);

    v.resize(0);
    REQUIRE(v.empty() == true);
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
