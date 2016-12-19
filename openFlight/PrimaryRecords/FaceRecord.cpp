
#include "FaceRecord.h"
#include <sstream>
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
mShaderIndex(-1)
{}

//------------------------------------------------------------------------------
FaceRecord::~FaceRecord()
{}

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

//------------------------------------------------------------------------------
bool FaceRecord::parseRecord(const std::string& iRawRecord, int iVersion)
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
    ok &= readInt32(iss, mIrColorCode);
    ok &= readInt16(iss, mRelativePriority);
    ok &= readInt8(iss, mDrawType);
    ok &= readInt8(iss, mShouldDrawTexturedFaceWhite);
    ok &= readUint16(iss, mColorNameIndex);
    ok &= readUint16(iss, mAlternateColorNameIndex);
    
    iss.seekg(25);
    ok &= readInt8(iss, mBillboardTemplate);
    ok &= readInt16(iss, mDetailTexturePattern);
    ok &= readInt16(iss, mTexturePatternIndex);
    ok &= readInt16(iss, mMaterialIndex);
    ok &= readInt16(iss, mSurfaceMaterialCode);
    ok &= readInt16(iss, mFeatureId);
    ok &= readInt32(iss, mIrMaterialCode);
    ok &= readUint16(iss, mTransparency);
    ok &= readUint8(iss, mLodGenerationControl);
    ok &= readUint8(iss, mLineStyleIndex);
    ok &= readInt32(iss, mFlags);
    ok &= readUint8(iss, mLightMode);
    
    iss.seekg(56);
    ok &= readUint32(iss, mPackedColor); //a,b,g,r
    swapBytes4((void*)&mPackedColor);
    ok &= readUint32(iss, mAlternatePackedColor);
    swapBytes4((void*)&mAlternatePackedColor);
    ok &= readInt16(iss, mTextureMappingIndex);

    iss.seekg(68);
    ok &= readUint32(iss, mColorIndex);
    ok &= readUint32(iss, mAlternateColorIndex);

    if(iVersion >= 1600)
    {
        iss.seekg(78);
        ok &= readInt16(iss, mShaderIndex);
    }
    return ok;
}
