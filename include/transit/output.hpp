#pragma once

#include "transportNetwork.hpp"
#include "types.hpp"

#include <iosfwd>
#include <optional>
#include <string_view>
#include <vector>

namespace transit {

    [[ nodiscard ]] std::vector<CompactLeg> compactByLine( const std::vector<Step>& steps );

    void printSummary( std::ostream& out, const TransportNetwork& network );
    void printRoute( std::ostream& out, const Result& result );
    void printMatchingStations( std::ostream& out, const TransportNetwork& network, std::optional<std::string_view> filter );
    void printUsage( std::ostream& out, std::string_view executable );
}
