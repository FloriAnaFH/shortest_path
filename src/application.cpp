#include "application.hpp"
#include "output.hpp"
#include "transportNetwork.hpp"

#include <iostream>
#include <optional>
#include <string_view>

namespace transit {

    int run( int argc, char* argv[] ) {
        const std::string_view executable = argc > 0 ? argv[0] : "verkehrsnetz";

        if ( argc == 1 || ( argc >= 2 &&  std::string_view( argv[1]) == "--help" ) ) {
            printUsage( std::cout, executable );
            return 0;
        }

        if ( argc == 3 && std::string_view( argv[1] ) == "--summary" ) {
            const auto network = TransportNetwork::fromFile( argv[2] );
            printSummary( std::cout, network );
            return 0;
        }

        if ( (argc == 3 || argc == 4 ) && std::string_view( argv[1] ) == "--list-stations" ) {
            const auto network = TransportNetwork::fromFile( argv[2] );
            std::optional<std::string_view> filter;
            if ( argc == 4 ) {
                filter = std::string_view( argv[3] );
            }
            printMatchingStations(std::cout, network,filter );
            return 0;
        }

        if ( argc == 4 ) {
            const auto network = TransportNetwork::fromFile(argv[1] );
            const std::string_view start = argv[2];
            const std::string_view target = argv[3];

            const auto result = network.shortestPath( start, target );
            if ( !result ) {
                std::cerr << "No route found. View available stations with --list-stations.\n";
                return 2;
            }

            printRoute( std::cout, *result );
            return 0;
        }

        printUsage( std::cerr, executable );
        return 1;
    }
}
