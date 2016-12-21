
#include "UnsupportedRecord.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
UnsupportedRecord::UnsupportedRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("n/a")
{}

//------------------------------------------------------------------------------
UnsupportedRecord::~UnsupportedRecord()
{}

//------------------------------------------------------------------------------
std::string UnsupportedRecord::getAsciiId() const
{ return mAsciiId;}

//------------------------------------------------------------------------------
opCode UnsupportedRecord::getOriginalOpCode() const
{ return mOriginalOpCode;}

//------------------------------------------------------------------------------
bool UnsupportedRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    // Lets move by 4 to skip the opCode and recordLenght... we already know
    // we have a valid record at this point.
    //
    iss.seekg(4);
    
    bool ok = true;
    mAsciiId = "Missing";
    mOriginalOpCode = mOpCode;
    mOpCode = ocUnsupported;
    return ok;
}
