#include "Record.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-----------------------------------------------------------------------------
//--- Record
//-----------------------------------------------------------------------------
Record::Record() :
mOpCode(ocUnknown),
mRecordLenght(0)
{}

//-----------------------------------------------------------------------------
Record::~Record()
{}

//-----------------------------------------------------------------------------
bool Record::parseRecord(const std::string& iRawRecord, int iVersion)
{
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    bool ok = true;
    uint16_t d;
    ok &= readUint16(iss, d);
    mOpCode = (opCode)d;
    ok &= readUint16(iss, mRecordLenght);
    
    return ok;
}
