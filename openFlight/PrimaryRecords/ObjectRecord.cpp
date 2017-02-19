
#include "ObjectRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
ObjectRecord::ObjectRecord(PrimaryRecord* ipParent) :
    PrimaryRecord(ipParent),
    mAsciiId("n/a"),
    mFlags(0),
    mRelativePriority(0),
    mTransparency(0),
    mSpecialEffectId1(0),
    mSpecialEffectId2(0),
    mSignificance(0)
{}

//------------------------------------------------------------------------------
ObjectRecord::~ObjectRecord()
{}

//------------------------------------------------------------------------------
const std::string& ObjectRecord::getAsciiId() const
{ return mAsciiId;}

//------------------------------------------------------------------------------
int32_t ObjectRecord::getFlags() const
{ return mFlags;}

//------------------------------------------------------------------------------
int16_t ObjectRecord::getRelativePriority() const
{ return mRelativePriority;}

//------------------------------------------------------------------------------
uint16_t ObjectRecord::getSignificance() const
{ return mSignificance;}

//------------------------------------------------------------------------------
uint16_t ObjectRecord::getSpecialEffectId1() const
{ return mSpecialEffectId1;}

//------------------------------------------------------------------------------
uint16_t ObjectRecord::getSpecialEffectId2() const
{ return mSpecialEffectId2;}

//------------------------------------------------------------------------------
//return the transparency with a double in range [0.0, 1.0] (OpenGL style)
//0 being transparent
//1 being opaque
double ObjectRecord::getTransparency() const
{
    double r = 1.0 - (mTransparency / 65535.0);
    return r;
}

//------------------------------------------------------------------------------
bool ObjectRecord::hasFlag(ObjectRecord::flag iFlag) const
{
    return false;
}

//------------------------------------------------------------------------------
bool ObjectRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    
    bool ok = true;
    ok &= readChar(iRawRecord, 8, mAsciiId);
    ok &= readInt32(iRawRecord, mFlags);
    ok &= readInt16(iRawRecord, mRelativePriority);
    ok &= readUint16(iRawRecord, mTransparency);
    ok &= readInt16(iRawRecord, mSpecialEffectId1);
    ok &= readInt16(iRawRecord, mSpecialEffectId2);
    ok &= readInt16(iRawRecord, mSignificance);
    return ok;
}
