// Copyright Eric Chauvin, 2021.



#include "MainApp.h"
#include "StIO.h"
#include "Str.h"
#include "RSA.h"
#include "Ellip.h"
#include "ThreadEC.h"



// int MainApp::mainLoop( int argc, char* argv[] )
int MainApp::mainLoop( void )
{
Uint32 delay = 200; // milliseconds.
const char* outFile =
             "\\Eric\\Main\\Crypto\\ExeOut.txt";

try
{
StIO::printFS( "See output at:\n" );
StIO::printFS( outFile );
StIO::printFS( "\n" );


if( !basicThingsAreRight())
  {
  // StIO::printFS()
  mainIO.appendChars(
   "basicThingsAreRight() returned false.\n" );

  mainIO.writeAll( outFile );
  return 1; // Some error code.
  }

mainIO.appendChars(
            "Programming by Eric Chauvin.\n" );

mainIO.appendChars( "Version date: " );
mainIO.appendChars( getVersionStr() );
mainIO.appendChars( "\n" );

RSA rsa;
rsa.test( mainIO );

// Ellip ellip;
// ellip.test( mainIO );

mainIO.appendChars( "End of main app.\n" );

// mainIO.readAll( fileName );
mainIO.writeAll( outFile );

ThreadEC::sleep( delay );

return 0;
}
catch( const char* in )
  {
  mainIO.appendChars( "Exception in main loop.\n" );
  mainIO.appendChars( in );
  mainIO.writeAll( outFile );

  ThreadEC::sleep( delay );
  return 1;
  }

catch( ... )
  {
  const char* in = "An unknown exception"
         " happened in the main loop.\n";

  mainIO.appendChars( in );
  mainIO.writeAll( outFile );

  ThreadEC::sleep( delay );
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
