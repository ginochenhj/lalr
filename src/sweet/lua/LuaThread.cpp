//
// LuaThread.cpp
// Copyright (c) 2008 - 2014 Charles Baker.  All rights reserved.
//

#include "LuaThread.hpp"
#include "LuaFileReader.hpp"
#include "LuaMemoryReader.hpp"
#include "LuaStackGuard.hpp"
#include "LuaValue.hpp"
#include "Lua.hpp"
#include <sweet/build.hpp>

using namespace sweet::lua;

/**
// Constructor.
//
// @param %lua
//  The %Lua virtual machine that this %LuaThread is part of.
*/
LuaThread::LuaThread( Lua& lua )
: lua_( &lua ),
  lua_state_( lua_newthread(lua.get_lua_state()) ),
  add_parameter_helper_( lua_state_, lua_ )
{
    SWEET_ASSERT( lua_ );
    SWEET_ASSERT( lua_state_ );

//
// Set the thread for this LuaThread as a value in the Lua registry using its 
// address as a key.  This keeps a reference to the thread in Lua as long as 
// this LuaThread is allocated and allows the Lua thread to be found from this
// LuaThread object.
//
// The stack is restored to its current position minus 1 to account for the 
// lua_Thread that has been pushed at the top of the stack by the 
// lua_newthread() call in the initializer list.
//
    {
        lua_State* lua_state = lua_->get_lua_state();
        LuaStackGuard guard( lua_state, 1 );
        lua_pushlightuserdata( lua_state, this );
        lua_insert( lua_state, -2 );
        lua_settable( lua_state, LUA_REGISTRYINDEX );
    }
}


/**
// Destructor.
//
// Remove the thread associated with this LuaThread from the Lua registry so
// that it will be garbage collected.  If the lua_State for this LuaThread's 
// Lua object is null then the Lua virtual machine has been destroyed and so
// no other cleanup needs to be done.
*/
LuaThread::~LuaThread()
{
    lua_State* lua_state = lua_->get_lua_state();
    if ( lua_state )
    {
        LuaStackGuard guard( lua_state );
        lua_pushlightuserdata( lua_state, this );
        lua_pushnil( lua_state );
        lua_settable( lua_state, LUA_REGISTRYINDEX );
    }
}

/**
// Get the %Lua virtual machine that this %LuaThread is part of.
//
// @return
//  The %Lua virtual machine.
*/
Lua* LuaThread::get_lua() const
{
    SWEET_ASSERT( lua_ );
    return lua_;
}

/**
// Get the lua_State for this %LuaThread.
//
// @return
//  The lua_State.
*/
lua_State* LuaThread::get_lua_state() const
{
    SWEET_ASSERT( lua_state_ );
    return lua_state_;
}

/**
// Get the LuaThreadState of this %LuaThread.
//
// @return
//  LUA_THREAD_READY if this %LuaThread is ready to execute, 
//  LUA_THREAD_SUSPENDED if this %LuaThread is in the middle of executing a
//  call that yielded, or LUA_THREAD_ERROR if an %error has occured while
//  executing a call on this %LuaThread.
*/
LuaThreadState LuaThread::get_state() const
{
    SWEET_ASSERT( lua_state_ );
    LuaThreadState state = LUA_THREAD_ERROR;
    switch ( lua_status(lua_state_) )
    {
        case 0:
            state = LUA_THREAD_READY;
            break;

        case LUA_YIELD:
            state = LUA_THREAD_SUSPENDED;
            break;

        default:
            state = LUA_THREAD_ERROR;
            break;
    }
    
    return state;
}

/**
// Get the event sink to fire erros at when this LuaThread finishes a call.
//
// @return
//  The event sink or null if there is no event sink to call.
*/
LuaThreadEventSink* LuaThread::event_sink() const
{
    return add_parameter_helper_.event_sink();
}

