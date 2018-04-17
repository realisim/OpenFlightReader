#pragma once

#include "OpCode.h"
#include "OpenFlightReader_export.h"

namespace OpenFlight
{
    class OFR_API Record
    {
    public:
        Record();
        Record(const Record&) = delete;
        Record& operator=(const Record&) = delete;
        virtual ~Record();
        
        opCode getOpCode() const { return mOpCode; }
        int getRecordLength() const {return mRecordLenght; }
        
    protected:
        /*Since the reader creates and manages the parsing of the
         records, he is friend.*/
        friend class OpenFlightReader;
        
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion);
        
        opCode mOpCode;
        uint16_t mRecordLenght;
    };
}