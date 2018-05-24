
#pragma once

#include <map>
#include "PrimaryRecord.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class OFR_API SwitchRecord : public PrimaryRecord
    {
    public:
        SwitchRecord() = delete;
        explicit SwitchRecord(PrimaryRecord* ipParent);
        SwitchRecord(const SwitchRecord&) = delete;
        SwitchRecord& operator=(const SwitchRecord&) = delete;
        virtual ~SwitchRecord();

        std::string getAsciiId() const;
        int32_t getCurrentMaskIndex() const;
        std::string getMaskName(int iMaskIndex) const; // fetch the indexedStringRecord...
        uint32_t getMask(int iMaskIndex) const;
        int32_t getNumberOfMasks() const;
        int32_t getNumberOfWordsPerMask() const;
        std::vector<int> getSelectedChildFromMask(int iMaskIndex) const;
        

        //    Setters
        //void setAsciiId(std::string);
        //void setCurrentMask(int32_t);
        //void setMaskWords(uint32_t);
        //void setNumberOfMasks(int32_t);
        //void setNumberOfWordsPerMask(int32_t);

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        virtual void handleAddedAncillaryRecord(AncillaryRecord*) override;

        std::string mAsciiId;
        int32_t mCurrentMask;
        int32_t mNumberOfMasks;
        int32_t mNumberOfWordsPerMask;
        std::vector<uint32_t> mMasks;

        std::map<int, std::string> mMaskNames; //not owned...
    };

}