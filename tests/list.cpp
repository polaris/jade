#include "catch.hpp"

#include "../include/list.h"

TEST_CASE("a new list is empty", "[list]") {
    jade::list<int> lst;
    REQUIRE(lst.empty());
}

TEST_CASE("new elements can be pushed to the back", "[list]") {
    jade::list<int> lst;
    lst.push_back(1);
    REQUIRE(!lst.empty());
    lst.push_back(2);
    REQUIRE(!lst.empty());
    lst.push_back(3);
    REQUIRE(!lst.empty());
}

TEST_CASE("elements can be popped from the back", "[list]") {
    jade::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    int value = 0;
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 1);
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 2);
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 3);
    REQUIRE(!lst.pop_front(value));
}

TEST_CASE("new elements can be pushed to the front", "[list]") {
    jade::list<int> lst;
    lst.push_front(1);
    REQUIRE(!lst.empty());
    lst.push_front(2);
    REQUIRE(!lst.empty());
    lst.push_front(3);
    REQUIRE(!lst.empty());
}

TEST_CASE("elements can be popped from the front", "[list]") {
    jade::list<int> lst;
    lst.push_front(1);
    lst.push_front(2);
    lst.push_front(3);

    int value = 0;
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 3);
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 2);
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 1);
    REQUIRE(!lst.pop_front(value));
}

TEST_CASE("push to back and pop from front twice", "[list]") {
    jade::list<int> lst;
    int value = 0;
    lst.push_back(1);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 1);
    REQUIRE(lst.empty());
    lst.push_back(2);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 2);
    REQUIRE(lst.empty());
}

TEST_CASE("push to front and pop from back twice", "[list]") {
    jade::list<int> lst;
    int value = 0;
    lst.push_front(1);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_back(value));
    REQUIRE(value == 1);
    REQUIRE(lst.empty());
    lst.push_front(2);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_back(value));
    REQUIRE(value == 2);
    REQUIRE(lst.empty());
}

TEST_CASE("push to front and pop from front then push to back and pop from back", "[list]") {
    jade::list<int> lst;
    int value = 0;
    lst.push_front(1);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 1);
    REQUIRE(lst.empty());
    lst.push_back(2);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_back(value));
    REQUIRE(value == 2);
    REQUIRE(lst.empty());
}

TEST_CASE("push to back and pop from back then push to front and pop from front", "[list]") {
    jade::list<int> lst;
    int value = 0;
    lst.push_back(1);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_back(value));
    REQUIRE(value == 1);
    REQUIRE(lst.empty());
    lst.push_front(2);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 2);
    REQUIRE(lst.empty());
}

TEST_CASE("insert an element to the beginning of a list", "[list]") {
    jade::list<int> lst;
    int value = 0;
    lst.insert(lst.begin(), 1);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_back(value));
    REQUIRE(value == 1);
    REQUIRE(lst.empty());
}

TEST_CASE("insert multiple elements to the beginning of a list 1", "[list]") {
    jade::list<int> lst;
    int value = 0;
    lst.insert(lst.begin(), 1);
    lst.insert(lst.begin(), 2);
    lst.insert(lst.begin(), 3);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_back(value));
    REQUIRE(value == 1);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_back(value));
    REQUIRE(value == 2);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_back(value));
    REQUIRE(value == 3);
    REQUIRE(lst.empty());
}

TEST_CASE("insert multiple elements to the beginning of a list 2", "[list]") {
    jade::list<int> lst;
    int value = 0;
    lst.insert(lst.begin(), 1);
    lst.insert(lst.begin(), 2);
    lst.insert(lst.begin(), 3);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 3);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 2);
    REQUIRE(!lst.empty());
    REQUIRE(lst.pop_front(value));
    REQUIRE(value == 1);
    REQUIRE(lst.empty());
}

TEST_CASE("iterator iterates over all elements", "[list]") {
    jade::list<int> lst;
    int value = 0;

    lst.insert(lst.begin(), 1);
    lst.insert(lst.begin(), 2);
    lst.insert(lst.begin(), 3);

    jade::list<int>::iterator itr = std::begin(lst);
    REQUIRE(*itr == 3);
    ++itr;
    REQUIRE(*itr == 2);
    ++itr;
    REQUIRE(*itr == 1);
}

TEST_CASE("insert an element inbetween existing elements", "[list]") {
    jade::list<int> lst;
    int value = 0;

    lst.insert(lst.end(), 1);
    lst.insert(lst.end(), 3);
    lst.insert(lst.end(), 5);
    
    jade::list<int>::iterator itr = std::begin(lst);
    ++itr;
    lst.insert(itr, 2);

    itr = std::begin(lst);
    ++itr;
    ++itr;
    ++itr;
    lst.insert(itr, 4);
    
    itr = std::begin(lst);
    REQUIRE(*itr == 1);
    ++itr;
    REQUIRE(*itr == 2);
    ++itr;
    REQUIRE(*itr == 3);
    ++itr;
    REQUIRE(*itr == 4);
    ++itr;
    REQUIRE(*itr == 5);
}
