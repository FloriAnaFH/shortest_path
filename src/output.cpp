#include "../include/transit/output.hpp"

#include "../include/transit/stringUtils.hpp"

#include <iostream>

namespace transit {

    std::vector<CompactLeg> compactByLine( const std::vector<Step>& steps ) {
        std::vector<CompactLeg> legs;
        for ( const Step& step : steps ) {
            if ( !legs.empty() && legs.back().line == step.line ) {
                legs.back().to = step.to;
                legs.back().minutes = step.minutes;
                ++legs.back().segments;
            } else {
                legs.push_back( CompactLeg{ step.line, step.from, step.to, step.minutes } );
            }
        }
        return legs;
    }

   void printSummary( std::ostream& out, const TransportNetwork& network ) {
       out  << "Netork loaded successfully\n"
            << "Routes: " << network.routeCount() << "\n"
            << "Stations " << network.stationCount() << "\n"
            << "Segments: " << network.segmentCount() << "\n";
   }

   void printRoute( std::ostream& out, const Result& result ) {
       out << "Shortest path: " << result.total_minutes << " minutes\n";

       const auto legs = compactByLine( result.steps );
       for ( std::size_t i = 0; i < legs.size(); ++i ) {
              const CompactLeg& leg = legs[i];
              out << ( i + 1 ) << ". Take " << leg.line << " from \"" << leg.from
                  << "\" to \"" << leg.to << "\" (" << leg.minutes << " min, "
                  << leg.segments << ( leg.segments == 1 ? " segment" : " segments" ) << ")\n";
          }
   }

   void printMatchingStations( std::ostream &out, const TransportNetwork &network, std::optional<std::string_view> filter ) {
       for ( const std::string& station : network.stationNamesSorted() ) {
           if ( !filter || contains(station, *filter ) ) {
               out << station << "\n";
           }
       }
   }

   void printUsage( std::ostream& out, std::string_view executable ) {
       out  << "Usage:\n"
            << "  " << executable << " DATA_FILE START_STATION TARGET_STATION\n"
            << "  " << executable << " --summary DATA_FILE\n"
            << "  " << executable << " --list-stations DATA_FILE [FILTER]\n"
            << "\nExamples:\n"
            << "  " << executable << " data/ADS_Programmieraufgabe3_WienerVerkehrsNetz.txt \"Leopoldau\" \"Stephansplatz\"\n"
            << "  " << executable << " --list-stations data/ADS_Programmieraufgabe3_WienerVerkehrsNetz.txt west\n";
   }
} // namespace
