// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


// I never use the C preprocessor except to use
// #include statements.
// Never ever.
// The C preprocessor is bad.  Very bad.


#include "BasicTypes.h"
#include "FileIO.h"



class MainApp
  {
  private:
  bool basicThingsAreRight();
  FileIO mainIO; // Sort of like Standard Out.

  public:
  inline static const char* getVersionStr( void )
    {
    return "2/5/2022";
    }

  // Int32 mainLoop( Int32 argc, char* argv[] );
  Int32 mainLoop( void );

  };
