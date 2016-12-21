
#pragma once

#include "Record.h"
#include <vector>

namespace OpenFlight
{
    class AncillaryRecord;
    class LongIdRecord;
    
    //-------------------------------------------------------------------------
    class PrimaryRecord : public Record
    {
    public:
        PrimaryRecord() = delete;
        explicit PrimaryRecord(PrimaryRecord* ipParent);
        PrimaryRecord(const PrimaryRecord&) = delete;
        PrimaryRecord& operator=(const PrimaryRecord&) = delete;
        virtual ~PrimaryRecord();

        void addAncillaryRecord(AncillaryRecord*);
        void addChild(PrimaryRecord*);
        AncillaryRecord* getAncillaryRecord(int) const;
        PrimaryRecord* getChild(int) const;
        LongIdRecord* getLongIdRecord() const;
        int getNumberOfAncillaryRecords() const;
        int getNumberOfChilds() const;
        PrimaryRecord* getParent() const;
        bool hasLongIdRecord() const;
        bool isExternalReference() const;
        
    protected:
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) = 0;
        virtual void handleAddedAncillaryRecord(AncillaryRecord*);
        
        std::vector<AncillaryRecord*> mAncillaryRecords;
        std::vector<PrimaryRecord*> mChilds;
        PrimaryRecord* mpParent;
        
        // ancillary records
        // These are just convenient pointers to data into mAncillaryRecords.
        //
        LongIdRecord *mpLongId; //owned in mAncillaryRecords
        // comment
        // longId
        // transformation
        //   matrix
        //   rotate...
    };
}