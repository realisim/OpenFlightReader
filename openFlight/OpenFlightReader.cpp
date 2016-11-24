

#include <fstream>
#include <iostream>
#include "Nodes.h"
#include "OpCode.h"
#include "OpenFlightReader.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-----------------------------------------------------------------------------
OpenFlightReader::OpenFlightReader() :
    mErrors(),
    mHasDebugEnabled(false),
    mpRootNode(nullptr)
{}

//-----------------------------------------------------------------------------
OpenFlightReader::~OpenFlightReader()
{}

//-----------------------------------------------------------------------------
void OpenFlightReader::addError(const std::string& iE) const
{
    mErrors += hasErrors() ? "\n" + iE : iE;
}

//-----------------------------------------------------------------------------
void OpenFlightReader::enableDebug(bool iE)
{ mHasDebugEnabled = iE; }

//-----------------------------------------------------------------------------
bool OpenFlightReader::hasDebugEnabled() const
{ return mHasDebugEnabled; }

//-----------------------------------------------------------------------------
std::string OpenFlightReader::getAndClearLastErrors() const
{
    string r = mErrors;
    mErrors.clear();
    return r;
}

//-----------------------------------------------------------------------------
bool OpenFlightReader::hasErrors() const
{ return !mErrors.empty(); }

//-----------------------------------------------------------------------------
INode* OpenFlightReader::open(const std::string& iFileNamePath)
{

    ifstream ifs;
    ifs.open(iFileNamePath, ifstream::in | ios_base::binary);

    if (!ifs.fail())
    {
        while (ifs.good() && !ifs.eof() && !hasErrors())
        { readRecord(ifs); }
    }
    else
    {
        ostringstream oss;
        oss << "OpenFlightReader::open - Could not open file " << iFileNamePath;
        addError( oss.str() );
    }

    return mpRootNode;
}

//-----------------------------------------------------------------------------
void OpenFlightReader::parseHeaderRecord(int iRecordSize, char* iRawRecord)
{
    if (mpRootNode == nullptr)
    {
        mpRootNode = new HeaderNode();
        mpRootNode->parseRecord( iRecordSize, iRawRecord );
    }
}

//-----------------------------------------------------------------------------
void OpenFlightReader::parseRawRecord(uint16_t iOpCode, int iRecordSize, char* iRawRecord)
{
    switch (iOpCode)
    {
    case ocHeader: parseHeaderRecord(iRecordSize, iRawRecord); break;
    default: break;
    }   
}

//-----------------------------------------------------------------------------
void OpenFlightReader::readRecord(ifstream& iFileStream)
{
    // read first 4 bytes of records, this will give us the opCode
    // and the length of the record to read.

    // record format
    //
    // |  2 bytes |  2 bytes       |  lengthOfRecord - 4 |
    // |  opCode  | LengthOfRecord |  recordPayload      | 
    //

    bool ok = true;
    uint16_t opCode = 0;
    uint16_t lengthOfRecord = 0;
    ok &= readUint16(iFileStream, opCode);
    ok &= readUint16(iFileStream, lengthOfRecord);
    if (ok)
    {
        char *rawRecord = new char[lengthOfRecord];

        // lets move back at the begining of the record and read the whole  thing
        //
        std::streamoff currentPosition = iFileStream.tellg();
        iFileStream.seekg( currentPosition - 4 ); 
        iFileStream.read(rawRecord, lengthOfRecord);

        if( iFileStream.good() )
        {
            if( hasDebugEnabled() )
            { cout << rawRecordToString(lengthOfRecord, rawRecord) << endl; }

            parseRawRecord( opCode, lengthOfRecord, rawRecord );
        }
        else
        {
            ostringstream oss;
            oss << "OpenFlightReader::readRecord - Could not read record with opCode " << opCode <<
                " . " << lengthOfRecord << " bytes were requested, only " << iFileStream.gcount() << " could be read." ;
            addError( oss.str() );
        }

        delete[] rawRecord;
    }
    
    // when reaching eof, ok will be false (see istream documentation about eof, mostly due because
    // eof is set when trying to read pass the end...)
    //
    if( !ok && !iFileStream.eof() )
    { 
        ostringstream oss;
        oss << "OpenFlightReader::readRecord - Could not read record header with opCode " << opCode;
        addError( oss.str() );
    }
}


//-----------------------------------------------------------------------------
// iOpCode is in decimal
// iPayload is in hexadecimal at this point and not yet parsed.
//
string OpenFlightReader::rawRecordToString(int iRecordSize, char* iRawRecord) const
{
    ostringstream oss;
    
    string hexPayload;
    char hex[5];
    for(size_t i = 0; i < iRecordSize; ++i)
    { 
        sprintf(hex, "[%02X]", (unsigned char)iRawRecord[i]);
        hexPayload += hex;
    }

    oss << "Raw Record (hex):" << hexPayload;

    return oss.str();
}