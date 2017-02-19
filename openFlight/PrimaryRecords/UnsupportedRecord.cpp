
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
bool UnsupportedRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    mAsciiId = "Missing";
    mOriginalOpCode = mOpCode;
    mOpCode = ocUnsupported;
    return ok;
}
