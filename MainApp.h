// Copyright Eric Chauvin, 2021.



#ifndef ECMainApp_H
#define ECMainApp_H


// An old saying: "Make it work first, then make
// it work fast".


#include "BasicTypes.h"



class MainApp
  {
  private:
  bool basicThingsAreRight();


  public:
  inline static const char* getVersionStr( void )
    {
    return "Version date: 4/5/2021";
    }

  int mainLoop( void );

  };


#endif
