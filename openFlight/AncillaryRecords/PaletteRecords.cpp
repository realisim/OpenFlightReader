
#include <cassert>
#include "PaletteRecords.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

namespace
{
    const int kNumberOfColorEntries = 1024;
}

//-------------------------------------------------------------------------
//--- ColorPalette
//-------------------------------------------------------------------------
ColorPaletteRecord::ColorPaletteRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{
    //there are 1024 entries in the palette
    mColors.resize(kNumberOfColorEntries);
}

//-------------------------------------------------------------------------
bool ColorPaletteRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    
    // 132 is where the data starts, 
    //
    iRawRecord.seekg(startPos + 132);
    //color format is a, b, g, r.
    for(int i = 0; i < kNumberOfColorEntries && ok; ++i)
    {
        uint32_t color;
        ok &= readUint32(iRawRecord, color);
        swapBytes4((void*)&color); //swap to have r g b a;
        
        mColors[i] = Color4ub(color);
    }
    
    // bool hasColorName = getRecordLength() > 4228;
    // read color name table
    // not implemented yet...
    //
    return ok;
}

//-------------------------------------------------------------------------
//--- LightSourcePaletteRecord
//-------------------------------------------------------------------------
LightSourcePaletteRecord::LightSourcePaletteRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{}

//------------------------------------------------------------------------------
const Color4f& LightSourcePaletteRecord::getAmbient() const
{ return mAmbient;}

//------------------------------------------------------------------------------
float LightSourcePaletteRecord::getConstantAttenuationCoefficient() const
{ return mConstantAttenuationCoefficient;}

//------------------------------------------------------------------------------
const Color4f& LightSourcePaletteRecord::getDiffuse() const
{ return mDiffuse;}

//------------------------------------------------------------------------------
int32_t LightSourcePaletteRecord::getIndex() const
{ return mIndex;}

//------------------------------------------------------------------------------
LightSourcePaletteRecord::lightType LightSourcePaletteRecord::getLightType() const
{ return mLightType;}

//------------------------------------------------------------------------------
float LightSourcePaletteRecord::getLinearAttenuationCoefficient() const
{ return mLinearAttenuationCoefficient;}

//------------------------------------------------------------------------------
std::string LightSourcePaletteRecord::getName() const
{ return mName;}

//------------------------------------------------------------------------------
float LightSourcePaletteRecord::getPitch() const
{ return mPitch;}

//------------------------------------------------------------------------------
float LightSourcePaletteRecord::getQuadraticAttenuationCoefficient() const
{ return mQuadraticAttenuationCoefficient;}

//------------------------------------------------------------------------------
const Color4f& LightSourcePaletteRecord::getSpecular() const
{ return mSpecular;}

//------------------------------------------------------------------------------
float LightSourcePaletteRecord::getSpotCutoffAngle() const
{ return mSpotCutoffAngle;}

//------------------------------------------------------------------------------
float LightSourcePaletteRecord::getSpotExponentialDropoff() const
{ return mSpotExponentialDropoff;}

//------------------------------------------------------------------------------
float LightSourcePaletteRecord::getYaw() const
{ return mYaw;}

//------------------------------------------------------------------------------
bool LightSourcePaletteRecord::isModelingLight() const
{ return mIsModelingLight;}

//-------------------------------------------------------------------------
bool LightSourcePaletteRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    int32_t dummyInt32;

    ok &= readInt32(iRawRecord, mIndex);
    
    iRawRecord.seekg(startPos + 16);
    ok &= readChar(iRawRecord, 20, mName);
    
    iRawRecord.seekg(startPos + 40);
    ok &= readColor4f(iRawRecord, mAmbient);
    ok &= readColor4f(iRawRecord, mDiffuse);
    ok &= readColor4f(iRawRecord, mSpecular);
    ok &= readInt32(iRawRecord, dummyInt32);
    mLightType = (lightType)dummyInt32;
    
    iRawRecord.seekg(startPos + 132);
    ok &= readFloat32(iRawRecord, mSpotExponentialDropoff);
    ok &= readFloat32(iRawRecord, mSpotCutoffAngle);
    ok &= readFloat32(iRawRecord, mYaw);
    ok &= readFloat32(iRawRecord, mPitch);
    ok &= readFloat32(iRawRecord, mConstantAttenuationCoefficient);
    ok &= readFloat32(iRawRecord, mLinearAttenuationCoefficient);
    ok &= readFloat32(iRawRecord, mQuadraticAttenuationCoefficient);
    
    ok &= readInt32(iRawRecord, dummyInt32);
    mIsModelingLight = dummyInt32 == 0 ? false : true;
    return ok;
}

//-------------------------------------------------------------------------
//--- MaterialPaletteRecord
//-------------------------------------------------------------------------
MaterialPaletteRecord::MaterialPaletteRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{}

//------------------------------------------------------------------------------
float MaterialPaletteRecord::getAlpha() const
{ return mAlpha;}

//------------------------------------------------------------------------------
const Color3f& MaterialPaletteRecord::getAmbient() const
{ return mAmbient;}

