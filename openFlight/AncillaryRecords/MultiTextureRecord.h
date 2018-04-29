#pragma once

#include <array>
#include "AncillaryRecord.h"


namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // The multitexture record is an ancillary record of face and mesh nodes.
    // It specifies the texture layer information for the face or mesh.
    //
    //
    // multitexture records covers 7 layers. From layer 1 to 8.
    // Layer 0 is the base layer and is handled at the FaceRecord.
    //
    // Here methods with iLayerIndex start at index 0, meaning the first layer
    // of the multitextureRecord, so layer1 of the face.
    //
    //
    class OFR_API MultiTextureRecord : public AncillaryRecord
    {
    public:
        MultiTextureRecord() = delete;
        explicit MultiTextureRecord(PrimaryRecord* ipParent);
        MultiTextureRecord(const MultiTextureRecord&) = delete;
        MultiTextureRecord& operator=(const MultiTextureRecord&) = delete;
        virtual ~MultiTextureRecord() {}
        
        enum EffectType{etTextureEnvironment, etBump, etReserved, etUserDefined };
        
        int getData(int iLayerIndex) const;
        EffectType getEffect(int iLayerIndex) const;
        int getMappingIndex(int iLayerIndex) const;
        int getTexturePatternIndex(int iLayerIndex) const;
        bool hasLayers() const;
        bool hasLayer(int iLayerIndex) const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        int32_t mAttributeMask;
        std::array<uint32_t, 7> mTexturePatternIndices;
        std::array<uint32_t, 7> mMappingIndices;
        std::array<uint32_t, 7> mEffects;
        std::array<uint32_t, 7> mData;

    };
}