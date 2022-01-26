// Copyright Eric Chauvin 2021 - 2022.



#include "FileIO.h"
#include <iostream>
#include <fstream>
#include "StIO.h"
#include "CastE.h"


// using namespace std;


FileIO::FileIO( void )
{
// StIO::printFS(
//        "FileIO constructor called.\n" );
}


// The copy constructor.
FileIO::FileIO( const FileIO &in )
{
// Make the compiler think in is being used.
if( in.testForCopy == 7 )
  return;

// Don't copy a giant buffer.
const char* showS = "The FileIO copy constructor"
         " should not be getting called.\n";
throw showS;
}



FileIO::~FileIO( void )
{
// StIO::printFS(
//       "FileIO destructor called.\n" );
}


void FileIO::writeAll( const char* fileName )
{
Int32 howMany = cBuf.getLast();
const char* buffer = cBuf.getBufPoint();

std::ofstream outFile( fileName,
                       std::ofstream::binary );

outFile.write( buffer, howMany );
outFile.close();
}



void FileIO::readAll( const char* fileName )
{
std::ifstream inFile( fileName,
                      std::ifstream::binary );

inFile.seekg( 0, inFile.end );
Int64 howMany = inFile.tellg();
// Error returns -1.
if( howMany < 0 )
  throw "Infile tellg() returned < 0.";

if( howMany > 4000000000 )
  throw "Infile tellg() returned > 4000000000.";

inFile.seekg( 0 );

char* buffer = new char[CastE::i64ToU64(
                                     howMany )];
inFile.read( buffer, howMany );

cBuf.appendCharBuf( buffer, CastE::i64ToI32(
                                   howMany ));

delete[] buffer;
inFile.close();
}



void FileIO::appendStr( Str& in )
{
cBuf.appendStr( in );
}




void FileIO::appendChars( const char* pStr )
{
cBuf.appendChars( pStr );
}
