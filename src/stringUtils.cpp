#include "stringUtils.hpp"

#include <algorithm>
#include <cctype>

namespace transit {

    std::string trimCopy( std::string_view text ) {
        auto isNotSpace = [] ( unsigned char ch ) { return !std::isspace(ch); };

        const auto first = std::find_if( text.begin(), text.end(), isNotSpace );
        if ( first == text.end() ) {
            return {};
        }

        const auto last = std::find_if( text.rbegin(), text.rend(), isNotSpace).base();
        return std::string( first, last );
    }

    std::string lowerCopy( std::string_view text ) {
        std::string result;
        result.reserve( text.size() );
        for ( unsigned char ch : text ) {
            result.push_back( static_cast<char>(std::tolower(ch ) ));
        }
        return result;
    }

    bool contains( std::string_view haystack, std::string_view needle ) {
        return lowerCopy( haystack ).find( lowerCopy( needle )) != std::string::npos;
    }
}
