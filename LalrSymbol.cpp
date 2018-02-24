//
// LalrSymbol.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include "LalrSymbol.hpp"
#include "LalrProduction.hpp"
#include "assert.hpp"

using std::set;
using std::vector;
using std::shared_ptr;
using namespace sweet::lalr;

LalrSymbol::LalrSymbol( const std::string& lexeme )
: lexeme_( lexeme ),
  identifier_(),
  symbol_type_( SYMBOL_NULL ),
  lexeme_type_( LEXEME_NULL ),
  associativity_( ASSOCIATE_NONE ),
  precedence_( 0 ),
  productions_()
{
}

const std::string& LalrSymbol::lexeme() const
{
    return lexeme_;
}

const std::string& LalrSymbol::identifier() const
{
    return identifier_;
}

SymbolType LalrSymbol::symbol_type() const
{
    return symbol_type_;
}

LexemeType LalrSymbol::lexeme_type() const
{
    return lexeme_type_;
}

Associativity LalrSymbol::associativity() const
{
    return associativity_;
}

int LalrSymbol::precedence() const
{
    return precedence_;
}

int LalrSymbol::line() const
{
    return line_;
}

int LalrSymbol::index() const
{
    return index_;
}

bool LalrSymbol::nullable() const
{
    return nullable_;
}

const std::set<const LalrSymbol*>& LalrSymbol::first() const
{
    return first_;
}

const std::set<const LalrSymbol*>& LalrSymbol::follow() const
{
    return follow_;
}

const std::vector<LalrProduction*>& LalrSymbol::productions() const
{
    return productions_;
}

/**
// Get the implicit terminal for this symbol.
//
// The implicit terminal for this symbol is the single symbol on the 
// right-hand side of its single, action-less production.
//
// There is an implicit terminal for this symbol only if this symbol has a
// single, action-less production with a single symbol on its right-hand side.
// In that situation that this symbol is simply an alias for the single 
// terminal symbol on the right-hand side.
//
// @return
//  The implict terminal for this symbol or null if this symbol doesn't have
//  an implicit terminal.
*/
LalrSymbol* LalrSymbol::implicit_terminal() const
{
    LalrSymbol* implicit_terminal_symbol = nullptr;    
    if ( productions_.size() == 1 )
    {
        const LalrProduction* production = productions_.front();
        SWEET_ASSERT( production );
        if ( production->length() == 1 && !production->action() )
        {
            LalrSymbol* symbol = production->symbols().front();
            if ( symbol->symbol_type() == SYMBOL_TERMINAL )
            {
                implicit_terminal_symbol = symbol;
            }
        }
    }
    return implicit_terminal_symbol;
}


void LalrSymbol::set_lexeme( const std::string& lexeme )
{
    lexeme_ = lexeme;
}

void LalrSymbol::set_identifier( const std::string& identifier )
{
    identifier_ = identifier;
}

void LalrSymbol::set_symbol_type( SymbolType symbol_type )
{
    SWEET_ASSERT( symbol_type >= SYMBOL_NULL && symbol_type < SYMBOL_TYPE_COUNT );
    symbol_type_ = symbol_type;
}

void LalrSymbol::set_lexeme_type( LexemeType lexeme_type )
{
    SWEET_ASSERT( lexeme_type >= LEXEME_NULL && lexeme_type < LEXEME_TYPE_COUNT );
    lexeme_type_ = lexeme_type;
}

void LalrSymbol::set_associativity( Associativity associativity )
{
    SWEET_ASSERT( associativity >= ASSOCIATE_NONE && associativity <= ASSOCIATE_RIGHT );
    associativity_ = associativity;
}

void LalrSymbol::set_precedence( int precedence )
{
    SWEET_ASSERT( precedence >= 0 );
    precedence_ = precedence;
}

void LalrSymbol::set_line( int line )
{
    SWEET_ASSERT( line >= 0 );
    line_ = line;
}

