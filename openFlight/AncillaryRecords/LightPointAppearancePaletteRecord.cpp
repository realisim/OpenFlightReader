#include "LightPointAppearancePaletteRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace OpenFlight;

//------------------------------------------------------------------------------
LightPointAppearancePaletteRecord::LightPointAppearancePaletteRecord(PrimaryRecord* ipParent) :
    AncillaryRecord(ipParent),
    mName(""),
    mIndex(-1),
    mSurfaceMaterialCode(-1),
    mFeatureId(-1),
    mBackColorForBidirectionalPoints(0),
//    mDisplayMode(dmRaster),
    mIntensity(1.0),
    mBackIntensity(1.0),
//    mFadingMode(fmEnabled),
//    mFogPunchMode(fpmDisabled),
//    mDirectionalMode(dmEnabled),
//    mRangeMode(rmUseZBuffer),
    mMinPixelSize(0),
    mMaxPixelSize(0),
    mActualSize(0),
//    mTransparentFalloffExponent(0),
//    mTransparentFalloffScalar(0),
//    mTransparentFalloffClamp(0),
//    mFogScalar(0),
//    mFogIntensity(0),
//    mSizeDifferenceThreshold(0),
    mDirectionality(dOmnidirectional)
//    mHorizontalLobeAngle(0),
//    mVerticalLobeAngle(0),
//    mLobeRollAngle(0),
//    mDirectionalFalloffExponent(0),
//    mDirectionalAmbientIntensity(0),
//    mSignificance(0)
//    mFlags(0),
//    mVisibilityRange(0),
//    mFadeRangeRatio(0),
//    mFadeInDuration(0),
//    mFadeOutDuration(0),
//    mLodRangeRation(0),
//    mLodScale(0),
//    mTexturePatternIndex(-1)
{}

//------------------------------------------------------------------------------
LightPointAppearancePaletteRecord::~LightPointAppearancePaletteRecord()
{}

//------------------------------------------------------------------------------
float LightPointAppearancePaletteRecord::getActualSize() const
{ return mActualSize; }

//------------------------------------------------------------------------------
uint32_t LightPointAppearancePaletteRecord::getBackColorForBidirectionalPoints() const
{ return mBackColorForBidirectionalPoints; }

//------------------------------------------------------------------------------
float LightPointAppearancePaletteRecord::getBackIntensity() const
{ return mBackIntensity; }

//------------------------------------------------------------------------------
LightPointAppearancePaletteRecord::Directionality LightPointAppearancePaletteRecord::getDirectionality() const
{ return mDirectionality; }

//------------------------------------------------------------------------------
uint16_t LightPointAppearancePaletteRecord::getFeatureId() const
{ return mFeatureId; }

//------------------------------------------------------------------------------
int32_t LightPointAppearancePaletteRecord::getIndex() const
{ return mIndex; }

//------------------------------------------------------------------------------
float LightPointAppearancePaletteRecord::getIntensity() const
{ return mIntensity; }

//------------------------------------------------------------------------------
float LightPointAppearancePaletteRecord::getMaxPixelSize() const
{ return mMaxPixelSize; }

//------------------------------------------------------------------------------
float LightPointAppearancePaletteRecord::getMinPixelSize() const
{ return mMinPixelSize; }

//------------------------------------------------------------------------------
std::string LightPointAppearancePaletteRecord::getName() const
{ return mName; }

//------------------------------------------------------------------------------
uint16_t LightPointAppearancePaletteRecord::getSurfaceMaterialCode() const
{ return mSurfaceMaterialCode; }

//------------------------------------------------------------------------------
bool LightPointAppearancePaletteRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    //reserved
    iRawRecord.seekg(startPos + 8);
    ok &= readChar(iRawRecord, 256, mName);
    ok &= readInt32(iRawRecord, mIndex);
    ok &= readUint16(iRawRecord, mSurfaceMaterialCode);
    ok &= readUint16(iRawRecord, mFeatureId);
    ok &= readUint32(iRawRecord, mBackColorForBidirectionalPoints);
    
    //displayMode
    
    iRawRecord.seekg(startPos + 280);
    ok &= readFloat32(iRawRecord, mIntensity);
    ok &= readFloat32(iRawRecord, mBackIntensity);
    
    //skipping
    iRawRecord.seekg(startPos + 312);
    ok &= readFloat32(iRawRecord, mMinPixelSize);
    ok &= readFloat32(iRawRecord, mMaxPixelSize);
    ok &= readFloat32(iRawRecord, mActualSize);
    
    //skipping
    iRawRecord.seekg(startPos + 352);
    int32_t t;
    ok &= readInt32(iRawRecord, t);
    mDirectionality = (Directionality)t;
    
    return ok;
}