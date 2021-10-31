// Copyright Eric Chauvin, 2021.



#pragma once



#include "BasicTypes.h"
#include "ProjConst.h"


class OneDUint64
  {
  private:
  Uint64* aR;
  static const Uint32 last =
                      ProjConst::digitArraySize;

  public:
  OneDUint64( void );
  ~OneDUint64( void );
  inline Uint64 getV( Uint32 where )
    {
    if( where >= last )
      throw "OneDUint64 get out of bounds.";

    return aR[where];
    }

  inline void setV( Uint32 where, Uint64 val )
    {
    if( where >= last )
      throw "OneDUint64 set out of bounds.";

    aR[where] = val;
    }


  };
