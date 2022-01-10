// Copyright Eric Chauvin, 2021 - 2022.



#pragma once


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
    return "1/10/2022";
    }

  // Int32 mainLoop( Int32 argc, char* argv[] );
  Int32 mainLoop( void );

  };
