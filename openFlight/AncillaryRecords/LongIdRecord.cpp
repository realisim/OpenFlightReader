#include <cassert>
#include "LongIdRecord.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
LongIdRecord::LongIdRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{}

//-------------------------------------------------------------------------
const string& LongIdRecord::getAsciiId() const
{ return mAsciiId; }

//-------------------------------------------------------------------------
bool LongIdRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    iss.seekg(4);

    bool ok = true;
    ok &= readChar(iss, getRecordLength() - 4, mAsciiId);
    
    return ok;
}