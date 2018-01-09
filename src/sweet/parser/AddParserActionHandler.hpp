#ifndef SWEET_PARSER_ADDHANDLER_HPP_INCLUDED
#define SWEET_PARSER_ADDHANDLER_HPP_INCLUDED

#include <functional>

namespace sweet
{

namespace parser
{

class ParserSymbol;
template <class Iterator, class UserData, class Char, class Traits, class Allocator> class Parser;

/**
// A helper that provides a convenient syntax for adding handlers to a %Parser.
*/
template <class Iterator, class UserData, class Char, class Traits, class Allocator>
class AddParserActionHandler
{
    typedef std::function<void (Iterator* begin, Iterator end, std::basic_string<Char, Traits, Allocator>* lexeme, const ParserSymbol** symbol)> LexerActionFunction;
    typedef std::function<UserData (const ParserSymbol* symbol, const ParserNode<UserData, Char, Traits, Allocator>* start, const ParserNode<UserData, Char, Traits, Allocator>* finish)> ParserActionFunction;

    Parser<Iterator, UserData, Char, Traits, Allocator>* parser_; ///< The Parser to add handlers to.

    public:
        AddParserActionHandler( Parser<Iterator, UserData, Char, Traits, Allocator>* parser );
        const AddParserActionHandler& default_action( ParserActionFunction function ) const;
        const AddParserActionHandler& operator()( const char* identifier, ParserActionFunction function ) const;
};

}

}

#endif
