//
// LexerErrorPolicy.cpp
// Copyright (c) 2010 - 2011 Charles Baker.  All rights reserved.
//

#include "stdafx.hpp"
#include "LexerErrorPolicy.hpp"

using namespace sweet;
using namespace sweet::lexer;

/**
// Destructor.
*/
LexerErrorPolicy::~LexerErrorPolicy()
{
}

void LexerErrorPolicy::lexer_error( int /*line*/, const error::Error& /*error*/ )
{
}

void LexerErrorPolicy::lexer_vprintf( const char* /*format*/, va_list /*args*/ )
{
}
