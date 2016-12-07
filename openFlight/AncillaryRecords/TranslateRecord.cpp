#include <cassert>
#include "TranslateRecord.h"
#include <sstream>
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
bool TranslateRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    iss.seekg(8);

    bool ok = true;
    ok &= readVector3d(iss, mOrigin);
    ok &= readVector3d(iss, mDelta);
    
    return ok;
}