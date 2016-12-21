
#include "MissingRecord.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
MissingRecord::MissingRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("n/a")
{}

//------------------------------------------------------------------------------
MissingRecord::~MissingRecord()
{}

//------------------------------------------------------------------------------
std::string MissingRecord::getAsciiId() const
{ return mAsciiId;}

//------------------------------------------------------------------------------
opCode MissingRecord::getOriginalOpCode() const
{ return mOriginalOpCode;}

//------------------------------------------------------------------------------
bool MissingRecord::parseRecord(const std::string& iRawRecord, int iVersion)
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
