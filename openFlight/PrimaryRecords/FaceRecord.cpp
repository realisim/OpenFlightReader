
#include "FaceRecord.h"
#include "AncillaryRecords/MultiTextureRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
FaceRecord::FaceRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("n/a"),
mIrColorCode(0),
mRelativePriority(0),
mDrawType(0),
mShouldDrawTexturedFaceWhite(0),
mColorNameIndex(0),
mAlternateColorNameIndex(0),
mBillboardTemplate(0),
mDetailTexturePattern(0),
mTexturePatternIndex(0),
mMaterialIndex(0),
mSurfaceMaterialCode(0),
mFeatureId(0),
mIrMaterialCode(0),
mTransparency(0),
mLodGenerationControl(0),
mLineStyleIndex(0),
mFlags(0),
mLightMode(0),
mPackedColor(0),
mAlternatePackedColor(0),
mTextureMappingIndex(0),
mColorIndex(0),
mAlternateColorIndex(0),
mShaderIndex(-1),
mpMultiTextureRecord(nullptr)
{}

//------------------------------------------------------------------------------
FaceRecord::~FaceRecord()
{
    mpMultiTextureRecord = nullptr;
}

//------------------------------------------------------------------------------
uint32_t FaceRecord::getAlternateColorIndex() const
{ return mAlternateColorIndex;}

//------------------------------------------------------------------------------
uint16_t FaceRecord::getAlternateColorNameIndex() const
{ return mAlternateColorNameIndex;}

//------------------------------------------------------------------------------
OpenFlight::Color4ub FaceRecord::getAlternatePackedColor() const
{ 
    uint32_t t = mAlternatePackedColor;
    swapBytes4((void*)&t); //packed color is in a,b,g,r and we want r,g,b,a
    return Color4ub(t);
}

//------------------------------------------------------------------------------
const std::string& FaceRecord::getAsciiId() const
{ return mAsciiId;}

//------------------------------------------------------------------------------
FaceRecord::billboardTemplate FaceRecord::getBillboardTemplate() const
{ return (billboardTemplate)mBillboardTemplate; }

//------------------------------------------------------------------------------
uint32_t FaceRecord::getColorIndex() const
{ return mColorIndex;}

//------------------------------------------------------------------------------
uint16_t FaceRecord::getColorNameIndex() const
{ return mColorNameIndex;}

//------------------------------------------------------------------------------
int16_t FaceRecord::getDetailTexturePattern() const
{ return mDetailTexturePattern;}

//------------------------------------------------------------------------------
FaceRecord::drawType FaceRecord::getDrawType() const
{ return (drawType)mDrawType;}

//------------------------------------------------------------------------------
int16_t FaceRecord::getFeatureId() const
{ return mFeatureId;}

//------------------------------------------------------------------------------
int32_t FaceRecord::getFlags() const
{ return mFlags;}

//------------------------------------------------------------------------------
int32_t FaceRecord::getIrColorCode() const
{ return mIrColorCode;}

//------------------------------------------------------------------------------
int32_t FaceRecord::getIrMaterialCode() const
{ return mIrMaterialCode;}

//------------------------------------------------------------------------------
FaceRecord::lightMode FaceRecord::getLightMode() const
{ return (lightMode)mLightMode;}

//------------------------------------------------------------------------------
uint8_t FaceRecord::getLineStyleIndex() const
{ return mLineStyleIndex;}

//------------------------------------------------------------------------------
uint8_t FaceRecord::getLodGenerationControl() const
{ return mLodGenerationControl;}

//------------------------------------------------------------------------------
int16_t FaceRecord::getMaterialIndex() const
{ return mMaterialIndex;}

//------------------------------------------------------------------------------
MultiTextureRecord* FaceRecord::getMultiTextureRecord()
{ return mpMultiTextureRecord;}

//------------------------------------------------------------------------------
OpenFlight::Color4ub FaceRecord::getPackedColor() const
{ 
    uint32_t t = mPackedColor;
    swapBytes4((void*)&t); //packed color is in a,b,g,r and we want r,g,b,a
    return Color4ub(t);
}

