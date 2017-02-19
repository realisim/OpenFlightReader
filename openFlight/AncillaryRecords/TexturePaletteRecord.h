#pragma once

#include "AncillaryRecord.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class TexturePaletteRecord : public AncillaryRecord
    {
    public:
        TexturePaletteRecord() = delete;
        explicit TexturePaletteRecord(PrimaryRecord* ipParent);
        TexturePaletteRecord(const TexturePaletteRecord&) = delete;
        TexturePaletteRecord& operator=(const TexturePaletteRecord&) = delete;
        virtual ~TexturePaletteRecord() {}
        
        const std::string& getFilenamePath() const;
        const Vector2i& getLocation() const;
        int32_t getTexturePatternIndex() const;
        
    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        std::string mFilenamePath;
        int32_t mTexturePatternIndex;
        Vector2i mLocation; //Location in the texture palette (x, y)
    };
}