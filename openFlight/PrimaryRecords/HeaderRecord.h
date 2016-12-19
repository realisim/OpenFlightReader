
#pragma once

#include "PrimaryRecord.h"
#include <vector>
#include <string>

namespace OpenFlight
{
    class ColorPaletteRecord;
    class LightSourcePaletteRecord;
    class MaterialPaletteRecord;
    class VertexPaletteRecord;
    class TexturePaletteRecord;
    
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class HeaderRecord : public PrimaryRecord
    {
    public:
        HeaderRecord() = delete;
        explicit HeaderRecord(PrimaryRecord* ipParent);
        HeaderRecord(const HeaderRecord&) = delete;
        HeaderRecord& operator=(const HeaderRecord&) = delete;
        virtual ~HeaderRecord();

        enum vertexCoordinateUnits { vcuMeters = 0, vcuKilometers = 1, 
            vcuFeet = 4, vcuInches = 5, vcuNauticalMiles = 8 };

        enum projectionType { ptFlatEarth = 0, ptTrapezoidal = 1, ptRoundEarth = 2,
            ptLambert = 3, ptUTM = 4,  ptGeodetic = 5, Geocentric = 6 };

        enum databaseOrigin { doOpenFlight = 100, doDIG_I_DIG_II = 200,
            doEvans_and_Sutherland_CT5A_CT6 = 300, doPSP_DIG = 400,
            doGeneral_Electric_CIV_CV_PT2000 = 600 , doEvans_and_Sutherland_GDF = 700};

        enum earthEllipsoidModel{ eemWgs1984 = 0, eemWgs1972 = 1, eemBessel = 2,
            eemClarke1866 = 3, eemNad1927 = 4, eemUserDefined = -1 };
        
        std::string getAsciiId() const;
        std::string getDateAntTimeOfLastRevision() const;
        databaseOrigin getDatabaseOrigin() const;
        double getDeltaX() const;
        double getDeltaY() const;
        double getDeltaZ() const;
        earthEllipsoidModel getEarthEllipsoidModel() const;
        double getEarthMajorAxis() const;
        double getEarthMinorAxis() const;
        int getEditRevision() const;
        std::string getFilePath() const;
        std::string getFilename() const;
        std::string getFilenamePath() const;
        int getFlags() const;
        int getFormatRevision() const;
        double getLambertLowerLatitude() const;
        double getLambertUpperLatitude() const;
        uint16_t getNextAdaptiveNodeId() const;
        uint16_t getNextBspNodeId() const;
        uint16_t getNextCatNodeId() const;
        uint16_t getNextClipNodeId() const;
        uint16_t getNextCurveNodeId() const;
        int16_t getNextDofNodeId() const;
        uint16_t getNextFaceNodeId() const;
        uint16_t getNextGroupNodeId() const;
        uint16_t getNextLightPointNodeId() const;
        uint16_t getNextLightPointSystemId() const;
        uint16_t getNextLightSourceNodeId() const;
        uint16_t getNextLodNodeId() const;
        uint16_t getNextMeshNodeId() const;
        uint16_t getNextObjectNodeId() const;
        uint16_t getNextPathNodeId() const;
        uint16_t getNextRoadNodeId() const;
        uint16_t getNextSoundNodeId() const;
        uint16_t getNextSwitchNodeId() const;
        uint16_t getNextTextNodeId() const;
        double getNorthEastCornerLatitude() const;
        double getNorthEastCornerLongitude() const;
        double getOriginLatitude() const;
        double getOriginLongitude() const;
        projectionType getProjection() const;
        double getRadius() const;
        bool getShouldSetWhiteTextureOnNewFace() const;
        double getSouthWestCornerLatitude() const;
        double getSouthWestCornerLongitude() const;
        double getSouthWestDbCoordinateX() const;
        double getSouthWestDbCoordinateY() const;
        uint16_t getUnitMultiplier() const;
        int16_t getUtmZone() const;
        vertexCoordinateUnits getVertexCoordinateUnits() const;
        VertexPaletteRecord* getVertexPalette();
        uint16_t getVertexStorageType() const;
        

        //setters
        /*void setAsciiId(std::string);
        void setDateAntTimeOfLastRevision(std::string);
        void setDatabaseOrigin(databaseOrigin);
        void setDeltaX(double);
        void setDeltaY(double);
        void setDeltaZ(double);
        void setEarthEllipsoidModel(EarthEllipsoidModel);
        void setEarthMajorAxis(double);
        void setEarthMinorAxis(double);
        void setEditRevision(int);
        void setFlags(int);
        void setFormatRevision(int);
        void setLambertLowerLatitude(double);
        void setLambertUpperLatitude(double);
        void setNextAdaptiveNodeId(uint16_t);
        void setNextBspNodeId(uint16_t);
        void setNextCatNodeId(uint16_t);
        void setNextClipNodeId(uint16_t);
        void setNextCurveNodeId(uint16_t);
        void setNextDofNodeId(int16_t);
        void setNextFaceNodeId(uint16_t);
        void setNextGroupNodeId(uint16_t);
        void setNextLightPointNodeId(uint16_t);
        void setNextLightPointSystemId(uint16_t);
        void setNextLightSourceNodeId(uint16_t);
        void setNextLodNodeId(uint16_t);
        void setNextMeshNodeId(uint16_t);
        void setNextObjectNodeId(uint16_t);
        void setNextPathNodeId(uint16_t);
        void setNextRoadNodeId(uint16_t);
        void setNextSoundNodeId(uint16_t);
        void setNextSwitchNodeId(uint16_t);
        void setNextTextNodeId(uint16_t);
        void setNorthEastCornerLatitude(double);
        void setNorthEastCornerLongitude(double);
        void setOriginLatitude(double);
        void setOriginLongitude(double);
        void setProjection(projectionType);
        void setRadius(double);
        void setShouldSetWhiteTextureOnNewFace(bool);
        void setSouthWestCornerLatitude(double);
        void setSouthWestCornerLongitude(double);
        void setSouthWestDbCoordinateX(double);
        void setSouthWestDbCoordinateY(double);
        void setUnitMultiplier(uint16_t);
        void setUtmZone(int16_t);
        void setVertexCoordinateUnits(vertexCoordinateUnits);
        void setVertexStorageType(uint16_t);*/

    protected:
        friend class OpenFlightReader;
        
        virtual void handleAddedAncillaryRecord(Record*) override;
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) override;
        void setFileInfo(const std::string& iFilenamePath, const std::string& iFilePath, const std::string& iFilename);
        
