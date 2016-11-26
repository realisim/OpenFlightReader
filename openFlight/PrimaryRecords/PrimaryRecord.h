
#pragma once

#include "Record.h"
#include <vector>

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class PrimaryRecord : public Record
    {
    public:
        PrimaryRecord() = delete;
        explicit PrimaryRecord(PrimaryRecord* ipParent);
        PrimaryRecord(const PrimaryRecord&) = delete;
        PrimaryRecord& operator=(const PrimaryRecord&) = delete;
        virtual ~PrimaryRecord();

        void addAncillaryRecord(Record*);
        void addChild(PrimaryRecord*);
        Record* getAncillaryRecord(int) const;
        PrimaryRecord* getChild(int) const;
        int getNumberOfAncillaryRecords() const;
        int getNumberOfChilds() const;
        
    protected:
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) = 0;
        virtual void handleAddedAncillaryRecord(Record*);
        
        std::vector<Record*> mAncillaryRecords;
        std::vector<PrimaryRecord*> mChilds;
        
        //ancillary records...
        // comment
        // longId
        // transformation
        //   matrix
        //   rotate...
    };
}