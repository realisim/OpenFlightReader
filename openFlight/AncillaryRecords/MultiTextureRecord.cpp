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
    memset(&mTexturePatternIndices[0], 0, 7*sizeof(uint32_t));
    memset(&mMappingIndices[0], 0, 7*sizeof(uint32_t));
    memset(&mEffects[0], 0, 7*sizeof(uint32_t));
    memset(&mData[0], 0, 7*sizeof(uint32_t));
}

//-------------------------------------------------------------------------
int MultiTextureRecord::getData(int iLayerIndex) const
{
    int r = -1;
    if(iLayerIndex >= 0 && iLayerIndex < 7)
    {
        r = mData[iLayerIndex];
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
    { e = etTextureEnvironment; }
    else if(e == 1)
    { e = etBump; }
    else if(e >= 2 && e <= 100)
    { e = etReserved; }
    else //( e > 100)
    {
        e = etUserDefined;
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
    }
    return r;
}

//-------------------------------------------------------------------------
bool MultiTextureRecord::hasLayers() const
{
    //keep only first 7 bits
    const int t = mAttributeMask & 0x000F;

    return t > 0;
}

//-------------------------------------------------------------------------
bool MultiTextureRecord::hasLayer(int iLayerIndex) const
{
    return mAttributeMask & (0x1 << iLayerIndex);
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
            uint32_t value;
            ok &= readUint32(iRawRecord, value);
            mTexturePatternIndices[i] = value;
            
            ok &= readUint32(iRawRecord, value);
            mMappingIndices[i] = value;
            
            ok &= readUint32(iRawRecord, value);
            mEffects[i] = value;
            
            ok &= readUint32(iRawRecord, value);
            mData[i] = value;
        }
    }
    
    return ok;
}