
#pragma once

#include "PrimaryRecord.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class OFR_API FaceRecord : public PrimaryRecord
    {
    public:
        FaceRecord() = delete;
        explicit FaceRecord(PrimaryRecord* ipParent);
        FaceRecord(const FaceRecord&) = delete;
        FaceRecord& operator=(const FaceRecord&) = delete;
        virtual ~FaceRecord();

        enum drawType{ dtDrawSolidWithBackfaceCulling = 0, dtDrawSolidNoBackfaceCulling = 1,
            dtDrawWireframeAndClose = 2, dtDrawWireframe = 3, dtSurroundWithWireframeInAlternateColor = 4,
            dtOmnidirectionalLight = 8, dtUniDirectionalLight = 9, dtBidirectionalLight = 10 };

        enum billboardTemplate{ btFixedNoAlphaBlending = 0, btFixedAlphaBlending = 1, 
            btAxialRotateWithAlphaBlending = 2, btPointRotateWithAlphaBlending = 4 };

        enum flag{ fTerrain = 1 << 31, fNoColor = 1 << 30, fNoAlternateColor = 1 << 29,
            fPackedColor = 1 << 28, fTerrainCultureCutout = 1 << 27,
            fHidden = 1 << 26, fRoofLine = 1 << 25 };

        enum lightMode{ lmUseFaceColor=0, lmUseVertexColor, lmUseFaceColorAndNormal, 
            lmUseVertexColorAndNormal };

        uint32_t getAlternateColorIndex() const;
        uint16_t getAlternateColorNameIndex() const;
        Color4ub getAlternatePackedColor() const;
        const std::string& getAsciiId() const;
        billboardTemplate getBillboardTemplate() const;
        uint32_t getColorIndex() const;
        uint16_t getColorNameIndex() const;
        int16_t getDetailTexturePattern() const;
        drawType getDrawType() const;
        int16_t getFeatureId() const;
        int32_t getFlags() const;
        int32_t getIrColorCode() const;
        int32_t getIrMaterialCode() const;
        lightMode getLightMode() const;
        uint8_t getLineStyleIndex() const;
        uint8_t getLodGenerationControl() const;
        int16_t getMaterialIndex() const;
        Color4ub getPackedColor() const;
        int16_t getRelativePriority() const;
        int16_t getShaderIndex() const;
        bool getShouldDrawTexturedFaceWhite() const;
        int16_t getSurfaceMaterialCode() const;
        int16_t getTextureMappingIndex() const;
        int16_t getTexturePatternIndex() const;
        double getTransparency() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::string mAsciiId;
        int32_t mIrColorCode;
        int16_t mRelativePriority;
        int8_t mDrawType;
        int8_t mShouldDrawTexturedFaceWhite;
        uint16_t mColorNameIndex;
        uint16_t mAlternateColorNameIndex;
        int8_t mBillboardTemplate;
        int16_t mDetailTexturePattern; //-1 if none
        int16_t mTexturePatternIndex; //-1 if none
        int16_t mMaterialIndex;
        int16_t mSurfaceMaterialCode; //for DFAD
        int16_t mFeatureId; //for DFAD
        int32_t mIrMaterialCode;
        uint16_t mTransparency; //0 -> opaque | 65535 -> totally clear
        uint8_t mLodGenerationControl;
        uint8_t mLineStyleIndex;
        int32_t mFlags;
        uint8_t mLightMode;
        uint32_t mPackedColor;
        uint32_t mAlternatePackedColor;
        int16_t mTextureMappingIndex; //-1 if none
        uint32_t mColorIndex;
        uint32_t mAlternateColorIndex;
        int16_t mShaderIndex;

    };

}