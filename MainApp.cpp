// Copyright Eric Chauvin, 2021 - 2022.



#include "../LinuxApi/StIO.h"
#include "../LinuxApi/Str.h"
#include "../LinuxApi/SetStack.h"
#include "../LinuxApi/Casting.h"


// #include "../LinuxApi/Threads.h"


#include "MainApp.h"
// #include "RsaTest.h"
// #include "CrtTest.h"
// #include "Ellip.h"



// int MainApp::mainLoop( int argc, char* argv[] )
int MainApp::mainLoop( void )
{
// Int32 delay = 200; // milliseconds.
const char* outFile =
             "/home/Eric/Crypto/ExeOut.txt";

try
{
StIO::cPuts( "See output at:\n" );
StIO::cPuts( outFile );
StIO::cPuts( "\n" );


if( !basicThingsAreRight())
  {
  mainIO.appendChars(
          "basicThingsAreRight() returned false.\n" );

  mainIO.writeAll( outFile );
  return 1; // Some error code.
  }

mainIO.appendChars(
            "Programming by Eric Chauvin.\n" );

mainIO.appendChars( "Version date: " );
mainIO.appendChars( getVersionStr() );
mainIO.appendChars( "\n\n" );

Int32 stackSize = SetStack::getSize();
Str showS( stackSize );

mainIO.appendChars( "Stack size: " );
mainIO.appendStr( showS );
mainIO.appendChars( "\n\n" );


// RsaTest rsaTest;
// rsaTest.test( mainIO );

// CrtTest crtTest;
// crtTest.test( mainIO );

// Ellip ellip;
// ellip.test( mainIO );

mainIO.appendChars( "End of main app.\n" );

//             mainIO.readAll( fileName );
mainIO.writeAll( outFile );

// Threads::sleep( delay );

return 0;
}
catch( const char* in )
  {
  mainIO.appendChars( "Exception in main loop.\n" );
  mainIO.appendChars( in );
  mainIO.appendChars( "\n" );
  mainIO.writeAll( outFile );

  // Threads::sleep( delay );
  return 1;
  }

catch( ... )
  {
  const char* in = "An unknown exception"
         " happened in the main loop.\n";

  mainIO.appendChars( in );
  mainIO.writeAll( outFile );

  // Threads::sleep( delay );
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

// if( sizeof( Int8 ) != 1 )
  // return false;

// if( sizeof( Char8 ) != 1 )
  // return false;

// if( sizeof( Char16 ) != 2 )
  // return false;

// if( sizeof( Int16 ) != 2 )
  // return false;

if( sizeof( UTF16 ) != 2 )
  return false;

if( sizeof( Int32 ) != 4 )
  return false;

// if( sizeof( Uint32 ) != 4 )
  // return false;

if( sizeof( Int64 ) != 8 )
  return false;

if( sizeof( ArrayU64 ) != 8 )
  return false;

if( sizeof( Float32 ) != 4 )
  return false;

if( sizeof( Float64 ) != 8 )
  return false;

return true;
}
