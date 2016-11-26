
#include "HeaderRecord.h"
#include "AncillaryRecords/PaletteRecords.h"
#include "AncillaryRecords/TexturePaletteRecord.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace OpenFlight;
using namespace std;

//-------------------------------------------------------------------------
//--- HeaderRecord
//-------------------------------------------------------------------------
HeaderRecord::HeaderRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("n/a"),
mFormatRevision(0),
mEditRevision(0),
mDateAntTimeOfLastRevision("n/a"),
mNextGroupNodeId(0),
mNextLodNodeId(0),
mNextObjectNodeId(0),
mNextFaceNodeId(0),
mUnitMultiplier(0),
mVertexCoordinateUnits(vcuMeters),
mShouldSetWhiteTextureOnNewFace(0),
mFlags(0),
mProjection(ptFlatEarth),
mNextDofNodeId(0),
mVertexStorageType(1),
mDatabaseOrigin(doOpenFlight),
mSouthWestDbCoordinateX(0.0),
mSouthWestDbCoordinateY(0.0),
mDeltaX(0.0),
mDeltaY(0.0),
mNextSoundNodeId(0),
mNextPathNodeId(0),
mNextClipNodeId(0),
mNextTextNodeId(0),
mNextBspNodeId(0),
mNextSwitchNodeId(0),
mSouthWestCornerLatitude(0.0),
mSouthWestCornerLongitude(0.0),
mNorthEastCornerLatitude(0.0),
mNorthEastCornerLongitude(0.0),
mOriginLatitude(0.0),
mOriginLongitude(0.0),
mLambertUpperLatitude(0.0),
mLambertLowerLatitude(0.0),
mNextLightSourceNodeId(0),
mNextLightPointNodeId(0),
mNextRoadNodeId(0),
mNextCatNodeId(0),
mEarthEllipsoidModel(eemBessel),
mNextAdaptiveNodeId(0),
mNextCurveNodeId(0),
mUtmZone(0),
mDeltaZ(0.0),
mRadius(0.0),
mNextMeshNodeId(0),
mNextLightPointSystemId(0),
mEarthMajorAxis(0.0),
mEarthMinorAxis(0.0),
mpColorPalette(nullptr),
mpLightSourcePalette(nullptr),
mMaterialPalettes(),
mpVertexPalette(nullptr),
mpTexturePalette(nullptr)
{}

//-------------------------------------------------------------------------
HeaderRecord::~HeaderRecord()
{
    mpColorPalette = nullptr;
    mpLightSourcePalette = nullptr;
    mMaterialPalettes.clear();
    mpVertexPalette = nullptr;
}

//------------------------------------------------------------------------------
string HeaderRecord::getAsciiId() const
{ return mAsciiId;}

//------------------------------------------------------------------------------
string HeaderRecord::getDateAntTimeOfLastRevision() const
{ return mDateAntTimeOfLastRevision;}

//------------------------------------------------------------------------------
HeaderRecord::databaseOrigin HeaderRecord::getDatabaseOrigin() const
{ return mDatabaseOrigin;}

//------------------------------------------------------------------------------
double HeaderRecord::getDeltaX() const
{ return mDeltaX;}

//------------------------------------------------------------------------------
double HeaderRecord::getDeltaY() const
{ return mDeltaY;}

//------------------------------------------------------------------------------
double HeaderRecord::getDeltaZ() const
{ return mDeltaZ;}

//------------------------------------------------------------------------------
HeaderRecord::earthEllipsoidModel HeaderRecord::getEarthEllipsoidModel() const
{ return mEarthEllipsoidModel;}

//------------------------------------------------------------------------------
double HeaderRecord::getEarthMajorAxis() const
{ return mEarthMajorAxis;}

//------------------------------------------------------------------------------
double HeaderRecord::getEarthMinorAxis() const
{ return mEarthMinorAxis;}

//------------------------------------------------------------------------------
int HeaderRecord::getEditRevision() const
{ return mEditRevision;}

//------------------------------------------------------------------------------
int HeaderRecord::getFlags() const
{ return mFlags;}

//------------------------------------------------------------------------------
int HeaderRecord::getFormatRevision() const
{ return mFormatRevision;}

//------------------------------------------------------------------------------
double HeaderRecord::getLambertLowerLatitude() const
{ return mLambertLowerLatitude;}

