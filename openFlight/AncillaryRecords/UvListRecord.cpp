
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
    
    if (iLayerIndex >= 0 && iLayerIndex < 8)
    {
        const vector<float> &u = mUCoordinates[iLayerIndex];
        const vector<float> &v = mVCoordinates[iLayerIndex];

        // we assume both vector have same size...
        if (iVertexIndex >= 0 && iVertexIndex < (int)u.size())
        {
            r.mX = u[iVertexIndex];
            r.mY = v[iVertexIndex];
        }
    }
    
    return r;
}

//-------------------------------------------------------------------------
bool UvListRecord::hasLayers() const
{
    //keep only first 7 bits (counting from the left side... see doc)
    const int t = mAttributeMask & 0xFF000000;
    
    return t != 0;
}

//-------------------------------------------------------------------------
bool UvListRecord::hasLayer(int iLayerIndex) const
{
    // masked bits starts on the left.... so 31 - iLayerIndex
    //
    return mAttributeMask & (0x1 << (31 - iLayerIndex));
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