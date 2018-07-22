#include "LightPointAnimationPaletteRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace OpenFlight;

//------------------------------------------------------------------------------
LightPointAnimationPaletteRecord::LightPointAnimationPaletteRecord(PrimaryRecord* ipParent) :
    AncillaryRecord(ipParent),
    mName(),
    mIndex(-1),
    mAnimationPeriod(0),
    mAnimationPhaseDelay(0),
    mAnimationEnabledPeriod(0),
    mRotationAxisX(0),
    mRotationAxisY(0),
    mRotationAxisZ(0),
    mFlags(0),
    mAnimationType(atFlashingSequence),
    mMorseCodeTiming(mctStandart),
    mWordRate(0),
    mCharacterRate(0),
    mMorseCodeString(""),
    mNumberOfFlashingSequences(0),
    mSequences()
{}

//------------------------------------------------------------------------------
LightPointAnimationPaletteRecord::~LightPointAnimationPaletteRecord()
{}

//------------------------------------------------------------------------------
float LightPointAnimationPaletteRecord::getAnimationEnabledPeriod() const
{ return mAnimationEnabledPeriod; }

//------------------------------------------------------------------------------
float LightPointAnimationPaletteRecord::getAnimationPeriod() const
{ return mAnimationPeriod; }

//------------------------------------------------------------------------------
float LightPointAnimationPaletteRecord::getAnimationPhaseDelay() const
{ return mAnimationPhaseDelay; }

//------------------------------------------------------------------------------
LightPointAnimationPaletteRecord::AnimationType LightPointAnimationPaletteRecord::getAnimationType() const
{ return mAnimationType; }

//------------------------------------------------------------------------------
int32_t LightPointAnimationPaletteRecord::getCharacterRate() const
{ return mCharacterRate; }

//------------------------------------------------------------------------------
int32_t LightPointAnimationPaletteRecord::getFlags() const
{ return mFlags; }

//------------------------------------------------------------------------------
int32_t LightPointAnimationPaletteRecord::getIndex() const
{ return mIndex; }

//------------------------------------------------------------------------------
std::string LightPointAnimationPaletteRecord::getMorseCodeString() const
{ return mMorseCodeString; }

//------------------------------------------------------------------------------
LightPointAnimationPaletteRecord::MorseCodeTiming LightPointAnimationPaletteRecord::getMorseCodeTiming() const
{ return mMorseCodeTiming; }

//------------------------------------------------------------------------------
std::string LightPointAnimationPaletteRecord::getName() const
{ return mName; }

//------------------------------------------------------------------------------
int32_t LightPointAnimationPaletteRecord::getNumberOfFlashingSequences() const
{ return mNumberOfFlashingSequences; }

//------------------------------------------------------------------------------
float LightPointAnimationPaletteRecord::getRotationAxisX() const
{ return mRotationAxisX; }

//------------------------------------------------------------------------------
float LightPointAnimationPaletteRecord::getRotationAxisY() const
{ return mRotationAxisY; }

//------------------------------------------------------------------------------
float LightPointAnimationPaletteRecord::getRotationAxisZ() const
{ return mRotationAxisZ; }

//------------------------------------------------------------------------------
int32_t LightPointAnimationPaletteRecord::getWordRate() const
{ return mWordRate; }

//------------------------------------------------------------------------------
bool LightPointAnimationPaletteRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    //reserved
    iRawRecord.seekg(startPos + 8);
    ok &= readChar(iRawRecord, 256, mName);
    ok &= readInt32(iRawRecord, mIndex);
    ok &= readFloat32(iRawRecord, mAnimationPeriod);
    ok &= readFloat32(iRawRecord, mAnimationPhaseDelay);
    ok &= readFloat32(iRawRecord, mAnimationEnabledPeriod);
    ok &= readFloat32(iRawRecord, mRotationAxisX);
    ok &= readFloat32(iRawRecord, mRotationAxisY);
    ok &= readFloat32(iRawRecord, mRotationAxisZ);
    ok &= readInt32(iRawRecord, mFlags);
    
    int32_t t;
    ok &= readInt32(iRawRecord, t);
    mAnimationType = (AnimationType)t;
    
    ok &= readInt32(iRawRecord, t);
    mMorseCodeTiming = (MorseCodeTiming)t;
    
    ok &= readInt32(iRawRecord, mWordRate);
    ok &= readInt32(iRawRecord, mCharacterRate);
    
    ok &= readChar(iRawRecord, 1024, mMorseCodeString);
    ok &= readInt32(iRawRecord, mNumberOfFlashingSequences);
    
    for(int i = 0; i < mNumberOfFlashingSequences; ++i)
    {
        Sequence s;
        
        uint32_t t1;
        ok &= readUint32(iRawRecord, t1);
        s.mState = (Sequence::State)t1;
        
        ok &= readFloat32(iRawRecord, s.mDuration);
        ok &= readUint32(iRawRecord, s.mColor);
        
        mSequences.push_back(s);
    }
    
    return ok;
}
