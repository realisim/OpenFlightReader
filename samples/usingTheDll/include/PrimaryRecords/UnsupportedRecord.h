
#pragma once

#include "PrimaryRecord.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    // This node is inserted each time an unsupported node is encountered, the
    // idea is to keep the tree structure inchanged even when an unsupported
    // node is parsed.
    //
    // By unsupported, I mean not yet implemented with this openflight reader.
    // An unsupported node will appear in the warnings. see 
    // OpenFlightReader::getAndClearLastWarnings()
    //
    class OFR_API UnsupportedRecord : public PrimaryRecord
    {
    public:
        UnsupportedRecord() = delete;
        explicit UnsupportedRecord(PrimaryRecord* ipParent);
        UnsupportedRecord(const UnsupportedRecord&) = delete;
        UnsupportedRecord& operator=(const UnsupportedRecord&) = delete;
        virtual ~UnsupportedRecord();

        std::string getAsciiId() const;
        opCode getOriginalOpCode() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::string mAsciiId;
        opCode mOriginalOpCode;
    };

}