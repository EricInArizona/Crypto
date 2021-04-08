// Copyright Eric Chauvin, 2021.



#include "MainApp.h"
#include "FileUtil.h"
#include "Base10Number.h"
#include "Str.h"
#include "Integer.h"

// Make Windows objects.
// #include <Windows.h>



int MainApp::mainLoop( int argc, char* argv[] )
{
try
{
if( !basicThingsAreRight())
  {
  FileUtil::uPrintf(
      "basicThingsAreRight() returned false.\n" );

  return 1; // Some error code.
  }

FileUtil::uPrintf(
              "Programming by Eric Chauvin.\n" );

FileUtil::uPrintf( "Version date: " );
FileUtil::uPrintf( getVersionStr() );
FileUtil::uPrintf( "\n" );

Str oneS( "123456789" );
Str twoS( "987654" );

FileUtil::uPrintf( "Created strings.\n" );

Base10Number b1( oneS );
Base10Number b2( twoS );

FileUtil::uPrintf( "Created Base 10 numbers.\n" );

Integer int1;
int1.setToOne();

FileUtil::uPrintf( "Created Integer.\n" );

return 0;
}
catch( const char* str )
  {
  FileUtil::uPrintf( "Exception in main loop.\n" );
  FileUtil::uPrintf( str );
  return 1;
  }

catch( ... )
  {
  const char* errorS = "An unknown exception"
         " happened in the main loop.\n";

  FileUtil::uPrintf( errorS );
  return 1;
  }
}



bool MainApp::basicThingsAreRight()
{
/*
  printf( "Int8 size: %d\n", (int)sizeof( Int8 ) );
  printf( "Char8 size: %d\n",
                         (int)sizeof( Char8 ) );
  printf( "Char16 size: %d\n",
                         (int)sizeof( Char16 ) );
  printf( "Int16 size: %d\n",
                         (int)sizeof( Int16 ) );
  printf( "Uint16 size: %d\n",
                         (int)sizeof( Uint16 ) );
  printf( "Int32 size: %d\n",
                         (int)sizeof( Int32 ) );
  printf( "Uint32 size: %d\n",
                         (int)sizeof( Uint32 ) );
  printf( "Int64 size: %d\n",
                         (int)sizeof( Int64 ) );
  printf( "Uint64 size: %d\n",
                         (int)sizeof( Uint64 ) );
  printf( "Float32 size: %d\n",
                         (int)sizeof( Float32 ) );
  printf( "Float64 size: %d\n",
                         (int)sizeof( Float64 ) );
  // Float128
*/

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
