#include "../include/transit/stationIndex.hpp"

#include <algorithm>
#include <utility>

namespace transit {

    StationId StationIndex::idFor( std::string name ) {
        if ( auto it = ids_.find( std::string( name )); it != ids_.end() ) {
            return it->second;
        }

        const StationId id = names_.size();
        names_.push_back( name );
        ids_.emplace( std::move( name ), id );
        return id;
    }

    std::optional<StationId> StationIndex::find( std::string_view name ) const {
        if ( auto it = ids_.find(std::string( name ) ); it != ids_.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    std::string_view StationIndex::name( StationId id ) const {
        return names_.at( id );
    }

    std::size_t StationIndex::size() const noexcept {
        return names_.size();
    }

    std::vector<std::string> StationIndex::sortedNames() const {
        auto result = names_;
        std::sort( result.begin(), result.end() );
        return result;
    }
}
