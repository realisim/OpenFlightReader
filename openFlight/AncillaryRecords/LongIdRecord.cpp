#include <cassert>
#include "LongIdRecord.h"
#include <fstream>
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
bool LongIdRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    ok &= readBytes(iRawRecord, getRecordLength() - 4, mAsciiId);
    
    return ok;
}