//------------------------------------------------------------------------------
const Color3f& MaterialPaletteRecord::getDiffuse() const
{ return mDiffuse;}

//------------------------------------------------------------------------------
const Color3f& MaterialPaletteRecord::getEmissive() const
{ return mEmissive;}

//------------------------------------------------------------------------------
int MaterialPaletteRecord::getFlags() const
{ return mFlags;}

//------------------------------------------------------------------------------
int MaterialPaletteRecord::getIndex() const
{ return mIndex;}

//------------------------------------------------------------------------------
std::string MaterialPaletteRecord::getName() const
{ return mName;}

//------------------------------------------------------------------------------
float MaterialPaletteRecord::getShininess() const
{ return mShininess;}

//------------------------------------------------------------------------------
const Color3f& MaterialPaletteRecord::getSpecular() const
{ return mSpecular;}

//-------------------------------------------------------------------------
bool MaterialPaletteRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    
    ok &= readInt32(iRawRecord, mIndex);
    ok &= readChar(iRawRecord, 12, mName);
    ok &= readInt32(iRawRecord, mFlags);
    ok &= readColor3f(iRawRecord, mAmbient);
    ok &= readColor3f(iRawRecord, mDiffuse);
    ok &= readColor3f(iRawRecord, mSpecular);
    ok &= readColor3f(iRawRecord, mEmissive);
    ok &= readFloat32(iRawRecord, mShininess);
    ok &= readFloat32(iRawRecord, mAlpha);
    return ok;
}

//-------------------------------------------------------------------------
//--- VertexPaletteRecord
//-------------------------------------------------------------------------
VertexPaletteRecord::VertexPaletteRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent),
mOffset(8)
{
    //As stated by the specification, the first vertex will be found
    //at offset 8.
}

//-------------------------------------------------------------------------
bool VertexPaletteRecord::addVertexRawRecord(std::ifstream& iRawRecord)
{
    bool ok = true;
    
    uint16_t dummyInt16;
    uint16_t recordLength = 0;
    ok &= readUint16(iRawRecord, dummyInt16);
    opCode oc = (opCode)dummyInt16;
    ok &= readUint16(iRawRecord, recordLength);
    if(ok)
    {
        Vertex v;
        
        ok &= readUint16(iRawRecord, v.mColorNameIndex);
        ok &= readUint16(iRawRecord, v.mFlags);
        ok &= readVector3d(iRawRecord, v.mCoordinate);
        
        int32_t dummyInt32;
        switch (oc)
        {
            case ocVertexWithColor:
            {
            }break;
            case ocVertexWithColorAndNormal:
            {
                ok &= readVector3f(iRawRecord, v.mNormal);
            }break;
            case ocVertexWithColorNormalAndUv:
            {
                ok &= readVector3f(iRawRecord, v.mNormal);
                ok &= readVector2f(iRawRecord, v.mTextureCoordinate);
            }break;
            case ocVertexWithColorAndUv:
            {
                ok &= readVector2f(iRawRecord, v.mTextureCoordinate);
            }break;
                
            default: break;
        }
        
        // do not read color if the flags is set, since they are
        // undefined...
        if( !v.hasFlag(Vertex::fNoColor) )
        {
            //packed color is in a,b,g,r and we want r,g,b,a
            ok &= readInt32(iRawRecord, dummyInt32);
            swapBytes4((void*) &dummyInt32);
            v.mPackedColor = Color4ub(dummyInt32);
            ok &= readUint32(iRawRecord, v.mColorIndex);
        }
        
        mOffsetToVertexIndex.insert( make_pair(mOffset, (int)mVertices.size() ) );
        mOffset += recordLength;
        mVertices.push_back( v );
    }
    return ok;
}

//-------------------------------------------------------------------------
int VertexPaletteRecord::getIndexFromByteOffset(int iOffset) const
{
    auto it = mOffsetToVertexIndex.find(iOffset);
    return it != mOffsetToVertexIndex.end() ? it->second : -1;
}

//-------------------------------------------------------------------------
int VertexPaletteRecord::getNumberOfVertices() const
{ return (int)mVertices.size(); }

//-------------------------------------------------------------------------
const Vertex& VertexPaletteRecord::getVertex(int iIndex) const
{
    assert(iIndex >= 0 && iIndex < mVertices.size());
    return mVertices.at(iIndex);
}

//-------------------------------------------------------------------------
const std::vector<Vertex>& VertexPaletteRecord::getVertices() const
{ return mVertices; }

//-------------------------------------------------------------------------
bool VertexPaletteRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    
    //since all vertex data are contained in the records following
    //the vertex palette, there is nothing to read here!
    
    //The vertex palette will be populated by the reader when
    //it encouters the actual vertex record.
    
    // it is possible to skip the whole vertex data by skipping
    // all the following records
    //
    // ocVertexWithColor:
    // ocVertexWithColorAndNormal:
    // ocVertexWithColorNormalAndUv:
    // ocVertexWithColorAndUv:
    //
    //
    
    return ok;
}
