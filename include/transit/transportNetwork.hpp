#pragma once

#include "stationIndex.hpp"
#include "types.hpp"

#include <filesystem>
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace transit {

    class TransportNetwork {
        public:
            [[ nodiscard ]] static TransportNetwork fromFile( const std::filesystem::path& path );
            [[ nodiscard ]] static TransportNetwork fromStream( std::istream& input, std::string_view sourceName );
            [[ nodiscard ]] std::size_t stationCount() const noexcept;
            [[ nodiscard ]] std::size_t routeCount() const noexcept;
            [[ nodiscard ]] std::size_t segmentCount() const noexcept;
            [[ nodiscard ]] std::vector<std::string> stationNamesSorted() const;

            [[ nodiscard ]] std::optional<Result> shortestPath( std::string_view startName, std::string_view target_name ) const;

        private:
            void addRoute( const ParsedRoute& route );
            [[ nodiscard ]] StationId ensureStation( const std::string& name );
            void addSegment( StationId a, StationId b, int minutes, const std::string& line );

            StationIndex stations_;
            std::vector<std::vector<Edge>> graph_;
            std::size_t routeCount_{};
            std::size_t segmentCount_{};
    };
}
