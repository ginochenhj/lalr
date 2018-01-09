//
// TestLuaPreprocessor.cpp
// Copyright (c) Charles Baker. All rights reserved.
//

#include <unit/UnitTest.h>
#include <sweet/lua/Lua.hpp>
#include <sweet/error/ErrorPolicy.hpp>
#include <string.h>

using namespace sweet;
using namespace sweet::lua;

SUITE( TestLuaPreprocessor )
{
    struct Fixture
    {
        error::ErrorPolicy error_policy;
        Lua lua;
        
        Fixture()
        : error_policy(),
          lua( error_policy )
        {
            const char* script = "io.write = print;";
            lua.globals()( "print", &Fixture::print );
            lua.call( script, script + strlen(script), "TestLuaPreprocessor" ).end();
        }
        
        static void print()
        {            
        }
    };

    TEST_FIXTURE( Fixture, HelloWorld )
    {
        const char* script = "<?lua for i = 1, 8 do ?>Hello World <?lua print(i) end ?>";
        lua.preprocess( script, script + strlen(script), "HelloWorld" ).end();
    }
    
    TEST_FIXTURE( Fixture, Expression )
    {
        const char* script = "<?lua= 'Hello World' ?>";
        lua.preprocess( script, script + strlen(script), "Expression" ).end();
        script = "<?lua= 32 ?>";
        lua.preprocess( script, script + strlen(script), "Expression" ).end();
    }
    
    TEST_FIXTURE( Fixture, EmbeddedPostLiteralSequence )
    {
        const char* script = "Embedded post literal ']])'";
        lua.preprocess( script, script + strlen(script), "EmbeddedPostLiteralSequence" ).end();
    }
    
    TEST_FIXTURE( Fixture, EmbeddedPostExpressionSequence )
    {
        const char* script = "<?lua= 'Embedded post expression ))' ?>";
        lua.preprocess( script, script + strlen(script), "EmbeddedPostExpressionSequence" ).end();
    }
}
