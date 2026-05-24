#include "../include/transit/transportNetwork.hpp"

#include "../include/transit/parser.hpp"
#include "../include/transit/stringUtils.hpp"

#include <algorithm>
#include <fstream>
#include <functional>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <utility>


namespace transit {

    TransportNetwork TransportNetwork::fromFile( const std::filesystem::path& path ) {
        std::ifstream input( path );
        if ( !input ) {
            throw::std::runtime_error( "Cannot open file: " + path.string() );
        }

        return fromStream( input, path.string() );
    }

    TransportNetwork TransportNetwork::fromStream(std::istream &input, std::string_view sourceName  ) {
        TransportNetwork network;
        std::string line;
        std::size_t lineNumber = 0;

        while ( std::getline( input, line )) {
            ++lineNumber;
            if ( trimCopy( line ).empty() ) {
                continue;
            }

        ParsedRoute route = Parser( line ).parse( lineNumber  );
        network.addRoute( route );
        }

        if ( network.routeCount_ == 0 ) {
            throw std::runtime_error( "Input source does not contain any route names: " + std::string( sourceName ));
        }

        return network;
    }

    std::size_t TransportNetwork::stationCount() const noexcept {
        return stations_.size();
    }

    std::size_t TransportNetwork::routeCount() const noexcept {
        return routeCount_;
    }

    std::size_t TransportNetwork::segmentCount() const noexcept {
        return segmentCount_;
    }

    std::vector<std::string> TransportNetwork::stationNamesSorted() const {
        return stations_.sortedNames();
    }

    std::optional<Result> TransportNetwork::shortestPath( std::string_view startName, std::string_view targetName ) const {
        const auto start = stations_.find( startName );
        const auto target = stations_.find(targetName );
        if ( !start || !target ) {
            return std::nullopt;
        }

        struct Previous {
            StationId from{};
            std::string line;
            int minutes{};
        };

        const int infinity = std::numeric_limits<int>::max() / 4;
        std::vector<int> distance( stationCount(), infinity );
        std::vector<std::optional<Previous>> previous( stationCount() );

        using QueueEntry = std::pair<int, StationId>;\
        std::priority_queue<QueueEntry,std::vector<QueueEntry>, std::greater<>> queue;

        distance[*start] = 0;
        queue.emplace( 0, *start );

        while ( !queue.empty() ) {
            const auto [currentDistance, current] = queue.top();
            queue.pop();

            if ( currentDistance != distance[current] ) {
                continue;
            }
            if ( current == *target )  {
                break;
            }
            for ( const Edge& edge : graph_[current]) {
                const int candidate = currentDistance + edge.minutes;
                if ( candidate < distance[edge.to] ) {
                    distance[edge.to] = candidate;
                    previous[edge.to] = Previous{ current, edge.line, edge.minutes };
                    queue.emplace( candidate, edge.to );
                }
            }
        }

        if ( distance[*target] == infinity ) {
            return std::nullopt;
        }

        Result result;
        result.total_minutes = distance[*target];

        for ( StationId at = *target; at != *start; ) {
            const auto& prev = previous[at];
            if ( !prev ) {
                throw std::logic_error( "Broken predecessor chain after Dijkstra" );
            }

            result.steps.push_back( Step {
                std::string( stations_.name(prev->from )),
                std::string( stations_.name( at )),
                prev->line,
                prev->minutes,
            });
            at = prev->from;
        }

        std::reverse( result.steps.begin(), result.steps.end() );
        return result;
    }

    void TransportNetwork::addRoute( const ParsedRoute& route ) {
        ++routeCount_;

        for ( std::size_t i = 0; i + 1 < route.stations.size(); ++i ) {
            const StationId from = ensureStation( route.stations[i] );
            const StationId to = ensureStation( route.stations[i+1] );
            const int minutes = route.minutesToNext[i];

            addSegment( from, to, minutes, route.lineName );
        }
    }

    StationId TransportNetwork::ensureStation( const std::string& name ) {
        const StationId id = stations_.idFor( name );
        if ( id >= graph_.size() ) {
            graph_.resize( id + 1 );
        }
        return id;
    }

    void TransportNetwork::addSegment( StationId a, StationId b, int minutes, const std::string& line ) {
        graph_[a].push_back( Edge{ b, minutes, line } );
        graph_[b].push_back( Edge{ a, minutes, line } );
        ++segmentCount_;
    }

} //namespace
