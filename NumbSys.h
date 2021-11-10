// Copyright Eric Chauvin, 2021.



#pragma once


// A number system.

// An early version of this idea is in old code
// I wrote from 2015 and earlier at:
// https://github.com/Eric7Apps/OldCode/
       //     blob/master/ModularReduction.cs


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "ProjConst.h"



class NumbSys
  {
  private:
  Int32 testForCopy = 123;
  Integer currentBase;

  // IntBuf* intBuf[];
  // TwoDUint64 baseAr;  // Base Array
  // OneDUint32 baseInd;
  // OneDUint64 numVal;
  // Uint32 valIndex = 0;

  void setValFromInt( const Integer& toSet );
  void setOneBaseFromInt( const Uint32 row,
                          const Integer& toSet );
  void setupBaseArray( const Integer& setBase,
                       IntegerMath& intMath );

  public:
  NumbSys( void );
  NumbSys( const NumbSys& in );
  ~NumbSys( void );

  void reduce( Integer& result,
               const Integer& toReduce,
               const Integer& modulus,
               IntegerMath& intMath );

  };