//------------------------------------------------------------------------------
double HeaderRecord::getLambertUpperLatitude() const
{ return mLambertUpperLatitude;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextAdaptiveNodeId() const
{ return mNextAdaptiveNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextBspNodeId() const
{ return mNextBspNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextCatNodeId() const
{ return mNextCatNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextClipNodeId() const
{ return mNextClipNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextCurveNodeId() const
{ return mNextCurveNodeId;}

//------------------------------------------------------------------------------
int16_t HeaderRecord::getNextDofNodeId() const
{ return mNextDofNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextFaceNodeId() const
{ return mNextFaceNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextGroupNodeId() const
{ return mNextGroupNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextLightPointNodeId() const
{ return mNextLightPointNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextLightPointSystemId() const
{ return mNextLightPointSystemId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextLightSourceNodeId() const
{ return mNextLightSourceNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextLodNodeId() const
{ return mNextLodNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextMeshNodeId() const
{ return mNextMeshNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextObjectNodeId() const
{ return mNextObjectNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextPathNodeId() const
{ return mNextPathNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextRoadNodeId() const
{ return mNextRoadNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextSoundNodeId() const
{ return mNextSoundNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextSwitchNodeId() const
{ return mNextSwitchNodeId;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getNextTextNodeId() const
{ return mNextTextNodeId;}

//------------------------------------------------------------------------------
double HeaderRecord::getNorthEastCornerLatitude() const
{ return mNorthEastCornerLatitude;}

//------------------------------------------------------------------------------
double HeaderRecord::getNorthEastCornerLongitude() const
{ return mNorthEastCornerLongitude;}

//------------------------------------------------------------------------------
double HeaderRecord::getOriginLatitude() const
{ return mOriginLatitude;}

//------------------------------------------------------------------------------
double HeaderRecord::getOriginLongitude() const
{ return mOriginLongitude;}

//------------------------------------------------------------------------------
HeaderRecord::projectionType HeaderRecord::getProjection() const
{ return mProjection;}

//------------------------------------------------------------------------------
double HeaderRecord::getRadius() const
{ return mRadius;}

//------------------------------------------------------------------------------
bool HeaderRecord::getShouldSetWhiteTextureOnNewFace() const
{ return mShouldSetWhiteTextureOnNewFace; }

//------------------------------------------------------------------------------
double HeaderRecord::getSouthWestCornerLatitude() const
{ return mSouthWestCornerLatitude;}

//------------------------------------------------------------------------------
double HeaderRecord::getSouthWestCornerLongitude() const
{ return mSouthWestCornerLongitude;}

//------------------------------------------------------------------------------
double HeaderRecord::getSouthWestDbCoordinateX() const
{ return mSouthWestDbCoordinateX;}

//------------------------------------------------------------------------------
double HeaderRecord::getSouthWestDbCoordinateY() const
{ return mSouthWestDbCoordinateY;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getUnitMultiplier() const
{ return mUnitMultiplier;}

//------------------------------------------------------------------------------
int16_t HeaderRecord::getUtmZone() const
{ return mUtmZone;}

//------------------------------------------------------------------------------
VertexPaletteRecord* HeaderRecord::getVertexPalette()
{ return mpVertexPalette;}

//------------------------------------------------------------------------------
HeaderRecord::vertexCoordinateUnits HeaderRecord::getVertexCoordinateUnits() const
{ return mVertexCoordinateUnits;}

//------------------------------------------------------------------------------
uint16_t HeaderRecord::getVertexStorageType() const
{ return mVertexStorageType;}

//-------------------------------------------------------------------------
// Explain...
void HeaderRecord::handleAddedAncillaryRecord(Record* ipAncillary)
{
    switch (ipAncillary->getOpCode())
    {
        case ocColorPalette: mpColorPalette = (ColorPaletteRecord*)ipAncillary; break;
        case ocLightSourcePalette: mpLightSourcePalette = (LightSourcePaletteRecord*)ipAncillary; break;
        case ocMaterialPalette: mMaterialPalettes.push_back( (MaterialPaletteRecord*)ipAncillary ); break;
        case ocVertexPalette: mpVertexPalette = (VertexPaletteRecord*)ipAncillary; break;
        case ocTexturePalette: mpTexturePalette = (TexturePaletteRecord*)ipAncillary; break;
        default: break;
    }
}

//-------------------------------------------------------------------------
bool HeaderRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    // Lets move by 4 to skip the opCode and recordLenght... we already know
    // we have a valid record at this point.
    //
    iss.seekg(4);

    uint8_t dummyUint8;
    int16_t dummyInt16;
    int32_t dummyInt32;

    bool ok = true;    
    ok &= readChar(iss, 8, mAsciiId);
    ok &= readInt32(iss, mFormatRevision);
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
  
    if(ok && mFormatRevision >= 1580)
    { ok &= readInt16(iss, mUtmZone); }
    else{ readInt16(iss, dummyInt16); }
  
    //reserved
    iss.seekg(284);
  
    if(ok && mFormatRevision >= 1570)
    {
      ok &= readDouble(iss, mDeltaZ);
      ok &= readDouble(iss, mRadius);
      ok &= readUint16(iss, mNextMeshNodeId);
    }
  
    if(ok && mFormatRevision >= 1580)
    {
      ok &= readUint16(iss, mNextLightPointSystemId);
      //reserved
      iss.seekg(308);
      ok &= readDouble(iss, mEarthMajorAxis);
      ok &= readDouble(iss, mEarthMinorAxis);
    }
    
    return ok;
}