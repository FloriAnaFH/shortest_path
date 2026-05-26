#include "parser.hpp"
#include "stringUtils.hpp"

#include <cctype>
#include <limits>
#include <stdexcept>
#include <string>

namespace transit {

    Parser::Parser( std::string_view  text ) : text_( text ) {}

    ParsedRoute Parser:: parse( std::size_t lineNumber ) {
        const auto colon = text_.find( ':' );
        if ( colon == std::string_view::npos ) {
            throw std::runtime_error( "Line " + std::to_string( lineNumber ) + ":missing ':' after rout name" );
        }

        ParsedRoute route;
        route.lineName = trimCopy( text_.substr( 0, colon ) );
        if ( route.lineName.empty() ) {
            throw std::runtime_error( "Line " + std::to_string( lineNumber ) + ": route name is empty" );
        }

        pos_ = colon + 1;
        skipSpaces();

        while ( !done() ) {
            route.stations.push_back( readQuotedStation( lineNumber ) );
            skipSpaces();

            if ( done() ) {
                break;
            }

            route.minutesToNext.push_back( readInteger( lineNumber ) );
            skipSpaces();
        }

        if ( route.stations.size() < 2 ) {
            throw std::runtime_error( "Line " + std::to_string( lineNumber) + ": a route must contain at least two stations" );
        }
        if ( route.minutesToNext.size() + 1 != route.stations.size() ) {
            throw std::runtime_error( "line" + std::to_string( lineNumber ) +
                ": expected format: station/time/station/time/.../station");
        }

        return route;
    }

    bool Parser::done() const noexcept {
        return pos_ >= text_.size();
    }

    void Parser::skipSpaces() noexcept {
        while ( !done() && std::isspace( static_cast<unsigned char> ( text_[pos_] ))) {
            ++pos_;
        }
    }

    std::string Parser::readQuotedStation( std::size_t lineNumber ) {
        if ( done() || text_[pos_] != '"' ) {
            throw std::runtime_error( "Line " + std::to_string( lineNumber ) + ": expected quoted station name" );
        }

        ++pos_;
        const auto start = pos_;
        while ( !done() && text_[pos_] != '"' ) {
            ++pos_;
        }
        if ( done() ) {
            throw std::runtime_error( "Line " + std::to_string( lineNumber ) + ": missing closing quote in station name");
        }

        std::string station( text_.substr( start, pos_ - start ) );
        ++pos_;

        if( station.empty()  ) {
            throw::std::runtime_error( "Line " + std::to_string( lineNumber ) + ": station name must not be empty");
        }

        return station;
    }

    int Parser::readInteger( std::size_t lineNumber ) {
        if ( done() || !std::isdigit( static_cast<unsigned char> ( text_[pos_] ))) {
            throw std::runtime_error( "Line " + std::to_string( lineNumber) + ": expected positive travel time" );
        }

        int value = 0;
        while  ( !done() && std::isdigit( static_cast<unsigned char> (  text_[pos_] ))) {
            const int digit = text_[pos_] - '0';
            if ( value >( std::numeric_limits<int>::max() - digit ) / 10 ) {
                throw std::runtime_error( "Line " + std::to_string( lineNumber  ) + ":  travel time is too large" );
            }
            value = value * 10 + digit;
            ++pos_;
        }

        if ( value <= 0 ) {
            throw std::runtime_error( "Line " + std::to_string( lineNumber ) + ": travel time must be positive" );
        }
        return value;
    }

}
