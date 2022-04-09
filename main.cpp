// Copyright Eric Chauvin 2021 - 2022.



#include "..\LinuxApi\BasicTypes.h"

// This is only for Linux.
// #include "../LinuxApi/SetStack.h"

#include "MainApp.h"



// Int32 main( Int32 argc, char* argv[] )
Int32 main( void )
{
// This is only for Linux.
// if( !SetStack::setit( 64 * 1024 * 1024 ))
  // return 1;


MainApp mApp;

return mApp.mainLoop(); //  argc, argv );
}
