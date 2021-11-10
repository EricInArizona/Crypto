// Copyright Eric Chauvin 2021.



// Number System


#include "NumbSys.h"
#include "Division.h"
#include "IntegerMath.h"


NumbSys::NumbSys( void )
{
// intBuf = new IntBuf( ProjConst::digitArraySize );
}


// The copy constructor.
NumbSys::NumbSys( const NumbSys& in )
{
// intBuf = new IntBuf( Integer::digitArraySize );

// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

throw "Don't use copy constructor for NumbSys.";
}


NumbSys::~NumbSys( void )
{
// delete intBuf;
}


void NumbSys::setupBaseArray(
                        const Integer& setBase,
                        IntegerMath& intMath )
{
currentBase.copy( setBase );

Integer base2;   // 0x1 0000 0000
base2.setFromULong( 0x100000000U );

Integer baseValue;
Integer quotient;
Integer remainder;

baseValue.setFromULong( 1 );

for( Uint32 count = 0; count <
             ProjConst::digitArraySize; count++ )
  {
  Division::divide( baseValue, currentBase,
                    quotient, remainder,
                    intMath );

  setOneBaseFromInt( count, remainder );

  // Done at the bottom for the next round of
  // the loop.
  baseValue.copy( remainder );
  intMath.multiply( baseValue, base2 );
  }
}



void NumbSys::setOneBaseFromInt(
                         const Uint32 row,
                         const Integer& toSet )
{
const Uint32 last = toSet.getIndex();

for( Uint32 count = 0; count <= last; count++ )
  {
/*
  intBuf[count].
===
  baseAr.setV( count, row, toSet.getD( count ));
*/
  }
}



void NumbSys::setValFromInt( const Integer& toSet )
{
/*
const Uint32 last = toSet.getIndex();
valIndex = last;

for( Uint32 count = 0; count <= last; count++ )
  numVal.setV( count, toSet.getD( count ));
*/
}



void NumbSys::reduce( Integer& result,
                      const Integer& toReduce,
                      const Integer& modulus,
                      IntegerMath& intMath )
{
/*
// currentBase would start out being set to
// zero, so it has to be set the first time
// it gets called.
if( !modulus.isEqual( currentBase ))
  setupBaseArray( modulus, intMath );

if( toReduce.paramIsGreater( currentBase ))
  {
  result.copy( toReduce );
  return;
  }

setValFromInt( toReduce );
const Uint32 last = valIndex;

Integer accumRow;

result.setToZero();
for( Uint32 row = 0; row <= last; row++ )
  {
  Uint64 val = numVal.getV( row );
  const Uint32 lastBase = baseInd.getV( row );
  accumRow.setIndex( lastBase );
  for( Uint32 column = 0; column <= lastBase;
                                       column++ )
    {
    Uint64 baseVal = baseAr.getV( column, row );
    Uint64 calc = baseVal * val;
    accumRow.setD( column, calc );
    }

  accumRow.cleanUp();
  result.add( accumRow );
  }
*/
}
