

#pragma once

#include "AncillaryRecord.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class OFR_API IndexedStringRecord : public AncillaryRecord
    {
    public:
        IndexedStringRecord() = delete;
        explicit IndexedStringRecord(PrimaryRecord* ipParent);
        IndexedStringRecord(const IndexedStringRecord&) = delete;
        IndexedStringRecord& operator=(const IndexedStringRecord&) = delete;
        virtual ~IndexedStringRecord() {}

        //    Getters
        uint32_t getIndex() const;
        std::string getString() const;

        //    Setters
        //void setIndex(uint32_t);
        //void setString(std::string);

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        uint32_t mIndex;
        std::string mString;
    };
}