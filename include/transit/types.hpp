#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace transit {

    using StationId = std::size_t;

    struct Edge {
        StationId to {};
        int minutes {};
        std::string line;
    };

    struct Step {
        std::string from;
        std::string to;
        std::string line;
        int minutes;

    };

    struct Result {
        int total_minutes {};
        std::vector<Step> steps;
    };

    struct ParsedRoute {
        std::string lineName;
        std::vector<std::string> stations;
        std::vector<int> minutesToNext;
    };

    struct CompactLeg {
        std::string line;
        std::string from;
        std::string to;
        int minutes{};
        int segments{};
    };
}
