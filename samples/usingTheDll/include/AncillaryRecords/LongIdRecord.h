#pragma once

#include "AncillaryRecord.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class OFR_API LongIdRecord : public AncillaryRecord
    {
    public:
        LongIdRecord() = delete;
        explicit LongIdRecord(PrimaryRecord* ipParent);
        LongIdRecord(const LongIdRecord&) = delete;
        LongIdRecord& operator=(const LongIdRecord&) = delete;
        virtual ~LongIdRecord() {}
        
        const std::string& getAsciiId() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        std::string mAsciiId;
    };
}