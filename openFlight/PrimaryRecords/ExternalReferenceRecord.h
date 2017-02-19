
#pragma once

#include "PrimaryRecord.h"
#include <vector>

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class ExternalReferenceRecord : public PrimaryRecord
    {
    public:
        ExternalReferenceRecord() = delete;
        explicit ExternalReferenceRecord(PrimaryRecord* ipParent);
        ExternalReferenceRecord(const ExternalReferenceRecord&) = delete;
        ExternalReferenceRecord& operator=(const ExternalReferenceRecord&) = delete;
        virtual ~ExternalReferenceRecord();

        enum flag{ fColorPaletteOverride = 1 << 31, fMaterialPaletteOverride = 1 << 30,
            fTextureAndMappingOverride = 1 << 29, fLineStylePaletteOverride = 1 << 28,
            fSoundPaletteOverride = 1 << 27, fLightSourcePaletteOverride = 1 << 26,
            fLightPointPaletteOverride = 1 << 25, fShaderPaletteOverride = 1 << 24 };

        std::string getFilenamePath() const;
        std::string getNodeName() const;
        bool hasFlag(flag) const;
        bool hasViewAsBoundingBox() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::string mFilenameAndNodeName;
        int32_t mFlags;
        int16_t mViewAsBoundingBox;
    };

}