//------------------------------------------------------------------------------
int16_t FaceRecord::getRelativePriority() const
{ return mRelativePriority;}

//------------------------------------------------------------------------------
int16_t FaceRecord::getShaderIndex() const
{ return mShaderIndex;}

//------------------------------------------------------------------------------
bool FaceRecord::getShouldDrawTexturedFaceWhite() const
{ return mShouldDrawTexturedFaceWhite != 0; }

//------------------------------------------------------------------------------
int16_t FaceRecord::getSurfaceMaterialCode() const
{ return mSurfaceMaterialCode;}

//------------------------------------------------------------------------------
int16_t FaceRecord::getTextureMappingIndex() const
{ return mTextureMappingIndex;}

//------------------------------------------------------------------------------
int16_t FaceRecord::getTexturePatternIndex() const
{ return mTexturePatternIndex;}

//------------------------------------------------------------------------------
//return the transparency with a double in range [0.0, 1.0] (OpenGL style)
//0 being transparent
//1 being opaque
double FaceRecord::getTransparency() const
{
    double r = 1.0 - (mTransparency / 65535.0);
    return r;
}

//-------------------------------------------------------------------------
// Explain...
void FaceRecord::handleAddedAncillaryRecord(AncillaryRecord* ipAncillary)
{
    PrimaryRecord::handleAddedAncillaryRecord(ipAncillary);

    switch (ipAncillary->getOpCode())
    {
    case ocMultitexture: mpMultiTextureRecord = (MultiTextureRecord*)ipAncillary; break;    
    default: break;
    }
}

//------------------------------------------------------------------------------
bool FaceRecord::hasMultiTexture() const
{
    return mpMultiTextureRecord != nullptr;
}

//------------------------------------------------------------------------------
bool FaceRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    ok &= readChar(iRawRecord, 8, mAsciiId);
    ok &= readInt32(iRawRecord, mIrColorCode);
    ok &= readInt16(iRawRecord, mRelativePriority);
    ok &= readInt8(iRawRecord, mDrawType);
    ok &= readInt8(iRawRecord, mShouldDrawTexturedFaceWhite);
    ok &= readUint16(iRawRecord, mColorNameIndex);
    ok &= readUint16(iRawRecord, mAlternateColorNameIndex);
    
    iRawRecord.seekg(startPos + 25);
    ok &= readInt8(iRawRecord, mBillboardTemplate);
    ok &= readInt16(iRawRecord, mDetailTexturePattern);
    ok &= readInt16(iRawRecord, mTexturePatternIndex);
    ok &= readInt16(iRawRecord, mMaterialIndex);
    ok &= readInt16(iRawRecord, mSurfaceMaterialCode);
    ok &= readInt16(iRawRecord, mFeatureId);
    ok &= readInt32(iRawRecord, mIrMaterialCode);
    ok &= readUint16(iRawRecord, mTransparency);
    ok &= readUint8(iRawRecord, mLodGenerationControl);
    ok &= readUint8(iRawRecord, mLineStyleIndex);
    ok &= readInt32(iRawRecord, mFlags);
    ok &= readUint8(iRawRecord, mLightMode);
    
    iRawRecord.seekg(startPos + 56);
    ok &= readUint32(iRawRecord, mPackedColor); //a,b,g,r
    swapBytes4((void*)&mPackedColor);
    ok &= readUint32(iRawRecord, mAlternatePackedColor);
    swapBytes4((void*)&mAlternatePackedColor);
    ok &= readInt16(iRawRecord, mTextureMappingIndex);

    iRawRecord.seekg(startPos + 68);
    ok &= readUint32(iRawRecord, mColorIndex);
    ok &= readUint32(iRawRecord, mAlternateColorIndex);

    if(iVersion >= 1600)
    {
        iRawRecord.seekg(startPos + 78);
        ok &= readInt16(iRawRecord, mShaderIndex);
    }
    return ok;
}
