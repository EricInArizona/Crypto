// Copyright Eric Chauvin 2021.



#include "FileIO.h"
#include <iostream>
#include <fstream>
#include "StIO.h"


// using namespace std;


FileIO::FileIO( void )
{
// StIO::printFS(
//        "FileIO constructor called.\n" );
}


// The copy constructor.
FileIO::FileIO( const FileIO &obj )
{
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
Uint32 howMany = cBuf.getLast();
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
Uint64 howMany = inFile.tellg();
inFile.seekg( 0 );

char* buffer = new char[howMany];
inFile.read( buffer, howMany );

cBuf.appendChars( buffer, howMany );

delete[] buffer;
inFile.close();
}



void FileIO::appendStr( Str& in )
{
cBuf.appendStr( in );
}




void FileIO::appendChars( const char* fromBuf,
                                 Uint32 howMany )
{
cBuf.appendChars( fromBuf, howMany );
}
