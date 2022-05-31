// Copyright Eric Chauvin, 2021 - 2022.



// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#include "../CppBase/StIO.h"
#include "../CppBase/Str.h"

// This is only for Linux.
// #include "../LinuxApi/SetStack.h"

#include "../CppBase/Casting.h"
#include "../CppBase/Threads.h"
#include "../WinApi/Signals.h"


#include "MainApp.h"
#include "RsaTest.h"
#include "CrtTest.h"
#include "Ellip.h"






// int MainApp::mainLoop( int argc, char* argv[] )
int MainApp::mainLoop( void )
{
Int32 delay = 200; // milliseconds.

// For Linux.
// const char* outFile = "/home/Eric/Crypto/ExeOut.txt";

// const char* outFile =
   //          "\\Eric\\Main\\Crypto\\ExeOut.txt";

try
{
StIO::putS( "See output at:" );
// StIO::putS( outFile );

// Throws an exception if things are not right.
BasicTypes::thingsAreRight();


// mainIO.appendChars(
   //         "Programming by Eric Chauvin.\n" );

// mainIO.appendChars( "Version date: " );
// mainIO.appendChars( getVersionStr() );
// mainIO.appendChars( "\n\n" );

// For Linux:
// Int32 stackSize = SetStack::getSize();
// Str showS( stackSize );
// mainIO.appendChars( "Stack size: " );
// mainIO.appendStr( showS );
// mainIO.appendChars( "\n\n" );


Signals::setupControlCSignal();
Signals::setupFpeSignal();
Signals::setupIllegalOpSignal();
Signals::setupBadMemSignal();



// RsaTest rsaTest;
// rsaTest.test();

// CrtTest crtTest;
// crtTest.test( mainIO );

// Ellip ellip;
// ellip.test( mainIO );

// mainIO.appendChars( "End of main app.\n" );

//             mainIO.readAll( fileName );
// mainIO.writeAll( outFile );

Threads::sleep( delay );

return 0;
}
catch( const char* in )
  {
  StIO::putS( in );

  // mainIO.appendChars( "Exception in main loop.\n" );
  // mainIO.appendChars( in );
  // mainIO.appendChars( "\n" );
  // mainIO.writeAll( outFile );

  Threads::sleep( delay );
  return 1;
  }

catch( ... )
  {
  // const char* in = "An unknown exception"
    //               " happened in the main loop.\n";

  // mainIO.appendChars( in );
  // mainIO.writeAll( outFile );

  Threads::sleep( delay );
  return 1;
  }
}
