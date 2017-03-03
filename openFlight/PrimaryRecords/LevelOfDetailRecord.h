
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
    class LevelOfDetailRecord : public PrimaryRecord
    {
    public:
        LevelOfDetailRecord() = delete;
        explicit LevelOfDetailRecord(PrimaryRecord* ipParent);
        LevelOfDetailRecord(const LevelOfDetailRecord&) = delete;
        LevelOfDetailRecord& operator=(const LevelOfDetailRecord&) = delete;
        virtual ~LevelOfDetailRecord();

        enum flags{  fUsePreviousSlantRange = 0x1,
                    fAdditiveLodsBelow = 0x2,
                    fFreezeCenter = 0x4 };

        std::string getAsciiId() const;
        int32_t getFlags() const;
        double getLodX() const;
        double getLodY() const;
        double getLodZ() const;
        double getSignificantSize() const;
        int16_t getSpecialEffectId1() const;
        int16_t getSpecialEffectId2() const;
        double getSwitchInDistance() const;
        double getSwitchOutDistance() const;
        double getTransitionRange() const;


    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::string mAsciiId;
        double mSwitchInDistance;
        double mSwitchOutDistance;
        int16_t mSpecialEffectId1;
        int16_t mSpecialEffectId2;
        int32_t mFlags;
        double mLodX;
        double mLodY;
        double mLodZ;
        double mTransitionRange;
        double mSignificantSize;

    };

}