#pragma once

#include "Record.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class TranslateRecord : public Record
    {
    public:
        TranslateRecord() = delete;
        explicit TranslateRecord(Record* ipParent);
        TranslateRecord(const TranslateRecord&) = delete;
        TranslateRecord& operator=(const TranslateRecord&) = delete;
        virtual ~TranslateRecord() {}
        
        const Vector3d& getDelta() const;
        const Vector3d& getOrigin() const;

    protected:
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) override;
        
        Vector3d mOrigin;
        Vector3d mDelta;
    };
}