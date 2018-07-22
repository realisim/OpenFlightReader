
#pragma once

#include "PrimaryRecord.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class OFR_API IndexedLightPointRecord : public PrimaryRecord
    {
    public:
        IndexedLightPointRecord() = delete;
        explicit IndexedLightPointRecord(PrimaryRecord* ipParent);
        IndexedLightPointRecord(const IndexedLightPointRecord&) = delete;
        IndexedLightPointRecord& operator=(const IndexedLightPointRecord&) = delete;
        virtual ~IndexedLightPointRecord();

        std::string getAsciiId() const;
        int getAppearanceIndex() const;
        int getAnimationIndex() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::string mAsciiId;
        int mAppearanceIndex;
        int mAnimationIndex;
        //uint32_t mDrawOrder; // for calligraphic lights...
        //reserved
    };

}