// Copyright Eric Chauvin 2021 - 2022.


// This is licensed under the GNU General
// Public License (GPL).  It is the
// same license that Linux has.
// https://www.gnu.org/licenses/gpl-3.0.html


#include "../CppBase/BasicTypes.h"

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
