
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
    class MissingRecord : public PrimaryRecord
    {
    public:
        MissingRecord() = delete;
        explicit MissingRecord(PrimaryRecord* ipParent);
        MissingRecord(const MissingRecord&) = delete;
        MissingRecord& operator=(const MissingRecord&) = delete;
        virtual ~MissingRecord();

        std::string getAsciiId() const;
        opCode getOriginalOpCode() const;

    protected:
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) override;

        std::string mAsciiId;
        opCode mOriginalOpCode;
    };

}