

#include "HeaderRecord.h"
#include "AncillaryRecords/CommentRecord.h"
#include "AncillaryRecords/LightPointAnimationPaletteRecord.h"
#include "AncillaryRecords/LightPointAppearancePaletteRecord.h"
#include "AncillaryRecords/PaletteRecords.h"
#include "AncillaryRecords/TexturePaletteRecord.h"
#include <fstream>
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
mLightPointAppearancePalettes(),
mLightPointAnimationPalettes(),
mpVertexPalette(nullptr),
mTexturePalettes(),
mComments()
{}

//-------------------------------------------------------------------------
HeaderRecord::~HeaderRecord()
{
    mpColorPalette = nullptr;
    mpLightSourcePalette = nullptr;
    mMaterialPalettes.clear();
    mLightPointAppearancePalettes.clear();
    mLightPointAnimationPalettes.clear();
    mpVertexPalette = nullptr;
    mTexturePalettes.clear();
    mComments.clear();
}

//------------------------------------------------------------------------------
MaterialPaletteRecord* HeaderRecord::findMaterialPaletteByMaterialIndex(int iIndex)
{
    MaterialPaletteRecord *r = nullptr;
    for (size_t i = 0; i < mMaterialPalettes.size() && !r; ++i )
    {
        if(mMaterialPalettes[i]->getIndex() == iIndex)
        { r =  mMaterialPalettes[i]; }
    }
    return r;
}

//------------------------------------------------------------------------------
TexturePaletteRecord* HeaderRecord::findTexturePaletteByTexturePatternIndex(int iIndex)
{
    TexturePaletteRecord *r = nullptr;
    for (size_t i = 0; i < mTexturePalettes.size() && !r; ++i )
    {
        if(mTexturePalettes[i]->getTexturePatternIndex() == iIndex)
        { r =  mTexturePalettes[i]; }
    }
    return r;
}

//------------------------------------------------------------------------------
string HeaderRecord::getAsciiId() const
{ return mAsciiId;}

//------------------------------------------------------------------------------
ColorPaletteRecord* HeaderRecord::getColorPalette()
{
    return mpColorPalette;
}

//------------------------------------------------------------------------------
CommentRecord* HeaderRecord::getCommentRecord(int iIndex) const
{
    CommentRecord *r = nullptr;
    if (iIndex >= 0 && iIndex < (int)mComments.size())
    {
        r = mComments[iIndex];
    }
    return r;
}

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
std::string HeaderRecord::getFilePath() const
{ return mFilePath; }

//------------------------------------------------------------------------------
std::string HeaderRecord::getFilename() const
{ return mFilename; }

//------------------------------------------------------------------------------
std::string HeaderRecord::getFilenamePath() const
{ return mFilenamePath; }

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
LightPointAnimationPaletteRecord* HeaderRecord::getLightPointAnimationPalette(int iIndex) const
{
    LightPointAnimationPaletteRecord *r = nullptr;
    for (size_t i = 0; i < (int)mLightPointAnimationPalettes.size() && r == nullptr; ++i)
    {
        if(iIndex == mLightPointAnimationPalettes[i]->getIndex())
        {
            r = mLightPointAnimationPalettes[i];
        };
    }
    return r;
}

//------------------------------------------------------------------------------
LightPointAppearancePaletteRecord* HeaderRecord::getLightPointAppearancePalette(int iIndex) const
{
    LightPointAppearancePaletteRecord *r = nullptr;
    for (size_t i = 0; i < (int)mLightPointAppearancePalettes.size() && r == nullptr; ++i)
    {
        if(iIndex == mLightPointAppearancePalettes[i]->getIndex())
        {
            r = mLightPointAppearancePalettes[i];
        };
    }
    return r;
}

//------------------------------------------------------------------------------
double HeaderRecord::getLambertUpperLatitude() const
{ return mLambertUpperLatitude;}

//------------------------------------------------------------------------------
MaterialPaletteRecord* HeaderRecord::getMaterialPalette(int iIndex) const
{
    MaterialPaletteRecord *r = nullptr;
    if (iIndex >= 0 && iIndex < (int)mMaterialPalettes.size())
    {
        r = mMaterialPalettes[iIndex];
    }
    return r;
}

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
int HeaderRecord::getNumberOfComments() const
{ return (int)mComments.size();  }

//------------------------------------------------------------------------------
int HeaderRecord::getNumberOfLightPointAnimationPalettes() const
{ return (int)mLightPointAnimationPalettes.size(); }

//------------------------------------------------------------------------------
int HeaderRecord::getNumberOfLightPointAppearancePalettes() const
{ return (int)mLightPointAppearancePalettes.size(); }

//------------------------------------------------------------------------------
int HeaderRecord::getNumberOfMaterialPalettes() const
{ return (int)mMaterialPalettes.size(); }

//------------------------------------------------------------------------------
int HeaderRecord::getNumberOfTexturePalettes() const
{ return (int)mTexturePalettes.size(); }

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
TexturePaletteRecord* HeaderRecord::getTexturePalette(int iIndex) const
{
    TexturePaletteRecord* r = nullptr;
    if (iIndex >= 0 && iIndex < getNumberOfTexturePalettes())
    {
        r = mTexturePalettes[iIndex];
    }
    return r;
}

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
void HeaderRecord::handleAddedAncillaryRecord(AncillaryRecord* ipAncillary)
{
    switch (ipAncillary->getOpCode())
    {
        case ocColorPalette: mpColorPalette = (ColorPaletteRecord*)ipAncillary; break;
        case ocLightSourcePalette: mpLightSourcePalette = (LightSourcePaletteRecord*)ipAncillary; break;
        case ocMaterialPalette: mMaterialPalettes.push_back( (MaterialPaletteRecord*)ipAncillary ); break;
        case ocLightPointAppearancePalette: mLightPointAppearancePalettes.push_back( (LightPointAppearancePaletteRecord*)ipAncillary ); break;
        case ocLightPointAnimationPalette: mLightPointAnimationPalettes.push_back( (LightPointAnimationPaletteRecord*)ipAncillary ); break;
        case ocVertexPalette: mpVertexPalette = (VertexPaletteRecord*)ipAncillary; break;
        case ocTexturePalette: mTexturePalettes.push_back((TexturePaletteRecord*)ipAncillary); break;
        default: break;
    }
}

