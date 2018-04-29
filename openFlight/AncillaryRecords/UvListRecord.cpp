
#include <cassert>
#include "UvListRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
UvListRecord::UvListRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{}

//-------------------------------------------------------------------------
Vector2f UvListRecord::getUv(int iLayerIndex, int iVertexIndex) const
{
    Vector2f r;
    
    r.mX = mUCoordinates[iLayerIndex][iVertexIndex];
    r.mY = mUCoordinates[iLayerIndex][iVertexIndex];
    
    return r;
}

//-------------------------------------------------------------------------
bool UvListRecord::hasLayers() const
{
    //keep only first 7 bits
    const int t = mAttributeMask & 0x000F;
    
    return t > 0;
}

//-------------------------------------------------------------------------
bool UvListRecord::hasLayer(int iLayerIndex) const
{
    return mAttributeMask & (0x1 << iLayerIndex);
}

//-------------------------------------------------------------------------
bool UvListRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    ok &= readInt32(iRawRecord, mAttributeMask);
    
    // read uv list for each layer
    vector<int> layerIndicesToRead;
    for(int i = 0; i < 7; ++i)
    {
        if(hasLayer(i))
        {
            layerIndicesToRead.push_back(i);
        }
    }
    
    // for each vertex, read UV from each layer
    // in use.
    //
    const int numVertices = (mRecordLenght - 8) / (8 * layerIndicesToRead.size());
    for(int i = 0; i < numVertices; ++i)
    {
        for(int j = 0; j < layerIndicesToRead.size(); ++j)
        {
            const int layerIndex = layerIndicesToRead[j];
            
            float value = 0.0;
            ok &= readFloat32(iRawRecord, value);
            mUCoordinates[layerIndex].push_back(value);
            
            ok &= readFloat32(iRawRecord, value);
            mVCoordinates[layerIndex].push_back(value);
        }
    }
    
    
    return ok;
}