        std::string mAsciiId;
        int mFormatRevision;
        int mEditRevision;
        std::string mDateAntTimeOfLastRevision;
        uint16_t mNextGroupNodeId;
        uint16_t mNextLodNodeId;
        uint16_t mNextObjectNodeId;
        uint16_t mNextFaceNodeId;
        uint16_t mUnitMultiplier; //always 1
        vertexCoordinateUnits mVertexCoordinateUnits;
        bool mShouldSetWhiteTextureOnNewFace;
        int mFlags;
        projectionType mProjection;
        uint16_t mNextDofNodeId;
        uint16_t mVertexStorageType; //should always be 1 - Double precision float
        databaseOrigin mDatabaseOrigin;
        double mSouthWestDbCoordinateX;
        double mSouthWestDbCoordinateY;
        double mDeltaX;
        double mDeltaY;
        uint16_t mNextSoundNodeId;
        uint16_t mNextPathNodeId;
        uint16_t mNextClipNodeId;
        uint16_t mNextTextNodeId;
        uint16_t mNextBspNodeId;
        uint16_t mNextSwitchNodeId;
        double mSouthWestCornerLatitude;
        double mSouthWestCornerLongitude;
        double mNorthEastCornerLatitude;
        double mNorthEastCornerLongitude;
        double mOriginLatitude;
        double mOriginLongitude;
        double mLambertUpperLatitude;
        double mLambertLowerLatitude;
        uint16_t mNextLightSourceNodeId;
        uint16_t mNextLightPointNodeId;
        uint16_t mNextRoadNodeId;
        uint16_t mNextCatNodeId;
        earthEllipsoidModel mEarthEllipsoidModel;
        uint16_t mNextAdaptiveNodeId;
        uint16_t mNextCurveNodeId;
        int16_t mUtmZone;
        double mDeltaZ;
        double mRadius;
        uint16_t mNextMeshNodeId;
        uint16_t mNextLightPointSystemId;
        double mEarthMajorAxis; //in meters
        double mEarthMinorAxis; //in meters
        
        // Ancillary Records
        ColorPaletteRecord *mpColorPalette;
        LightSourcePaletteRecord *mpLightSourcePalette;
        std::vector<MaterialPaletteRecord*> mMaterialPalettes;
        VertexPaletteRecord *mpVertexPalette; //owned in PrimaryRecords::mAncillaryRecord ;
        std::vector<TexturePaletteRecord*> mTexturePalettes;
        
        // additionnal data, not part of the binary flt file
        std::string mFilenamePath;
        std::string mFilePath;
        std::string mFilename;
    };

}