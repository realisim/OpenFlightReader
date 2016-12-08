
#include <cassert>
#include "PaletteRecords.h"
#include <sstream>
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
bool ColorPaletteRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );
    
    bool ok = true;
    
    iss.seekg(132);
    //color format is a, b, g, r.
    for(int i = 0; i < kNumberOfColorEntries && ok; ++i)
    {
        uint32_t color;
        ok &= readUint32(iss, color);
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
bool LightSourcePaletteRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );
    
    bool ok = true;
    
    //skip opcode and record length
    int32_t dummyInt32;
    iss.seekg(4);
    ok &= readInt32(iss, mIndex);
    
    iss.seekg(16);
    ok &= readChar(iss, 20, mName);
    
    iss.seekg(40);
    ok &= readColor4f(iss, mAmbient);
    ok &= readColor4f(iss, mDiffuse);
    ok &= readColor4f(iss, mSpecular);
    ok &= readInt32(iss, dummyInt32);
    mLightType = (lightType)dummyInt32;
    
    iss.seekg(132);
    ok &= readFloat32(iss, mSpotExponentialDropoff);
    ok &= readFloat32(iss, mSpotCutoffAngle);
    ok &= readFloat32(iss, mYaw);
    ok &= readFloat32(iss, mPitch);
    ok &= readFloat32(iss, mConstantAttenuationCoefficient);
    ok &= readFloat32(iss, mLinearAttenuationCoefficient);
    ok &= readFloat32(iss, mQuadraticAttenuationCoefficient);
    
    ok &= readInt32(iss, dummyInt32);
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
bool MaterialPaletteRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );
    
    bool ok = true;
    
    //skip opcode and record length
    iss.seekg(4);
    
    ok &= readInt32(iss, mIndex);
    ok &= readChar(iss, 12, mName);
    ok &= readInt32(iss, mFlags);
    ok &= readColor3f(iss, mAmbient);
    ok &= readColor3f(iss, mDiffuse);
    ok &= readColor3f(iss, mSpecular);
    ok &= readColor3f(iss, mEmissive);
    ok &= readFloat32(iss, mShininess);
    ok &= readFloat32(iss, mAlpha);
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
bool VertexPaletteRecord::addVertexRawRecord(const std::string& iRawRecord)
{
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );
    bool ok = true;
    
    uint16_t dummyInt16;
    uint16_t recordLength = 0;
    ok &= readUint16(iss, dummyInt16);
    opCode oc = (opCode)dummyInt16;
    ok &= readUint16(iss, recordLength);
    if(ok)
    {
        Vertex v;
        
        ok &= readUint16(iss, v.mColorNameIndex);
        ok &= readUint16(iss, v.mFlags);
        ok &= readVector3d(iss, v.mCoordinate);
        
        int32_t dummyInt32;
        switch (oc)
        {
            case ocVertexWithColor:
            {
                ok &= readInt32(iss, dummyInt32);
                v.mPackedColor = Color4ub(dummyInt32);
                
                ok &= readUint32(iss, v.mColorIndex);
            }break;
            case ocVertexWithColorAndNormal:
            {
                ok &= readVector3f(iss, v.mNormal);
                ok &= readInt32(iss, dummyInt32);
                v.mPackedColor = Color4ub(dummyInt32);
                
                ok &= readUint32(iss, v.mColorIndex);
            }break;
            case ocVertexWithColorNormalAndUv:
            {
                ok &= readVector3f(iss, v.mNormal);
                ok &= readVector2f(iss, v.mTextureCoordinate);
                ok &= readInt32(iss, dummyInt32);
                v.mPackedColor = Color4ub(dummyInt32);
                
                ok &= readUint32(iss, v.mColorIndex);
            }break;
            case ocVertexWithColorAndUv:
            {
                ok &= readVector2f(iss, v.mTextureCoordinate);
                ok &= readInt32(iss, dummyInt32);
                v.mPackedColor = Color4ub(dummyInt32);
                
                ok &= readUint32(iss, v.mColorIndex);
            }break;
                
            default: break;
        }
        
        mOffsetToVertexIndex.insert( make_pair(mOffset, mVertices.size() ) );
        mOffset += iRawRecord.size();
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
bool VertexPaletteRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );
    
    bool ok = true;
    
    //skip opcode and record length
    iss.seekg(4);
    
    //since all vertex data are contained in the records following
    //the vertex palette, there is nothing to read here!
    
    //The vertex palette will be populated by the reader when
    //it encouters the actual vertex record.
    
    return ok;
}
