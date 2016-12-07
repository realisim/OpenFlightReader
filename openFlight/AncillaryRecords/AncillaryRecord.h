#pragma once

#include "Record.h"

namespace OpenFlight
{
    class PrimaryRecord;

    class AncillaryRecord : public Record
    {
    public:
        AncillaryRecord() = delete;
        explicit AncillaryRecord(PrimaryRecord* ipParent) : Record(), mpParent(ipParent) {}
        AncillaryRecord(const AncillaryRecord&) = delete;
        AncillaryRecord& operator=(const AncillaryRecord&) = delete;
        virtual ~AncillaryRecord() {;}

        PrimaryRecord* getParent() const {return mpParent;}
        
    protected:
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) override
        { return Record::parseRecord(iRawRecord, iVersion); };

        PrimaryRecord* mpParent; //not owned
    };
}