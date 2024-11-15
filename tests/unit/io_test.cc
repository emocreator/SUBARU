#include "../../include/io.h"
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("IO Basic File Operations", "[io]") {
    SECTION("Opening existing test files") {
        REQUIRE_NOTHROW(IO("tests/test.subaru"));
        REQUIRE_NOTHROW(IO("tests/test1.subaru"));
        REQUIRE_NOTHROW(IO("tests/test2.subaru"));
    }

    SECTION("Opening non-existent file throws") {
        REQUIRE_THROWS_AS(IO("tests/nonexistent.subaru"), std::runtime_error);
    }
}

TEST_CASE("IO Reading Operations", "[io]") {
    IO io("tests/test.subaru");

    SECTION("Reading characters sequentially") {
        // Store initial character
        char first = io.peek();
        REQUIRE_FALSE(io.eof());
        io.next();
        REQUIRE(io.peek() != first);
    }

    SECTION("Reset functionality") {
        char first = io.peek();
        io.next();
        io.next();
        io.reset();
        REQUIRE(io.peek() == first);
    }
}

TEST_CASE("IO String Operations", "[io]") {
    IO io("tests/test.subaru");

    SECTION("to_string basic functionality") {
        std::string result = io.to_string(5);
        REQUIRE(result.length() <= 5);
    }
}

TEST_CASE("IO File Navigation", "[io]") {
    IO io("tests/test.subaru");

    SECTION("Seek operations") {
        io.seek(5, std::ios::beg);
        char at_5 = io.peek();
        io.seek(0, std::ios::beg);
        io.next();
        io.next();
        io.next();
        io.next();
        io.next();
        REQUIRE(io.peek() == at_5);
    }
}

TEST_CASE("IO File Switching", "[io]") {
    IO io("tests/test1.subaru");

    SECTION("Switch to another test file") {
        char first_file_char = io.peek();
        io.set("tests/test2.subaru");
        REQUIRE(io.peek() != first_file_char);
    }

    SECTION("Switch to invalid file throws") {
        REQUIRE_THROWS_AS(io.set("tests/nonexistent.subaru"),
                          std::runtime_error);
    }
}
#define CATCH_CONFIG_MAIN
