// Copyright Eric Chauvin, 2021.



#pragma once



#include "BasicTypes.h"
#include "ProjConst.h"


class OneDUint32
  {
  private:
  Uint32* aR;
  static const Uint32 last =
                      ProjConst::digitArraySize;

  public:
  OneDUint32( void );
  ~OneDUint32( void );
  inline Uint32 getV( Uint32 where )
    {
    if( where >= last )
      throw "OneDUint32 get out of bounds.";

    return aR[where];
    }

  inline void setV( Uint32 where, Uint32 val )
    {
    if( where >= last )
      throw "OneDUint32 set out of bounds.";

    aR[where] = val;
    }


  };
