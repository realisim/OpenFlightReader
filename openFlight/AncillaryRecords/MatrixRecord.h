#pragma once

#include "AncillaryRecord.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class MatrixRecord : public AncillaryRecord
    {
    public:
        MatrixRecord() = delete;
        explicit MatrixRecord(PrimaryRecord* ipParent);
        MatrixRecord(const MatrixRecord&) = delete;
        MatrixRecord& operator=(const MatrixRecord&) = delete;
        virtual ~MatrixRecord() {}
        
        const Matrix4f& getMatrix() const;

    protected:
        virtual bool parseRecord(const std::string& iRawRecord, int iVersion) override;
        
        Matrix4f mMatrix;
    };
}