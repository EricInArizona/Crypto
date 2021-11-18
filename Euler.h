// Copyright Eric Chauvin, 2021.


#pragma once



#include "BasicTypes.h"
#include "Integer.h"
#include "Mod.h"



class Euler
  {
  private:

  public:
  static bool isQuadRes( const Integer& base,
                         Uint32 prime,
                         Mod& mod,
                         IntegerMath& intMath );

  };
