#pragma once

#include "AncillaryRecord.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class LongIdRecord : public AncillaryRecord
    {
    public:
        LongIdRecord() = delete;
        explicit LongIdRecord(PrimaryRecord* ipParent);
        LongIdRecord(const LongIdRecord&) = delete;
        LongIdRecord& operator=(const LongIdRecord&) = delete;
        virtual ~LongIdRecord() {}
        
        const std::string& getAsciiId() const;

    protected:
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) override;
        
        std::string mAsciiId;
    };
}