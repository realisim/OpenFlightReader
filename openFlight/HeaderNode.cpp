
#include "HeaderNode.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace OpenFlight;
using namespace std;

//-------------------------------------------------------------------------
//--- HeaderNode
//-------------------------------------------------------------------------
HeaderNode::HeaderNode()
{}

//-------------------------------------------------------------------------
HeaderNode::~HeaderNode()
{}

//------------------------------------------------------------------------------
string HeaderNode::getAsciiId() const
{ return mAsciiId;}

//------------------------------------------------------------------------------
string HeaderNode::getDateAntTimeOfLastRevision() const
{ return mDateAntTimeOfLastRevision;}

//------------------------------------------------------------------------------
HeaderNode::databaseOrigin HeaderNode::getDatabaseOrigin() const
{ return mDatabaseOrigin;}

//------------------------------------------------------------------------------
double HeaderNode::getDeltaX() const
{ return mDeltaX;}

//------------------------------------------------------------------------------
double HeaderNode::getDeltaY() const
{ return mDeltaY;}

//------------------------------------------------------------------------------
double HeaderNode::getDeltaZ() const
{ return mDeltaZ;}

//------------------------------------------------------------------------------
HeaderNode::earthEllipsoidModel HeaderNode::getEarthEllipsoidModel() const
{ return mEarthEllipsoidModel;}

//------------------------------------------------------------------------------
double HeaderNode::getEarthMajorAxis() const
{ return mEarthMajorAxis;}

//------------------------------------------------------------------------------
double HeaderNode::getEarthMinorAxis() const
{ return mEarthMinorAxis;}

//------------------------------------------------------------------------------
int HeaderNode::getEditRevision() const
{ return mEditRevision;}

//------------------------------------------------------------------------------
int HeaderNode::getFlags() const
{ return mFlags;}

//------------------------------------------------------------------------------
int HeaderNode::getFormatRevision() const
{ return mFormatRevision;}

//------------------------------------------------------------------------------
double HeaderNode::getLambertLowerLatitude() const
{ return mLambertLowerLatitude;}

