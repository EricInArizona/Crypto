// Copyright Eric Chauvin, 2021.



#ifndef ECMainApp_H
#define ECMainApp_H



#include "BasicTypes.h"



class MainApp
  {
  private:
  bool basicThingsAreRight();


  public:
  inline static const char* getVersionStr( void )
    {
    return "4/26/2021";
    }

  Int32 mainLoop( Int32 argc, char* argv[] );

  };


#endif
