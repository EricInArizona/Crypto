// Copyright Eric Chauvin, 2021.



#include "MainApp.h"
#include "FileUtil.h"



// int main( int argc, char* argv[] )

int MainApp::mainLoop( void )
{
if( !basicThingsAreRight())
  {
  FileUtil::uPrintf(
      "basicThingsAreRight() returned false.\n" );

  return 1; // Some error code.
  }

FileUtil::uPrintf( getVersionStr() );
FileUtil::uPrintf( "\n" );

return 0;
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