/**
// Get the context to pass to the events when this LuaThread finishes a call.
//
// @return 
//  The context to pass (possibly null).
*/
void* LuaThread::context() const
{
    return add_parameter_helper_.context();
}

/**
// Turn on Zero Brane Studio debugging for this LuaThread's coroutine.
//
// This function silently does nothing unless the macro 
// SWEET_LUA_MOBDEBUG_ENABLED is defined at compile time or if 
// Lua::mobdebug_start() has not already been called at runtime.
*/
void LuaThread::mobdebug_on()
{
#ifdef SWEET_LUA_MOBDEBUG_ENABLED
    SWEET_ASSERT( lua_ );
    LuaValue* mobdebug = lua_->mobdebug();
    if ( mobdebug )
    {
        call( "on", *mobdebug ).end();
    }
#endif
}

/**
// Turn off Zero Brane Studio debugging for this LuaThread's coroutine.
//
// This function silently does nothing unless the macro 
// SWEET_LUA_MOBDEBUG_ENABLED is defined at compile time or if 
// Lua::mobdebug_start() has not already been called at runtime.
*/
void LuaThread::mobdebug_off()
{
#ifdef SWEET_LUA_MOBDEBUG_ENABLED
    SWEET_ASSERT( lua_ );
    LuaValue* mobdebug = lua_->mobdebug();
    if ( mobdebug )
    {
        call( "off", *mobdebug ).end();
    }
#endif
}

/**
// Fire the returned event and then reset any event sink and context.
*/
void LuaThread::fire_returned()
{
    add_parameter_helper_.fire_returned( this );
}

/**
// Fire the errored event and then reset any event sink and context.
*/
void LuaThread::fire_errored()
{
    add_parameter_helper_.fire_errored( this );
}

/**
// Reset the event sink and context to null.
//
// If, for any reason, it becomes invalid to invoke the return function 
// callback when a Lua call completes this function can be used to reset the
// callback and its context back to null.  The Lua coroutine will still 
// complete its execution but the callback won't be called when 
// LuaThreadPool::end_call() is called.
*/
void LuaThread::reset_event_sink_and_context()
{
    add_parameter_helper_.reset_event_sink_and_context();
}

/**
// Load a script from \e reader and execute it.
//
// @param reader
//  The function to use to read data from.
//
// @param context
//  The context to pass to the reader function.
//
// @param name
//  The name to use when reporting errors.
*/
AddParameter LuaThread::call( lua_Reader reader, void* context, const char* name )
{
    return add_parameter_helper_.call( reader, context, name );
}

/**
// Load a script from a file and execute it.
//
// @param filename
//  The name of the file to load from.
//
// @param name
//  The name to give the imported chunk (to include in debugging information).
//
// @return
//  An %AddParameter helper that provides a convenient syntax for pushing
//  parameters to, calling, and retrieving return values from the chunk.
*/
AddParameter LuaThread::call( const char* filename, const char* name )
{
    LuaFileReader reader( filename, lua_->error_policy() );
    return add_parameter_helper_.call( &LuaFileReader::reader, &reader, name );
}

/**
// Load a script from memory and execute it.
//
// @param first
//  The first character in the string.
//
// @param last
//  One past the last character in the string.
//
// @param name
//  The name to give the imported chunk (to include in debugging information).
//
// @return
//  An %AddParameter helper that provides a convenient syntax for pushing
//  parameters to, calling, and retrieving return values from the chunk.
*/
AddParameter LuaThread::call( const char* first, const char* last, const char* name )
{
    LuaMemoryReader reader( first, last );
    return add_parameter_helper_.call( &LuaMemoryReader::reader, &reader, name );
}

/**
// Call a function in this %LuaThread.
//
// @param function
//  The function to call.
//
// @return
//  An %AddParameter helper object that provides a convenient syntax for 
//  passing parameters and receiving a return value.
*/
AddParameter LuaThread::call( const char* function )
{
    SWEET_ASSERT( function );
    return add_parameter_helper_.call( function );
}

