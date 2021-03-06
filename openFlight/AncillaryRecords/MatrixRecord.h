#pragma once

#include "AncillaryRecord.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class OFR_API MatrixRecord : public AncillaryRecord
    {
    public:
        MatrixRecord() = delete;
        explicit MatrixRecord(PrimaryRecord* ipParent);
        MatrixRecord(const MatrixRecord&) = delete;
        MatrixRecord& operator=(const MatrixRecord&) = delete;
        virtual ~MatrixRecord() {}
        
        const Matrix4f& getMatrix() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        Matrix4f mMatrix;
    };
}