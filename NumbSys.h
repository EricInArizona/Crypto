// Copyright Eric Chauvin, 2021.



#pragma once


// A number system.


// An early version of this idea is in old code
// I wrote from 2015 and earlier at:
// https://github.com/Eric7Apps/OldCode/blob/master/ModularReduction.cs


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "TwoDUint64.h"
#include "OneDUint64.h"
#include "OneDUint32.h"



class NumbSys
  {
  private:
  Int32 testForCopy = 123;
  Integer currentBase;
  TwoDUint64 baseAr;
  OneDUint32 baseInd;
  OneDUint64 numVal;
  Uint32 valIndex = 0;

  void setValFromInt( Integer& toSet );
  void setOneBaseFromInt( Uint32 row,
                              Integer& toSet );
  void setupBaseArray( Integer& setBase,
                       IntegerMath& intMath );

  public:
  NumbSys( void );
  NumbSys( const NumbSys& in );
  Uint32 reduce( Integer& result,
                 Integer& toReduce,
                 Integer& modulus,
                 IntegerMath& intMath );

  };
