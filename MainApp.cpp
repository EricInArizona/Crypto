// Copyright Eric Chauvin, 2021.



#include "MainApp.h"
#include "StIO.h"
#include "Base10Number.h"
#include "Str.h"
#include "Integer.h"
#include "FileIO.h"
// #include "Markers.h"



int MainApp::mainLoop( int argc, char* argv[] )
{
try
{
if( !basicThingsAreRight())
  {
  StIO::uPrintf(
      "basicThingsAreRight() returned false.\n" );

  return 1; // Some error code.
  }


Str me( "Programming by Eric Chauvin." );
me.print();
StIO::putC( '\n' );
// StIO::uPrintf( "Begin marker: >" );
// StIO::putC( Markers::Begin );
// StIO::putC( '<' );
// StIO::putC( '\n' );

StIO::uPrintf( "Version date: " );
Str ver( getVersionStr() );
ver.printLine();

StIO::uPrintf( "\n" );

Str oneS( "123456789" );
Str twoS( "987654" );

StIO::uPrintf( "Created strings.\n" );

Base10Number b1( oneS );
Base10Number b2( twoS );

StIO::uPrintf( "Created Base 10 numbers.\n" );

Integer int1;
int1.setToOne();

StIO::uPrintf( "Created Integer.\n" );

FileIO testFile;
testFile.appendStr( oneS );

const char* testChars = "\nHere are some test"
    " characters in this string here.\n";

Uint32 len = Str::charsLength( testChars );
testFile.appendChars( testChars, len );

const char* fileName =
          "\\Eric\\Main\\Crypto\\TestFile.txt";

testFile.writeAll( fileName );

return 0;
}
catch( const char* str )
  {
  StIO::uPrintf( "Exception in main loop.\n" );
  StIO::uPrintf( str );
  return 1;
  }

catch( ... )
  {
  const char* errorS = "An unknown exception"
         " happened in the main loop.\n";

  StIO::uPrintf( errorS );
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

// if( sizeof( Char8 ) != 1 )
  // return false;

// if( sizeof( Char16 ) != 2 )
  // return false;

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
