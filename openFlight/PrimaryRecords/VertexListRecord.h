
#pragma once

#include "PrimaryRecord.h"
#include <vector>

namespace OpenFlight
{
    class UvListRecord;
    //-------------------------------------------------------------------------
    // 
    // Current implementation supports the following version:
    //      15.7 to 16.5
    //
    class OFR_API VertexListRecord : public PrimaryRecord
    {
    public:
        VertexListRecord() = delete;
        explicit VertexListRecord(PrimaryRecord* ipParent);
        VertexListRecord(const VertexListRecord&) = delete;
        VertexListRecord& operator=(const VertexListRecord&) = delete;
        virtual ~VertexListRecord();

        int32_t getByteOffsetIntoVertexPalette(int) const;
        const std::vector<int32_t>& getByteOffsets() const;
        UvListRecord* getUvListRecord();
        int getNumberOfVertices() const;
        bool hasUvListRecord() const;

    protected:
        virtual void handleAddedAncillaryRecord(AncillaryRecord* ipAncillary) override;
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;

        std::vector<int32_t> mByteOffsets;

        // convenient accessor to UvListAncillary record.
        UvListRecord *mpUvListRecord; //not owned...
    };

}