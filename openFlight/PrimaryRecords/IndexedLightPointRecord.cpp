
#include "IndexedLightPointRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
IndexedLightPointRecord::IndexedLightPointRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("N/A"),
mAppearanceIndex(-1),
mAnimationIndex(-1)
{}

//------------------------------------------------------------------------------
IndexedLightPointRecord::~IndexedLightPointRecord()
{}

//------------------------------------------------------------------------------
std::string IndexedLightPointRecord::getAsciiId() const
{
    return mAsciiId;
}

//------------------------------------------------------------------------------
int IndexedLightPointRecord::getAppearanceIndex() const
{
    return mAppearanceIndex;
}

//------------------------------------------------------------------------------
int IndexedLightPointRecord::getAnimationIndex() const
{
    return mAnimationIndex;
}

//------------------------------------------------------------------------------
bool IndexedLightPointRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    ok &= readChar(iRawRecord, 8, mAsciiId);
    ok &= readInt32(iRawRecord, mAppearanceIndex);
    ok &= readInt32(iRawRecord, mAnimationIndex);
    
    return ok;
}