void LalrSymbol::set_index( int index )
{
    SWEET_ASSERT( index >= 0 );
    index_ = index;
}

void LalrSymbol::set_nullable( bool nullable )
{
    nullable_ = nullable;
}

void LalrSymbol::append_production( LalrProduction* production )
{
    SWEET_ASSERT( production );
    productions_.push_back( production );
}

/**
// Calculate the identifier for this symbol.
*/
void LalrSymbol::calculate_identifier()
{
    SWEET_ASSERT( !lexeme_.empty() );

    static const char* CHARACTER_NAMES [] =
    {
        "nul",
        "soh",
        "stx",
        "etx",
        "eot",
        "enq",
        "ack",
        "bel",
        "bs",
        "tab",
        "lf",
        "vt",
        "ff",
        "cr",
        "so",
        "si",
        "dle",
        "dc1",        
        "dc2",        
        "dc3",
        "dc4",
        "nak",
        "syn",
        "etb",
        "can",
        "em",
        "sub",
        "esc",
        "fs",
        "gs",
        "rs",
        "us",
        "space",
        "bang",
        "double_quote",
        "hash",
        "dollar",
        "percent",
        "amp",
        "single_quote",
        "left_paren",
        "right_paren",
        "star",
        "plus",
        "comma",
        "minus",
        "dot",
        "slash",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "colon",
        "semi_colon",
        "lt",
        "eq",
        "gt",
        "question",
        "at",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
        "left_square_paren",
        "backslash",
        "right_square_paren",
        "hat",
        "underscore",
        "backtick",
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
        "left_curly_brace",
        "pipe",
        "right_curly_brace",
        "tilde",
        "del"
    };

    identifier_.reserve( lexeme_.size() );
    std::string::const_iterator i = lexeme_.begin();     
    while ( i != lexeme_.end() )
    {
        if ( isalnum(*i) || *i == '_' )
        {
            identifier_.push_back( *i );
            ++i;
        }
        else
        {
            if ( i != lexeme_.begin() )
            {
                identifier_.append( "_" );
            }

            int character = *i;
            SWEET_ASSERT( character >= 0 && character < 128 );
            identifier_.append( CHARACTER_NAMES[character] );

            ++i;
            if ( i != lexeme_.end() )
            {
                identifier_.append( "_" );             
            }
        }
    }

    if ( symbol_type_ == SYMBOL_TERMINAL )
    {
        identifier_.append( "_terminal" );
    }    
}

/**
// Replace this symbol's identifier, line, precedence, and associativity 
// with those from *non_terminal_symbol*.  This is done as an optimization
// to remove redundant reductions for implicit terminal symbols.  See 
// `Grammar::calculate_implicit_terminal_symbols()`.
//
// This symbol is assumed to be of type `SYMBOL_TERMINAL`.
//
// @param non_terminal_symbol
//  The non terminal symbol to replace the identifier, line, precedence, and
//  associativity for this symbol with (assumed not null and of type 
//  `SYMBOL_NON_TERMINAL`).
*/
void LalrSymbol::replace_by_non_terminal( const LalrSymbol* non_terminal_symbol )
{
    SWEET_ASSERT( symbol_type() == SYMBOL_TERMINAL );
    SWEET_ASSERT( non_terminal_symbol );    
    SWEET_ASSERT( non_terminal_symbol->symbol_type() == SYMBOL_NON_TERMINAL );        
    identifier_ = non_terminal_symbol->lexeme_;
    line_ = non_terminal_symbol->line_;
    precedence_ = non_terminal_symbol->precedence_;
    associativity_ = non_terminal_symbol->associativity_;
}

/**
// Add a symbol to the first set of this symbol.
//
// @param symbol
//  The symbol to add to the first set of this symbol.
//
// @return
//  The number of symbols added (0 or 1).
*/
int LalrSymbol::add_symbol_to_first( const LalrSymbol* symbol )
{
    SWEET_ASSERT( symbol );
    return first_.insert( symbol ).second ? 1 : 0;
}