AddParameter LuaThread::call( const LuaValue& function )
{
    return add_parameter_helper_.call( function );
}

/**
// Call a function from the stack in \e lua_state.
//
// This takes the function or table at \e position in the stack of 
// \e lua_state and copies it into this LuaThread's stack before calling that
// function in this LuaThread.
//
// @param lua_state
//  The Lua state to copy the function or table to make the call on from.
//
// @param position
//  The stack index in \e lua_state of the function or table to call on this
//  LuaThread.
//
// @return
//  An %AddParameter helper object that provides a convenient syntax for 
//  passing parameters and receiving a return value.
*/
AddParameter LuaThread::call( lua_State* lua_state, int position )
{
    return add_parameter_helper_.call( lua_state, position );
}

/**
// Load a script from a file and resume it.
//
// @param filename
//  The name of the file to load from.
//
// @param name
//  The name to give the imported chunk (to include in debugging information).
//
// @param line
//  The line number to start numbering at (to include in debugging 
//  information).
//
// @return
//  An %AddParameter helper that provides a convenient syntax for pushing
//  parameters to, calling, and retrieving return values from the chunk.
*/
AddParameter LuaThread::resume( const char* filename, const char* name )
{
    LuaFileReader reader( filename, lua_->error_policy() );
    return add_parameter_helper_.resume( &LuaFileReader::reader, &reader, name );
}

/**
// Load a script from memory and resume it.
//
// @param first
//  The first character in the string.
//
// @param last
//  One past the last character in the string.
//
// @param name
//  The name to give the imported chunk (to include in debugging information).
//
// @param line
//  The line number to start numbering at (to include in debugging 
//  information).
//
// @return
//  An %AddParameter helper that provides a convenient syntax for pushing
//  parameters to, calling, and retrieving return values from the chunk.
*/
AddParameter LuaThread::resume( const char* first, const char* last, const char* name )
{
    LuaMemoryReader reader( first, last );
    return add_parameter_helper_.resume( &LuaMemoryReader::reader, &reader, name );
}

/**
// Resume a function in this %LuaThread.
//
// @param function
//  The function to call.
//
// @return
//  An %AddParameter helper object that provides a convenient syntax for 
//  passing parameters and receiving a return value.
*/
AddParameter LuaThread::resume( const char* function )
{
    SWEET_ASSERT( function );
    return add_parameter_helper_.resume( function );
}

/**
// Resume \e function in this %LuaThread.
//
// @param function
//  A LuaValue object corresponding to a callable value in the Lua virtual 
//  machine.
//
// @return
//  An %AddParameter helper object that provides a convenient syntax for 
//  passing paramters and receiving a return value.
*/
AddParameter LuaThread::resume( const LuaValue& function )
{
    return add_parameter_helper_.resume( function );
}

/**
// Resume a function from the stack in \e lua_state.
//
// This takes the function or table at \e position in the stack of 
// \e lua_state and copies it into this LuaThread's stack before calling that
// function in this LuaThread.
//
// @param lua_state
//  The Lua state to copy the function or table to make the call on from.
//
// @param position
//  The stack index in \e lua_state of the function or table to call on this
//  LuaThread.
//
// @return
//  An %AddParameter helper object that provides a convenient syntax for 
//  passing parameters and receiving a return value.
*/
AddParameter LuaThread::resume( lua_State* lua_state, int position )
{
    return add_parameter_helper_.resume( lua_state, position );
}

/**
// Resume a call that previously yielded in this %LuaThread.
//
// It is assumed that this %LuaThread is in the LUA_THREAD_SUSPENDED state 
// when this call is made.  This means that a call must have been started
// by using one of the other resume functions that takes arguments.
//
// @return
//  An %AddParameter helper object that provides a convenient syntax for 
//  passing parameters and receiving a return value.
*/
AddParameter LuaThread::resume()
{
    return add_parameter_helper_.resume();
}
