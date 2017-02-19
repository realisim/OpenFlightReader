
#include "GroupRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
GroupRecord::GroupRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("n/a"),
mRelativePriority(0),
mFlags(0),
mSpecialEffectId1(0),
mSpecialEffectId2(0),
mSignificance(0),
mLayerCode(0),
mLoopCount(0),
mLoopDuration(0.0),
mLastFrameDuration(0.0)
{}

//------------------------------------------------------------------------------
GroupRecord::~GroupRecord()
{}

//------------------------------------------------------------------------------
std::string GroupRecord::getAsciiId() const
{ return mAsciiId;}

//------------------------------------------------------------------------------
int32_t GroupRecord::getFlags() const
{ return mFlags;}

//------------------------------------------------------------------------------
int8_t GroupRecord::getLayerCode() const
{ return mLayerCode;}

//------------------------------------------------------------------------------
int32_t GroupRecord::getLoopCount() const
{ return mLoopCount;}

//------------------------------------------------------------------------------
float GroupRecord::getLoopDuration() const
{ return mLoopDuration;}

//------------------------------------------------------------------------------
int16_t GroupRecord::getRelativePriority() const
{ return mRelativePriority;}

//------------------------------------------------------------------------------
int16_t GroupRecord::getSignificance() const
{ return mSignificance;}

//------------------------------------------------------------------------------
int16_t GroupRecord::getSpecialEffectId1() const
{ return mSpecialEffectId1;}

//------------------------------------------------------------------------------
int16_t GroupRecord::getSpecialEffectId2() const
{ return mSpecialEffectId2;}

//------------------------------------------------------------------------------
bool GroupRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    
    bool ok = true;
    ok &= readChar(iRawRecord, 8, mAsciiId);
    ok &= readInt16(iRawRecord, mRelativePriority);
    
    iRawRecord.seekg(startPos + 16);
    ok &= readInt32(iRawRecord, mFlags);
    ok &= readInt16(iRawRecord, mSpecialEffectId1);
    ok &= readInt16(iRawRecord, mSpecialEffectId2);
    ok &= readInt16(iRawRecord, mSignificance);
    ok &= readInt8(iRawRecord, mLayerCode);
    
    if( iVersion >= 1580 )
    {
        iRawRecord.seekg(startPos + 32);
        ok &= readInt32(iRawRecord, mLoopCount);
        ok &= readFloat32(iRawRecord, mLoopDuration);
        ok &= readFloat32(iRawRecord, mLastFrameDuration);
    }
    return ok;
}
