
#include "GroupRecord.h"
#include <sstream>
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
bool GroupRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    // Lets move by 4 to skip the opCode and recordLenght... we already know
    // we have a valid record at this point.
    //
    iss.seekg(4);
    
    bool ok = true;
    ok &= readChar(iss, 8, mAsciiId);
    ok &= readInt16(iss, mRelativePriority);
    
    iss.seekg(16);
    ok &= readInt32(iss, mFlags);
    ok &= readInt16(iss, mSpecialEffectId1);
    ok &= readInt16(iss, mSpecialEffectId2);
    ok &= readInt16(iss, mSignificance);
    ok &= readInt8(iss, mLayerCode);
    
    if( iVersion >= 1580 )
    {
        iss.seekg(32);
        ok &= readInt32(iss, mLoopCount);
        ok &= readFloat32(iss, mLoopDuration);
        ok &= readFloat32(iss, mLastFrameDuration);
    }
    return ok;
}
