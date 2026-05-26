#include "../include/transit/parser.hpp"

#include <cassert>
#include <stdexcept>
#include <iostream>

namespace {

    void testValidRoute() {
        auto route = transit::Parser( R"(U1: "A" 2 "B" 3 "C")" ).parse(1);

        assert( route.lineName == "U1" );
        assert((  route.stations == std::vector<std::string> { "A", "B", "C" }));
        assert(( route.minutesToNext == std::vector<int>{2 ,3 }));
    }

    void rejectMissingColon() {
        bool thrown = false;
        try{
            static_cast<void> (transit::Parser( R"(U1 "A" 2 "B")" ).parse( 1 ));
        } catch ( const std::runtime_error& ) {
            thrown = true;
        }
        assert( thrown );
    }

    void rejectNonPositiveWeight() {
        bool thrown = false;
        try {
            static_cast<void> (transit::Parser( R"(U1: "A" 0 "B")" ).parse( 1 ));

        } catch ( const std::runtime_error& ) {
            thrown = true;
        }
        assert( thrown );
    }
} //namespace

    int main() {
        testValidRoute();
        rejectMissingColon();
        rejectNonPositiveWeight();
    std::cout << "All tests passed!\n";
    }
