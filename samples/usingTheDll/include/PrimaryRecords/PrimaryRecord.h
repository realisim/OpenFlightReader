
#pragma once

#include "Record.h"
#include <memory>
#include <vector>


namespace OpenFlight
{
    class AncillaryRecord;
    class LongIdRecord;
    
    //-------------------------------------------------------------------------
    // Explication sur le refcount...
    //
    //
    class OFR_API PrimaryRecord : public Record
    {
    public:
        PrimaryRecord() = delete;
        explicit PrimaryRecord(PrimaryRecord* ipParent);
        PrimaryRecord(const PrimaryRecord&) = delete;
        PrimaryRecord& operator=(const PrimaryRecord&) = delete;
        virtual ~PrimaryRecord();

        void addAncillaryRecord(AncillaryRecord*);
        void addChild(PrimaryRecord*);
        int decrementUseCount();
        AncillaryRecord* getAncillaryRecord(int) const;
        PrimaryRecord* getChild(int) const;
        LongIdRecord* getLongIdRecord() const;
        int getNumberOfAncillaryRecords() const;
        int getNumberOfChilds() const;
        PrimaryRecord* getParent() const;
        int getUseCount() const;
        bool hasLongIdRecord() const;
        bool isExternalReference() const;
        void incrementUseCount();
        
    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) = 0;
        virtual void handleAddedAncillaryRecord(AncillaryRecord*);
        void incrementUseCount(PrimaryRecord*, int);
        
        std::vector<AncillaryRecord*> mAncillaryRecords;
        std::vector< PrimaryRecord* > mChilds;
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
        
        // cheap way of ref counting... see openflightReader::parseExternalReference
        //
        int mUseCount;
    };
}