/**
// Add one or more symbols to the first set of this symbol.
//
// @param symbols
//  The symbols to add to the first set of this symbol.
//
// @return
//  The number of symbols added.
*/
int LalrSymbol::add_symbols_to_first( const std::set<const LalrSymbol*>& symbols )
{
    size_t original_size = first_.size();
    first_.insert( symbols.begin(), symbols.end() );
    return first_.size() - original_size;
}

/**
// Add a symbol to the follow set of this symbol.
//
// @param symbol
//  The symbol to add to the follow set of this symbol.
//
// @return
//  The number of symbols added (0 or 1).
*/
int LalrSymbol::add_symbol_to_follow( const LalrSymbol* symbol )
{
    SWEET_ASSERT( symbol );
    return follow_.insert( symbol ).second ? 1 : 0;
}

/**
// Add symbols to the follow set of this symbol.
//
// @param symbols
//  The symbols to add to the follow set of this symbol.
//
// @return
//  The number of symbols added.
*/
int LalrSymbol::add_symbols_to_follow( const std::set<const LalrSymbol*>& symbols )
{
    size_t original_size = follow_.size();
    follow_.insert( symbols.begin(), symbols.end() );
    return follow_.size() - original_size;
}

/**
// Calculate the first set and nullable for this symbol.
//
// @return
//  The number of symbols added to the first set and plus one if nullable
//  changed for this symbol.
*/
int LalrSymbol::calculate_first()
{
    int added = 0;
    if ( symbol_type_ == SYMBOL_NON_TERMINAL )
    {
        for ( vector<LalrProduction*>::const_iterator i = productions_.begin(); i != productions_.end(); ++i )
        {
            const LalrProduction* production = *i;
            SWEET_ASSERT( production );  
                  
            const vector<LalrSymbol*>& symbols = production->symbols();
            vector<LalrSymbol*>::const_iterator j = symbols.begin(); 
            while ( j != symbols.end() && (*j)->nullable() )
            {
                const LalrSymbol* symbol = *j;
                SWEET_ASSERT( symbol );
                added += add_symbols_to_first( symbol->first() );
                ++j;
            }
            
            if ( j != symbols.end() )
            {
                const LalrSymbol* symbol = *j;
                SWEET_ASSERT( symbol );
                added += add_symbols_to_first( symbol->first() );
            }
            else
            {
                added += nullable_ ? 0 : 1;
                nullable_ = true;
            }
        }
    }
    else
    {
        added += add_symbol_to_first( this );
    }
    return added;
}

/**
// Calculate the follow set for this symbol.
//
// @return
//  The number of symbols added to the follow set.
*/
int LalrSymbol::calculate_follow()
{
    int added = 0;
    for ( vector<LalrProduction*>::const_iterator i = productions_.begin(); i != productions_.end(); ++i )
    {
        const LalrProduction* production = *i;
        SWEET_ASSERT( production );
                    
        const vector<LalrSymbol*>& symbols = production->symbols();
        if ( !symbols.empty() )
        {
            vector<LalrSymbol*>::const_reverse_iterator j = symbols.rbegin(); 
            LalrSymbol* symbol = *j;
            added += symbol->add_symbols_to_follow( follow() );
            ++j;
        
            while ( j != symbols.rend() && symbol->nullable() )
            {
                LalrSymbol* previous_symbol = *j;
                SWEET_ASSERT( previous_symbol );
                added += previous_symbol->add_symbols_to_follow( symbol->first() );
                added += previous_symbol->add_symbols_to_follow( follow() );
                symbol = previous_symbol;
                ++j;                
            }
            
            while ( j != symbols.rend() )
            {
                LalrSymbol* previous_symbol = *j;
                SWEET_ASSERT( previous_symbol );
                added += previous_symbol->add_symbols_to_follow( symbol->first() );
                ++j;
            }
        }
    }
    return added;
}
