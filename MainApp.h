// Copyright Eric Chauvin 2021 - 2022.



#pragma once


// I never use the C preprocessor except to use
// #include statements.
// See SigAction.cpp for notes about why you should
// not use the C preprocessor.


#include "../LinuxApi/BasicTypes.h"
#include "../LinuxApi/FileIO.h"



class MainApp
  {
  private:
  FileIO mainIO;

  public:
  inline static const char* getVersionStr( void )
    {
    return "3/22/2022";
    }

  // Int32 mainLoop( Int32 argc, char* argv[] );
  Int32 mainLoop( void );

  };
