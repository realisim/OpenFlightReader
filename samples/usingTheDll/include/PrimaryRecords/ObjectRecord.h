
#pragma once

#include "PrimaryRecord.h"
#include <string>

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class OFR_API ObjectRecord : public PrimaryRecord
    {
    public:
        ObjectRecord() = delete;
        explicit ObjectRecord(PrimaryRecord* ipParent);
        ObjectRecord(const ObjectRecord&) = delete;
        ObjectRecord& operator=(const ObjectRecord&) = delete;
        virtual ~ObjectRecord();

        enum flag{fDontDisplayInDaylight = 1 << 31, fDontDisplayAtDusk = 1 << 30,
            fDontDisplayAtNight = 1 << 29, fDontIlluminate = 1 << 28,
            fFlatShaded = 1 << 27, fGroupsShadowObject = 1 << 26,
            fPreserveAtRuntime = 1 << 25 };

        const std::string& getAsciiId() const;
        int32_t getFlags() const;
        int16_t getRelativePriority() const;
        uint16_t getSignificance() const;
        uint16_t getSpecialEffectId1() const;
        uint16_t getSpecialEffectId2() const;
        double getTransparency() const;
        bool hasFlag( flag ) const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::string mAsciiId;
        int32_t mFlags;
        int16_t mRelativePriority;
        uint16_t mTransparency; //0 -> opaque | 65535 -> totally clear
        int16_t mSpecialEffectId1;
        int16_t mSpecialEffectId2;
        int16_t mSignificance;
    };

}