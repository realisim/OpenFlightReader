#pragma once

#include "AncillaryRecord.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class TranslateRecord : public AncillaryRecord
    {
    public:
        TranslateRecord() = delete;
        explicit TranslateRecord(PrimaryRecord* ipParent);
        TranslateRecord(const TranslateRecord&) = delete;
        TranslateRecord& operator=(const TranslateRecord&) = delete;
        virtual ~TranslateRecord() {}
        
        const Vector3d& getDelta() const;
        const Vector3d& getOrigin() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        Vector3d mOrigin;
        Vector3d mDelta;
    };
}