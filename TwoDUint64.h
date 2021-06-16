// Copyright Eric Chauvin, 2021.




#ifndef ECTwoDUint64_H
#define ECTwoDUint64_H


#include "BasicTypes.h"
#include "Integer.h"


class TwoDUint64
  {
  private:
  Uint64* aR;
  static const Uint32 last =
                      Integer::digitArraySize *
                      Integer::digitArraySize;

  public:
  TwoDUint64( void );
  ~TwoDUint64( void );
  inline Uint64 getVal( Uint32 row, Uint32 column )
    {
    Uint32 where = (row * Integer::digitArraySize)
                   + column;
    if( where >= last )
      throw "TwoDUint64 get out of bounds.";

    return aR[where];
    }


  inline void setVal( Uint32 row, Uint32 column,
                      Uint64 val )
    {
    Uint32 where = (row * Integer::digitArraySize)
                   + column;

    if( where >= last )
      throw "TwoDUint64 set out of bounds.";

    aR[where] = val;
    }


  };


#endif