//-------------------------------------------------------------------------
bool HeaderRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);

    uint8_t dummyUint8;
    int16_t dummyInt16;
    int32_t dummyInt32;

    bool ok = true;    
    ok &= readChar(iRawRecord, 8, mAsciiId);
    ok &= readInt32(iRawRecord, mFormatRevision);
    ok &= readInt32(iRawRecord, mEditRevision);
    ok &= readChar(iRawRecord, 32, mDateAntTimeOfLastRevision );
    ok &= readUint16(iRawRecord, mNextGroupNodeId);
    ok &= readUint16(iRawRecord, mNextLodNodeId);
    ok &= readUint16(iRawRecord, mNextObjectNodeId);
    ok &= readUint16(iRawRecord, mNextFaceNodeId);
    ok &= readUint16(iRawRecord, mUnitMultiplier);
    ok &= readUint8(iRawRecord, dummyUint8); mVertexCoordinateUnits = (vertexCoordinateUnits)dummyUint8;
    ok &= readUint8(iRawRecord, dummyUint8); mShouldSetWhiteTextureOnNewFace = dummyUint8 != 0;
    ok &= readInt32(iRawRecord, mFlags);
    //reserved
    iRawRecord.seekg(startPos + 92);
    ok &= readInt32(iRawRecord, dummyInt32); mProjection = (projectionType)dummyInt32;
    //reserved
    iRawRecord.seekg(startPos + 124);
    ok &= readUint16(iRawRecord, mNextDofNodeId);
    ok &= readUint16(iRawRecord, mVertexStorageType);
    ok &= readInt32(iRawRecord, dummyInt32); mDatabaseOrigin = (databaseOrigin)dummyInt32;
    ok &= readDouble(iRawRecord, mSouthWestDbCoordinateX);
    ok &= readDouble(iRawRecord, mSouthWestDbCoordinateY);
    ok &= readDouble(iRawRecord, mDeltaX);
    ok &= readDouble(iRawRecord, mDeltaY);
    ok &= readUint16(iRawRecord, mNextSoundNodeId);
    ok &= readUint16(iRawRecord, mNextPathNodeId);
    //reserved
    iRawRecord.seekg(startPos + 176);
    ok &= readUint16(iRawRecord, mNextClipNodeId);
    ok &= readUint16(iRawRecord, mNextTextNodeId);
    ok &= readUint16(iRawRecord, mNextBspNodeId);
    ok &= readUint16(iRawRecord, mNextSwitchNodeId);
    //reserved
    iRawRecord.seekg(startPos + 188);
    ok &= readDouble(iRawRecord, mSouthWestCornerLatitude);
    ok &= readDouble(iRawRecord, mSouthWestCornerLongitude);
    ok &= readDouble(iRawRecord, mNorthEastCornerLatitude);
    ok &= readDouble(iRawRecord, mNorthEastCornerLongitude);
    ok &= readDouble(iRawRecord, mOriginLatitude);
    ok &= readDouble(iRawRecord, mOriginLongitude);
    ok &= readDouble(iRawRecord, mLambertUpperLatitude);
    ok &= readDouble(iRawRecord, mLambertLowerLatitude);
    ok &= readUint16(iRawRecord, mNextLightSourceNodeId);
    ok &= readUint16(iRawRecord, mNextLightPointNodeId);
    ok &= readUint16(iRawRecord, mNextRoadNodeId);
    ok &= readUint16(iRawRecord, mNextCatNodeId);
    //reserved
    iRawRecord.seekg(startPos + 268);
    ok &= readInt32(iRawRecord, dummyInt32); mEarthEllipsoidModel = (earthEllipsoidModel)dummyInt32;
    ok &= readUint16(iRawRecord, mNextAdaptiveNodeId);
    ok &= readUint16(iRawRecord, mNextCurveNodeId);
  
    if(ok && mFormatRevision >= 1580)
    { ok &= readInt16(iRawRecord, mUtmZone); }
    else{ readInt16(iRawRecord, dummyInt16); }
  
    //reserved
    iRawRecord.seekg(startPos + 284);
  
    if(ok && mFormatRevision >= 1570)
    {
      ok &= readDouble(iRawRecord, mDeltaZ);
      ok &= readDouble(iRawRecord, mRadius);
      ok &= readUint16(iRawRecord, mNextMeshNodeId);
    }
  
    if(ok && mFormatRevision >= 1580)
    {
      ok &= readUint16(iRawRecord, mNextLightPointSystemId);
      //reserved
      iRawRecord.seekg(startPos + 308);
      ok &= readDouble(iRawRecord, mEarthMajorAxis);
      ok &= readDouble(iRawRecord, mEarthMinorAxis);
    }
    
    return ok;
}

//-------------------------------------------------------------------------
void HeaderRecord::setFileInfo(const std::string& iFilenamePath,
                 const std::string& iFilePath,
                 const std::string& iFilename)
{
    mFilenamePath = iFilenamePath;
    mFilePath = iFilePath;
    mFilename = iFilename;
}