//------------------------------------------------------------------------------
double HeaderNode::getLambertUpperLatitude() const
{ return mLambertUpperLatitude;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextAdaptiveNodeId() const
{ return mNextAdaptiveNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextBspNodeId() const
{ return mNextBspNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextCatNodeId() const
{ return mNextCatNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextClipNodeId() const
{ return mNextClipNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextCurveNodeId() const
{ return mNextCurveNodeId;}

//------------------------------------------------------------------------------
int16_t HeaderNode::getNextDofNodeId() const
{ return mNextDofNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextFaceNodeId() const
{ return mNextFaceNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextGroupNodeId() const
{ return mNextGroupNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextLightPointNodeId() const
{ return mNextLightPointNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextLightPointSystemId() const
{ return mNextLightPointSystemId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextLightSourceNodeId() const
{ return mNextLightSourceNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextLodNodeId() const
{ return mNextLodNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextMeshNodeId() const
{ return mNextMeshNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextObjectNodeId() const
{ return mNextObjectNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextPathNodeId() const
{ return mNextPathNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextRoadNodeId() const
{ return mNextRoadNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextSoundNodeId() const
{ return mNextSoundNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextSwitchNodeId() const
{ return mNextSwitchNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getNextTextNodeId() const
{ return mNextTextNodeId;}

//------------------------------------------------------------------------------
double HeaderNode::getNorthEastCornerLatitude() const
{ return mNorthEastCornerLatitude;}

//------------------------------------------------------------------------------
double HeaderNode::getNorthEastCornerLongitude() const
{ return mNorthEastCornerLongitude;}

//------------------------------------------------------------------------------
double HeaderNode::getOriginLatitude() const
{ return mOriginLatitude;}

//------------------------------------------------------------------------------
double HeaderNode::getOriginLongitude() const
{ return mOriginLongitude;}

//------------------------------------------------------------------------------
HeaderNode::projectionType HeaderNode::getProjection() const
{ return mProjection;}

//------------------------------------------------------------------------------
double HeaderNode::getRadius() const
{ return mRadius;}

//------------------------------------------------------------------------------
bool HeaderNode::getShouldSetWhiteTextureOnNewFace() const
{ return mShouldSetWhiteTextureOnNewFace; }

//------------------------------------------------------------------------------
double HeaderNode::getSouthWestCornerLatitude() const
{ return mSouthWestCornerLatitude;}

//------------------------------------------------------------------------------
double HeaderNode::getSouthWestCornerLongitude() const
{ return mSouthWestCornerLongitude;}

//------------------------------------------------------------------------------
double HeaderNode::getSouthWestDbCoordinateX() const
{ return mSouthWestDbCoordinateX;}

//------------------------------------------------------------------------------
double HeaderNode::getSouthWestDbCoordinateY() const
{ return mSouthWestDbCoordinateY;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getUnitMultiplier() const
{ return mUnitMultiplier;}

//------------------------------------------------------------------------------
int16_t HeaderNode::getUtmZone() const
{ return mUtmZone;}

//------------------------------------------------------------------------------
HeaderNode::vertexCoordinateUnits HeaderNode::getVertexCoordinateUnits() const
{ return mVertexCoordinateUnits;}

//------------------------------------------------------------------------------
uint16_t HeaderNode::getVertexStorageType() const
{ return mVertexStorageType;}

//-------------------------------------------------------------------------
void HeaderNode::parseRecord(int iRecordSize, char* iRawRecord)
{
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( string( iRawRecord, iRecordSize ) );

    // Lets move by 4 to skip the opCode and recordLenght... we already know
    // we have a valid record at this point.
    //
    iss.seekg(4);

    uint8_t dummyUint8;
    int32_t dummyInt32;

    bool ok = true;    
    ok &= readChar(iss, 8, mAsciiId);
    ok &= readInt32(iss, mFormatRevision);

    //Switch to read the right format.

    ok &= readInt32(iss, mEditRevision);
    ok &= readChar(iss, 32, mDateAntTimeOfLastRevision );
    ok &= readUint16(iss, mNextGroupNodeId);
    ok &= readUint16(iss, mNextLodNodeId);
    ok &= readUint16(iss, mNextObjectNodeId);
    ok &= readUint16(iss, mNextFaceNodeId);
    ok &= readUint16(iss, mUnitMultiplier);
    ok &= readUint8(iss, dummyUint8); mVertexCoordinateUnits = (vertexCoordinateUnits)dummyUint8;
    ok &= readUint8(iss, dummyUint8); mShouldSetWhiteTextureOnNewFace = dummyUint8 != 0;
    //reserved
    iss.seekg(92);
    ok &= readInt32(iss, dummyInt32); mProjection = (projectionType)dummyInt32;
    //reserved
    iss.seekg(124);
    ok &= readUint16(iss, mNextDofNodeId);
    ok &= readUint16(iss, mVertexStorageType);
    ok &= readInt32(iss, dummyInt32); mDatabaseOrigin = (databaseOrigin)dummyInt32;
    ok &= readDouble(iss, mSouthWestDbCoordinateX);
    ok &= readDouble(iss, mSouthWestDbCoordinateY);
    ok &= readDouble(iss, mDeltaX);
    ok &= readDouble(iss, mDeltaY);
    ok &= readUint16(iss, mNextSoundNodeId);
    ok &= readUint16(iss, mNextPathNodeId);
    //reserved
    iss.seekg(176);
    ok &= readUint16(iss, mNextClipNodeId);
    ok &= readUint16(iss, mNextTextNodeId);
    ok &= readUint16(iss, mNextBspNodeId);
    ok &= readUint16(iss, mNextSwitchNodeId);
    //reserved
    iss.seekg(188);
    ok &= readDouble(iss, mSouthWestCornerLatitude);
    ok &= readDouble(iss, mSouthWestCornerLongitude);
    ok &= readDouble(iss, mNorthEastCornerLatitude);
    ok &= readDouble(iss, mNorthEastCornerLongitude);
    ok &= readDouble(iss, mOriginLatitude);
    ok &= readDouble(iss, mOriginLongitude);
    ok &= readDouble(iss, mLambertUpperLatitude);
    ok &= readDouble(iss, mLambertLowerLatitude);
    ok &= readUint16(iss, mNextLightSourceNodeId);
    ok &= readUint16(iss, mNextLightPointNodeId);
    ok &= readUint16(iss, mNextRoadNodeId);
    ok &= readUint16(iss, mNextCatNodeId);
    //reserved
    iss.seekg(268);
    ok &= readInt32(iss, dummyInt32); mEarthEllipsoidModel = (earthEllipsoidModel)dummyInt32;
    ok &= readUint16(iss, mNextAdaptiveNodeId);
    ok &= readUint16(iss, mNextCurveNodeId);
    ok &= readInt16(iss, mUtmZone);
    //reserved
    iss.seekg(284);
    ok &= readDouble(iss, mDeltaZ);
    ok &= readDouble(iss, mRadius);
    ok &= readUint16(iss, mNextMeshNodeId);
    ok &= readUint16(iss, mNextLightPointSystemId);
    //reserved
    iss.seekg(308);
    ok &= readDouble(iss, mEarthMajorAxis);
    ok &= readDouble(iss, mEarthMinorAxis);
}
