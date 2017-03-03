
#include "LevelOfDetailRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
LevelOfDetailRecord::LevelOfDetailRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("n/a"),
mSwitchInDistance(0.0),
mSwitchOutDistance(0.0),
mSpecialEffectId1(0),
mSpecialEffectId2(0),
mFlags(0),
mLodX(0.0),
mLodY(0.0),
mLodZ(0.0),
mTransitionRange(0.0),
mSignificantSize(0.0)
{}

//------------------------------------------------------------------------------
LevelOfDetailRecord::~LevelOfDetailRecord()
{}

//------------------------------------------------------------------------------
std::string LevelOfDetailRecord::getAsciiId() const
{ return mAsciiId; }

//------------------------------------------------------------------------------
int32_t LevelOfDetailRecord::getFlags() const
{ return mFlags; }

//------------------------------------------------------------------------------
double LevelOfDetailRecord::getLodX() const
{ return mLodX; }

//------------------------------------------------------------------------------
double LevelOfDetailRecord::getLodY() const
{ return mLodY; }

//------------------------------------------------------------------------------
double LevelOfDetailRecord::getLodZ() const
{ return mLodZ; }

//------------------------------------------------------------------------------
double LevelOfDetailRecord::getSignificantSize() const
{ return mSignificantSize; }

//------------------------------------------------------------------------------
int16_t LevelOfDetailRecord::getSpecialEffectId1() const
{ return mSpecialEffectId1; }

//------------------------------------------------------------------------------
int16_t LevelOfDetailRecord::getSpecialEffectId2() const
{ return mSpecialEffectId2; }

//------------------------------------------------------------------------------
double LevelOfDetailRecord::getSwitchInDistance() const
{ return mSwitchInDistance; }

//------------------------------------------------------------------------------
double LevelOfDetailRecord::getSwitchOutDistance() const
{ return mSwitchOutDistance; }

//------------------------------------------------------------------------------
double LevelOfDetailRecord::getTransitionRange() const
{ return mTransitionRange; }

//------------------------------------------------------------------------------
bool LevelOfDetailRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    ok &= readChar(iRawRecord, 8, mAsciiId);

    iRawRecord.seekg(startPos + 16);
    ok &= readDouble(iRawRecord, mSwitchInDistance);
    ok &= readDouble(iRawRecord, mSwitchOutDistance);
    ok &= readInt16(iRawRecord, mSpecialEffectId1);
    ok &= readInt16(iRawRecord, mSpecialEffectId1);
    ok &= readInt32(iRawRecord, mFlags);
    ok &= readDouble(iRawRecord, mLodX);
    ok &= readDouble(iRawRecord, mLodY);
    ok &= readDouble(iRawRecord, mLodZ);
    ok &= readDouble(iRawRecord, mTransitionRange);
    
    if( iVersion >= 1580 )
    {
        ok &= readDouble(iRawRecord, mSignificantSize);
    }
    return ok;
}
