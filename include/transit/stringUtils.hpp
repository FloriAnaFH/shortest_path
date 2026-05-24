#pragma once

#include <string>
#include <string_view>

namespace transit {

    [[ nodiscard ]] std::string trimCopy( std::string_view text );
    [[ nodiscard ]] std::string lowerCopy( std::string_view text );
    [[ nodiscard ]] bool contains( std::string_view haystack, std::string_view needle ); //case insensitive
}
