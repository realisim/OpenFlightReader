#include <cassert>
#include "MultiTextureRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
MultiTextureRecord::MultiTextureRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent),
mAttributeMask(0)
{
    // -1 will become 65535 because storage is uint16_t
    memset(&mTexturePatternIndices[0], -1, 7*sizeof(uint16_t));
    memset(&mMappingIndices[0], -1, 7*sizeof(uint16_t));
    memset(&mEffects[0], -1, 7*sizeof(uint16_t));
    memset(&mData[0], -1, 7*sizeof(uint16_t));
}

//-------------------------------------------------------------------------
MultiTextureRecord::~MultiTextureRecord()
{
}

//-------------------------------------------------------------------------
int MultiTextureRecord::getData(int iLayerIndex) const
{
    int r = -1;
    if(iLayerIndex >= 0 && iLayerIndex < 7)
    {
        r = mData[iLayerIndex];
        if(r == 65535){r = -1;}
    }
    return r;
}

//-------------------------------------------------------------------------
MultiTextureRecord::EffectType MultiTextureRecord::getEffect(int iLayerIndex) const
{
    int e = -1;
    if(iLayerIndex >= 0 && iLayerIndex < 7)
    {
        e = mEffects[iLayerIndex];
    }
    
    EffectType r = etReserved;
    
    if(e == 0)
    { r = etTextureEnvironment; }
    else if(e == 1)
    { r = etBump; }
    else if(e >= 2 && e <= 100)
    { r = etReserved; }
    else //( e > 100)
    {
        r = etUserDefined;
    }
    
    return r;
}

//-------------------------------------------------------------------------
int MultiTextureRecord::getMappingIndex(int iLayerIndex) const
{
    int r = -1;
    if(iLayerIndex >= 0 && iLayerIndex < 7)
    {
        r = mMappingIndices[iLayerIndex];
        if(r == 65535){r = -1;}
    }
    return r;
}

//-------------------------------------------------------------------------
int MultiTextureRecord::getTexturePatternIndex(int iLayerIndex) const
{
    int r = -1;
    if(iLayerIndex >= 0 && iLayerIndex < 7)
    {
        r = mTexturePatternIndices[iLayerIndex];
        if(r == 65535){r = -1;}
    }
    return r;
}

//-------------------------------------------------------------------------
bool MultiTextureRecord::hasLayers() const
{
    //keep only first 7 bits (counting from the left side... see doc)
    const int t = mAttributeMask & 0xFF000000;

    return t != 0;
}

//-------------------------------------------------------------------------
bool MultiTextureRecord::hasLayer(int iLayerIndex) const
{
    // masked bits starts on the left.... so 31 - iLayerIndex
    //
    return mAttributeMask & (0x1 << (31 - iLayerIndex));
}

//-------------------------------------------------------------------------
bool MultiTextureRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    ok &= readInt32(iRawRecord, mAttributeMask);
    
    for(int i = 0; i < 7; ++i)
    {
        if(hasLayer(i))
        {
            uint16_t value;
            ok &= readUint16(iRawRecord, value);
            mTexturePatternIndices[i] = value;
            
            ok &= readUint16(iRawRecord, value);
            mEffects[i] = value;

            ok &= readUint16(iRawRecord, value);
            mMappingIndices[i] = value;
            
            ok &= readUint16(iRawRecord, value);
            mData[i] = value;
        }
    }
    
    return ok;
}