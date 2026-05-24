#pragma once

#include "types.hpp"

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace transit{

    class StationIndex {
        public:
            [[ nodiscard ]] StationId idFor( std::string name );
            [[ nodiscard ]] std::optional<StationId> find( std::string_view name ) const;
            [[ nodiscard ]] std::string_view name( StationId id ) const;
            [[ nodiscard ]] std::size_t size() const noexcept;
            [[ nodiscard ]] std::vector<std::string> sortedNames() const;

        private:
            std::unordered_map<std::string, StationId> ids_;
            std::vector<std::string> names_;
    };
}
