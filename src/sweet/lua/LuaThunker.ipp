//
// LuaThunker.ipp
// Copyright (c) 2007 - 2010 Charles Baker.  All rights reserved.
//

#ifndef SWEET_LUA_LUATHUNKER_IPP_INCLUDED
#define SWEET_LUA_LUATHUNKER_IPP_INCLUDED

#include "LuaThunker.hpp"
#include "LuaInvoker.ipp"

namespace sweet
{

namespace lua
{

/**
// Thunk a function call with no arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
int LuaThunker<R (*)(), Returner, P0, P1, P2, P3, P4, P5, P6>::function( lua_State* lua_state )
{
    typedef R (*Function)();
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    return LuaInvoker<Returner, Function>::call( lua_state, function );
}

/**
// Thunk a function call with one argument.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class A0, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
int LuaThunker<R (*)(A0), Returner, P0, P1, P2, P3, P4, P5, P6>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (*Function)(A0);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    return LuaInvoker<Returner, Function>::call( lua_state, function, a0 );
}

/**
// Thunk a function call with two arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class A0, class A1, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
int LuaThunker<R (*)(A0, A1), Returner, P0, P1, P2, P3, P4, P5, P6>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (*Function)(A0, A1);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    return LuaInvoker<Returner, Function>::call( lua_state, function, a0, a1 );
}

/**
// Thunk a function call with three arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class A0, class A1, class A2, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
int LuaThunker<R (*)(A0, A1, A2), Returner, P0, P1, P2, P3, P4, P5, P6>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (*Function)(A0, A1, A2);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    return LuaInvoker<Returner, Function>::call( lua_state, function, a0, a1, a2 );
}

/**
// Thunk a function call with four arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class A0, class A1, class A2, class A3, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
int LuaThunker<R (*)(A0, A1, A2, A3), Returner, P0, P1, P2, P3, P4, P5, P6>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (*Function)(A0, A1, A2, A3);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    return LuaInvoker<Returner, Function>::call( lua_state, function, a0, a1, a2, a3 );
}

/**
// Thunk a function call with five arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class A0, class A1, class A2, class A3, class A4, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
int LuaThunker<R (*)(A0, A1, A2, A3, A4), Returner, P0, P1, P2, P3, P4, P5, P6>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (*Function)(A0, A1, A2, A3, A4);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    typename traits<A4>::value_type a4 = LuaConverter<typename traits<A4>::value_type>::to( lua_state, P4 );
    return LuaInvoker<Returner, Function>::call( lua_state, function, a0, a1, a2, a3, a4 );
}

/**
// Thunk a function call with six arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class A0, class A1, class A2, class A3, class A4, class A5, class Returner, int P0, int P1, int P2, int P3, int P4, int P5, int P6>
int LuaThunker<R (*)(A0, A1, A2, A3, A4, A5), Returner, P0, P1, P2, P3, P4, P5, P6>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (*Function)(A0, A1, A2, A3, A4, A5);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    typename traits<A4>::value_type a4 = LuaConverter<typename traits<A4>::value_type>::to( lua_state, P4 );
    typename traits<A5>::value_type a5 = LuaConverter<typename traits<A5>::value_type>::to( lua_state, P5 );
    return LuaInvoker<Returner, Function>::call( lua_state, function, a0, a1, a2, a3, a4, a5 );
}

/**
// Thunk member functions with no arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(), Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)();
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk const member functions with no arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)() const, Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)() const;
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    const T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk member functions with one argument.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0), Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk const member functions with one argument.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0) const, Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0) const;
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    const T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk member functions with two arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1), Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk const member functions with two arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1) const, Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1) const;
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    const T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk member functions with three arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class A2, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1, A2), Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1, A2);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1, a2 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk const member functions with three arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class A2, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1, A2) const, Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1, A2) const;
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    const T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1, a2 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk member functions with four arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class A2, class A3, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1, A2, A3), Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1, A2, A3);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1, a2, a3 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk member functions with four arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class A2, class A3, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1, A2, A3) const, Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1, A2, A3) const;
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    const T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1, a2, a3 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk member functions with five arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1, A2, A3, A4), Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1, A2, A3, A4);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    typename traits<A4>::value_type a4 = LuaConverter<typename traits<A4>::value_type>::to( lua_state, P4 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1, a2, a3, a4 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk const member functions with five arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1, A2, A3, A4) const, Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1, A2, A3, A4) const;
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    const T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    typename traits<A4>::value_type a4 = LuaConverter<typename traits<A4>::value_type>::to( lua_state, P4 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1, a2, a3, a4 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk member functions with six arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1, A2, A3, A4, A5), Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1, A2, A3, A4, A5);
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    typename traits<A4>::value_type a4 = LuaConverter<typename traits<A4>::value_type>::to( lua_state, P4 );
    typename traits<A5>::value_type a5 = LuaConverter<typename traits<A5>::value_type>::to( lua_state, P5 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1, a2, a3, a4, a5 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

/**
// Thunk const member functions with six arguments.
//
// @return
//  The number of values returned (1 or 0 if a void function is being 
//  thunked).
*/
template <class R, class T, class A0, class A1, class A2, class A3, class A4, class A5, class Returner, int PT, int P0, int P1, int P2, int P3, int P4, int P5>
int LuaThunker<R (T::*)(A0, A1, A2, A3, A4, A5) const, Returner, PT, P0, P1, P2, P3, P4, P5>::function( lua_State* lua_state )
{
    using traits::traits;

    typedef R (T::* Function)(A0, A1, A2, A3, A4, A5) const;
    Function function = LuaConverter<Function>::to( lua_state, lua_upvalueindex(1) );
    const T* this_pointer = LuaConverter<T*>::to( lua_state, PT );
    typename traits<A0>::value_type a0 = LuaConverter<typename traits<A0>::value_type>::to( lua_state, P0 );
    typename traits<A1>::value_type a1 = LuaConverter<typename traits<A1>::value_type>::to( lua_state, P1 );
    typename traits<A2>::value_type a2 = LuaConverter<typename traits<A2>::value_type>::to( lua_state, P2 );
    typename traits<A3>::value_type a3 = LuaConverter<typename traits<A3>::value_type>::to( lua_state, P3 );
    typename traits<A4>::value_type a4 = LuaConverter<typename traits<A4>::value_type>::to( lua_state, P4 );
    typename traits<A5>::value_type a5 = LuaConverter<typename traits<A5>::value_type>::to( lua_state, P5 );
    if ( this_pointer )
    {
        return LuaInvoker<Returner, Function>::call( lua_state, function, this_pointer, a0, a1, a2, a3, a4, a5 );
    }
    else
    {
        lua_pushstring( lua_state, "Missing this pointer for call to C++ method" );
        return lua_error( lua_state );
    }
}

}

}

#endif
