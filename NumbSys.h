// Copyright Eric Chauvin, 2021.



#pragma once


// A Number System used for Modular Reduction.


// An early version of this idea is in old code
// I wrote from 2015 and earlier at:
// https://github.com/Eric7Apps/OldCode/
       //     blob/master/ModularReduction.cs


#include "BasicTypes.h"
#include "Integer.h"
#include "IntegerMath.h"
#include "ProjConst.h"
#include "IntBuf.h"



class NumbSys
  {
  private:
  Int32 testForCopy = 123;
  static const Uint32 last =
                      ProjConst::digitArraySize;

  Integer currentBase;
  Integer numVal;
  IntBuf* intBufAr;

  void setupBaseArray( const Integer& setBase,
                       IntegerMath& intMath );

  public:
  NumbSys( void );
  NumbSys( const NumbSys& in );
  ~NumbSys( void );

  // This is meant to only be used within the
  // Mod.cpp class.  Sort of like it's private
  // to the Mod.cpp class.
  void privateReduce( Integer& result,
               const Integer& toReduce,
               const Integer& modulus,
               IntegerMath& intMath );

  };
