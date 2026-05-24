#include "../include/transit/application.hpp"

#include <exception>
#include <iostream>

int maint( int argc, char* argv[] ) {
    try {
        return transit::run( argc, argv );
    } catch ( const std::exception& ex ) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
}
