
#pragma once

#include "PrimaryRecord.h"
#include <vector>

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class VertexListRecord : public PrimaryRecord
    {
    public:
        VertexListRecord() = delete;
        explicit VertexListRecord(PrimaryRecord* ipParent);
        VertexListRecord(const VertexListRecord&) = delete;
        VertexListRecord& operator=(const VertexListRecord&) = delete;
        virtual ~VertexListRecord();

        int32_t getByteOffsetIntoVertexPalette(int) const;
        const std::vector<int32_t>& getByteOffsets() const;
        int getNumberOfVertices() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::vector<int32_t> mByteOffsets;
    };

}