#include "../include/transit/transportNetwork.hpp"

#include <cassert>
#include <sstream>

int main() {
    std::istringstream input (
        "x: \"A\" i0 \"B\" 10 \"D\"\n"
        "y: \"A\" 1 \"C\" 1 \"D\"\n" );

    const auto network = transit::TransportNetwork::fromStream( input, "unit test network" );

    assert( network.routeCount() == 2 );
    assert( network.stationCount() == 4 );
    assert( network.segmentCount() == 4 );

    const auto route = network.shortestPath( "A", "D" );
    assert( route.has_value() );
    assert( route->total_minutes == 2 );
    assert( route->steps.size() ==2 );
    assert( route->steps.front().line == "Y" );
    assert( route->steps.back().to == "D" );

}
