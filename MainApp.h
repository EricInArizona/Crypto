// Copyright Eric Chauvin, 2021.



#ifndef ECMainApp_H
#define ECMainApp_H



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
    return "6/22/2021";
    }

  // Int32 mainLoop( Int32 argc, char* argv[] );
  Int32 mainLoop( void );

  };


#endif
