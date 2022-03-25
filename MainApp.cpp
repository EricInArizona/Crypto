// Copyright Eric Chauvin, 2021 - 2022.



#include "../LinuxApi/StIO.h"
#include "../LinuxApi/Str.h"
#include "../LinuxApi/SetStack.h"
#include "../LinuxApi/Casting.h"
#include "../LinuxApi/Threads.h"
#include "../LinuxApi/Signals.h"


#include "MainApp.h"
#include "RsaTest.h"
#include "CrtTest.h"
#include "Ellip.h"


/*
extern volatile Int32 gotSigFpe;


void MainApp::checkSignals( void )
{
if( gotSigFpe > 0 )
  throw "gotSigFpe > 0";

}
*/



// int MainApp::mainLoop( int argc, char* argv[] )
int MainApp::mainLoop( void )
{
Int32 delay = 200; // milliseconds.
const char* outFile = "/home/Eric/Crypto/ExeOut.txt";

try
{
StIO::putS( "See output at:" );
StIO::putS( outFile );

// Throws an exception if things are not right.
BasicTypes::thingsAreRight();


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

Signals::setupControlCSignal();
Signals::setupFpeSignal();
Signals::setupIllegalOpSignal();
Signals::setupBadMemSignal();


// RsaTest rsaTest;
// rsaTest.test( mainIO );

CrtTest crtTest;
crtTest.test( mainIO );

// Ellip ellip;
// ellip.test( mainIO );

mainIO.appendChars( "End of main app.\n" );

//             mainIO.readAll( fileName );
mainIO.writeAll( outFile );

Threads::sleep( delay );

return 0;
}
catch( const char* in )
  {
  mainIO.appendChars( "Exception in main loop.\n" );
  mainIO.appendChars( in );
  mainIO.appendChars( "\n" );
  mainIO.writeAll( outFile );

  Threads::sleep( delay );
  return 1;
  }

catch( ... )
  {
  const char* in = "An unknown exception"
                   " happened in the main loop.\n";

  mainIO.appendChars( in );
  mainIO.writeAll( outFile );

  Threads::sleep( delay );
  return 1;
  }
}
