#include "Record.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-----------------------------------------------------------------------------
//--- Record
//-----------------------------------------------------------------------------
Record::Record() :
mOpCode(ocUnsupported),
mRecordLenght(0)
{}

//-----------------------------------------------------------------------------
Record::~Record()
{}

//-----------------------------------------------------------------------------
bool Record::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    bool ok = true;
    uint16_t d;
    ok &= readUint16(iRawRecord, d);
    mOpCode = (opCode)d;
    ok &= readUint16(iRawRecord, mRecordLenght);
    
    return ok;
}
