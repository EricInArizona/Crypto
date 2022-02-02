// Copyright Eric Chauvin 2020 - 2022.


#pragma once


// Basic type definitions.



// The C and C++ standards don't specify an
// exact bit size for types.
// See MainApp::basicThingsAreRight().


// typedef char Int8;
// typedef unsigned char Uint8;
// typedef unsigned char Char8;
// typedef unsigned short Char16;
// typedef short Int16;

// This might be a UTF16 character or a
// byte that is not meant to have a sign bit.
typedef unsigned short UTF16;

typedef int Int32;
// typedef unsigned int Uint32;
typedef long long Int64; // A constant 123LL
                         // is Int64.

typedef unsigned long long ArrayU64; // 123ULL

typedef float Float32;
typedef double Float64;



/*
bool basicThingsAreRight()
  {
  printf( "Int8 size: %d\n", (int)sizeof( Int8 ) );
  printf( "Char8 size: %d\n", (int)sizeof( Char8 ) );
  printf( "Char16 size: %d\n", (int)sizeof( Char16 ) );
  printf( "Int16 size: %d\n", (int)sizeof( Int16 ) );
  printf( "Uint16 size: %d\n", (int)sizeof( Uint16 ) );
  printf( "Int32 size: %d\n", (int)sizeof( Int32 ) );
  printf( "Uint32 size: %d\n", (int)sizeof( Uint32 ) );
  printf( "Int64 size: %d\n", (int)sizeof( Int64 ) );
  printf( "Uint64 size: %d\n", (int)sizeof( Uint64 ) );
  printf( "Float32 size: %d\n", (int)sizeof( Float32 ) );
  printf( "Float64 size: %d\n", (int)sizeof( Float64 ) );

  // Float128

  if( sizeof( Int8 ) != 1 )
    return false;

  if( sizeof( Char8 ) != 1 )
    return false;

  if( sizeof( Char16 ) != 2 )
    return false;

  if( sizeof( Int16 ) != 2 )
    return false;

  if( sizeof( Uint16 ) != 2 )
    return false;

  if( sizeof( Int32 ) != 4 )
    return false;

  if( sizeof( Uint32 ) != 4 )
    return false;

  if( sizeof( Int64 ) != 8 )
    return false;

  if( sizeof( Uint64 ) != 8 )
    return false;

  if( sizeof( Float32 ) != 4 )
    return false;

  if( sizeof( Float64 ) != 8 )
    return false;

  return true;
  }
*/
