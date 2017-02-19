#include <cassert>
#include "TranslateRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
TranslateRecord::TranslateRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{}

//-------------------------------------------------------------------------
const Vector3d& TranslateRecord::getDelta() const
{ return mDelta; }

//-------------------------------------------------------------------------
const Vector3d& TranslateRecord::getOrigin() const
{ return mOrigin; }

//-------------------------------------------------------------------------
bool TranslateRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    iRawRecord.seekg(startPos + 8);

    bool ok = true;
    ok &= readVector3d(iRawRecord, mOrigin);
    ok &= readVector3d(iRawRecord, mDelta);
    
    return ok;
}