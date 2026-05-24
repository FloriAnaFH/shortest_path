#pragma once

#include "types.hpp"

#include <cstddef>
#include <string>
#include <string_view>

namespace transit {

    class Parser {
        public:
            explicit Parser( std::string_view text );

            [[ nodiscard ]] ParsedRoute parse( std::size_t lineNumber );

        private:
            [[ nodiscard ]] bool done() const noexcept;
            void skipSpaces() noexcept;
            [[ nodiscard ]] std::string readQuotedStation( std::size_t lineNumber );
            [[ nodiscard ]] int readInteger( std::size_t lineNumber );


            std::string_view text_;
            std::size_t pos_{};
    };
}
