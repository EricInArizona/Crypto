// Copyright Eric Chauvin 2021 - 2022.



// I had to put the Cryptography code back
// under Windows for now until I write my code
// editor for Linux.  Fortunately it
// recognizes a path with the slash
// character used iin the #include
// statements.

// I have given up on Java on Linux.
// Actually the OpenJDK JRE on Linux.


#pragma once


// I never use the C preprocessor except to use
// #include statements.


#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/FileIO.h"



class MainApp
  {
  private:
  FileIO mainIO;

  public:
  inline static const char* getVersionStr( void )
    {
    return "4/8/2022";
    }

  // Int32 mainLoop( Int32 argc, char* argv[] );
  Int32 mainLoop( void );

  };
