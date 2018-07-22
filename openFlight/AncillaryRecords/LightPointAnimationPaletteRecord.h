
#pragma once

#include "AncillaryRecord.h"
#include <vector>

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class OFR_API LightPointAnimationPaletteRecord : public AncillaryRecord
    {
    public:
        LightPointAnimationPaletteRecord() = delete;
        explicit LightPointAnimationPaletteRecord(PrimaryRecord* ipParent);
        LightPointAnimationPaletteRecord(const LightPointAnimationPaletteRecord&) = delete;
        LightPointAnimationPaletteRecord& operator=(const LightPointAnimationPaletteRecord&) = delete;
        virtual ~LightPointAnimationPaletteRecord();

        enum Flag {fFlashing = 0, fRotatingClockwise = 1, fRotatingCounterClockwise = 1 << 2};
        enum AnimationType {atFlashingSequence=0, atRotating, atStrobe, atMorseCode };
        enum MorseCodeTiming {mctStandart, mctFansworth};

        struct Sequence
        {
            enum State {sOn, sOff, sColorChange};
            
            State mState;
            float mDuration;
            uint32_t mColor;
        };

        //Getters
        float getAnimationEnabledPeriod() const;
        float getAnimationPeriod() const;
        float getAnimationPhaseDelay() const;
        AnimationType getAnimationType() const;
        int32_t getCharacterRate() const;
        int32_t getFlags() const;
        int32_t getIndex() const;
        std::string getMorseCodeString() const;
        MorseCodeTiming getMorseCodeTiming() const;
        std::string getName() const;
        int32_t getNumberOfFlashingSequences() const;
        float getRotationAxisX() const;
        float getRotationAxisY() const;
        float getRotationAxisZ() const;
        Sequence getSequence(int) const;
        int32_t getWordRate() const;
        
    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::string mName;
        int32_t mIndex;
        float mAnimationPeriod; //in seconds
        float mAnimationPhaseDelay;
        float mAnimationEnabledPeriod; //in seconds
        float mRotationAxisX;
        float mRotationAxisY;
        float mRotationAxisZ;
        int32_t mFlags;
        AnimationType mAnimationType;
        MorseCodeTiming mMorseCodeTiming;
        int32_t mWordRate;
        int32_t mCharacterRate;
        std::string mMorseCodeString;
        int32_t mNumberOfFlashingSequences;
        
        std::vector<Sequence> mSequences;
    };

}