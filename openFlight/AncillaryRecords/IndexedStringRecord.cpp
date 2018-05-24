
#include <cassert>
#include "IndexedStringRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
IndexedStringRecord::IndexedStringRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{}

//------------------------------------------------------------------------------
uint32_t IndexedStringRecord::getIndex() const
{ return mIndex; }

//------------------------------------------------------------------------------
string IndexedStringRecord::getString() const
{ return mString; }

//-------------------------------------------------------------------------
bool IndexedStringRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    ok &= readUint32(iRawRecord, mIndex);
    ok &= readChar(iRawRecord, getRecordLength() - 8, mString);

    return ok;
}