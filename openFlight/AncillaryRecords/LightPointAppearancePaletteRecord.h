
#pragma once

#include "AncillaryRecord.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class OFR_API LightPointAppearancePaletteRecord : public AncillaryRecord
    {
    public:
        LightPointAppearancePaletteRecord() = delete;
        explicit LightPointAppearancePaletteRecord(PrimaryRecord* ipParent);
        LightPointAppearancePaletteRecord(const LightPointAppearancePaletteRecord&) = delete;
        LightPointAppearancePaletteRecord& operator=(const LightPointAppearancePaletteRecord&) = delete;
        virtual ~LightPointAppearancePaletteRecord();

        enum DisplayMode {dmRaster = 0, dmCalligraphic, dmEither};
        enum Directionality {dOmnidirectional = 0, dUnidirectional, dBidirectional};
        enum FadingMode {fmEnabled, fmDisabled};
        enum FogPunchMode {fpmEnabled, fpmDisabled};
        enum DirectionalMode {dmEnabled, dmDisabled};
        enum RangeMode {rmUseZBuffer, rmUseSlantRange};

        float getActualSize() const;
        uint32_t getBackColorForBidirectionalPoints() const;
        float getBackIntensity() const;
        //float getDirectionalAmbientIntensity() const;
        //float getDirectionalFalloffExponent() const;
        //DirectionalMode getDirectionalMode() const;
        Directionality getDirectionality() const;
        //DisplayMode getDisplayMode() const;
        //float getFadeInDuration() const;
        //float getFadeOutDuration() const;
        //float getFadeRangeRatio() const;
        //int32_t getFadingMode() const;
        uint16_t getFeatureId() const;
        //int32_t getFlags() const;
        //float getFogIntensity() const;
        //int32_t getFogPunchMode() const;
        //float getFogScalar() const;
        //float getHorizontalLobeAngle() const;
        int32_t getIndex() const;
        float getIntensity() const;
        //float getLobeRollAngle() const;
        //float getLodRangeRation() const;
        //float getLodScale() const;
        float getMaxPixelSize() const;
        float getMinPixelSize() const;
        std::string getName() const;
        //int32_t getRangeMode() const;
        //float getSignificance() const;
        //float getSizeDifferenceThreshold() const;
        uint16_t getSurfaceMaterialCode() const;
        //int32_t getTexturePatternIndex() const;
        //float getTransparentFalloffClamp() const;
        //float getTransparentFalloffExponent() const;
        //float getTransparentFalloffScalar() const;
        //float getVerticalLobeAngle() const;
        //float getVisibilityRange() const;


// Setters
// void setActualSize(float);
// void setBackColorForBidirectionalPoints(uint32_t);
// void setDirectionalAmbientIntensity(float);
// void setDirectionalFalloffExponent(float);
// void setDirectionalMode(int32_t);
// void setDirectionality(int32_t);
// void setDisplayMode(int32_t);
// void setFadeInDuration(float);
// void setFadeOutDuration(float);
// void setFadeRangeRatio(float);
// void setFadingMode(int32_t);
// void setFeatureId(uint16_t);
// void setFlags(int32_t);
// void setFogIntensity(float);
// void setFogPunchMode(int32_t);
// void setFogScalar(float);
// void setHorizontalLobeAngle(float);
// void setIndex(int32_t);
// void setIntensity(float);
// void setLobeRollAngle(float);
// void setLodRangeRation(float);
// void setLodScale(float);
// void setMaxPixelSize(float);
// void setMinPixelSize(float);
// void setName(std::string);
// void setRangeMode(int32_t);
// void setSignificance(float);
// void setSizeDifferenceThreshold(float);
// void setSurfaceMaterialCode(uint16_t);
// void setTexturePatternIndex(int32_t);
// void setTransparentFalloffClamp(float);
// void setTransparentFalloffExponent(float);
// void setTransparentFalloffScalar(float);
// void setVerticalLobeAngle(float);
// void setVisibilityRange(float);


    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

// Most of the parameters are commented because we consider them
// obsolete...
//
        std::string mName;
        int32_t mIndex;
        uint16_t mSurfaceMaterialCode;
        uint16_t mFeatureId;
        uint32_t mBackColorForBidirectionalPoints;
        //DisplayMode mDisplayMode;
        float mIntensity;
        float mBackIntensity;
        //FadingMode mFadingMode;
        //FogPunchMode mFogPunchMode;
        //DirectionalMode mDirectionalMode;
        //RangeMode mRangeMode;
        float mMinPixelSize;
        float mMaxPixelSize;
        float mActualSize; // in db units
//        float mTransparentFalloffExponent;
//        float mTransparentFalloffScalar;
//        float mTransparentFalloffClamp;
//        float mFogScalar;
//        float mFogIntensity;
//        float mSizeDifferenceThreshold;
        Directionality mDirectionality;
//        float mHorizontalLobeAngle;
//        float mVerticalLobeAngle;
//        float mLobeRollAngle;
//        float mDirectionalFalloffExponent;
//        float mDirectionalAmbientIntensity;
//        float mSignificance;
//        int32_t mFlags;
//        float mVisibilityRange;
//        float mFadeRangeRatio;
//        float mFadeInDuration; // in seconds
//        float mFadeOutDuration; // in seconds
//        float mLodRangeRation;
//        float mLodScale;
//        int32_t mTexturePatternIndex;
    };

}