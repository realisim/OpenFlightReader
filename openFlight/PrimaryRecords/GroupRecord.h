
#pragma once

#include "PrimaryRecord.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class GroupRecord : public PrimaryRecord
    {
    public:
        GroupRecord() = delete;
        explicit GroupRecord(PrimaryRecord* ipParent);
        GroupRecord(const GroupRecord&) = delete;
        GroupRecord& operator=(const GroupRecord&) = delete;
        virtual ~GroupRecord();

        enum flags{ fReserved = 1 << 31, fForwardAnimation = 1 << 30, fSwingAnimation = 1 << 30, 
            fBoundingBoxFollows = 1 << 29, fFreezeBoundingBox = 1 << 28, fDefaultParent = 1 << 27,
            fBackwardAnimation = 1 << 26, fPreserveAtRuntime = 1 << 25 };

        std::string getAsciiId() const;
        int32_t getFlags() const;
        int8_t getLayerCode() const;
        int32_t getLoopCount() const;
        float getLoopDuration() const;
        int16_t getRelativePriority() const;
        int16_t getSignificance() const;
        int16_t getSpecialEffectId1() const;
        int16_t getSpecialEffectId2() const;

        /*void setAsciiId(std::string);
        void setFlags(int32_t);
        void setLayerCode(int8_t);
        void setLoopCount(int32_t);
        void setLoopDuration(float);
        void setRelativePriority(int16_t);
        void setSignificance(int16_t);
        void setSpecialEffectId1(int16_t);
        void setSpecialEffectId2(int16_t);*/

    protected:
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) override;

        std::string mAsciiId;
        int16_t mRelativePriority;
        int32_t mFlags;
        int16_t mSpecialEffectId1;
        int16_t mSpecialEffectId2;
        int16_t mSignificance;
        int8_t mLayerCode;
        int32_t mLoopCount;
        float mLoopDuration; //in seconds
        float mLastFrameDuration; //in seconds
    };

}