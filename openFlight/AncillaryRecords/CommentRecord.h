#pragma once

#include "AncillaryRecord.h"
#include <string>
#include "Types.h"

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class CommentRecord : public AncillaryRecord
    {
    public:
        CommentRecord() = delete;
        explicit CommentRecord(PrimaryRecord* ipParent);
        CommentRecord(const CommentRecord&) = delete;
        CommentRecord& operator=(const CommentRecord&) = delete;
        virtual ~CommentRecord() {}
        
        const std::string& getComment() const;

    protected:
        virtual bool parseRecord(std::ifstream& iRawRecord, int iVersion) override;
        
        std::string mComment;
    };
}