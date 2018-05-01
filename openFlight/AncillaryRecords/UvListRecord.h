

#pragma once

#include <array>
#include "AncillaryRecord.h"
#include <array>
#include "Types.h"
#include <vector>

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    // The uv list record is an ancillary record of vertex nodes. This record 
    // (if present) always follows the vertex list or morph vertex list record
    //  and contains texture layer information for the vertices represented in
    // the vertex list record it follows.
    //
    //
    class OFR_API UvListRecord : public AncillaryRecord
    {
    public:
        UvListRecord() = delete;
        explicit UvListRecord(PrimaryRecord* ipParent);
        UvListRecord(const UvListRecord&) = delete;
        UvListRecord& operator=(const UvListRecord&) = delete;
        virtual ~UvListRecord() {}

        Vector2f getUv(int iLayerIndex, int iVertexIndex) const;
        bool hasLayers() const;
        bool hasLayer(int iLayerIndex) const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        int32_t mAttributeMask;
        std::array< std::vector<float>, 7> mUCoordinates;
        std::array< std::vector<float>, 7> mVCoordinates;
        //std::array< std::vector<float, 7 > mUWeights; //?!?
        //std::array< std::vector<float, 7 > mVWeights; //?!?

    };
}