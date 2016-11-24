
#pragma once

#include <vector>

namespace OpenFlight
{
    //-------------------------------------------------------------------------
    class INode
    {
    public:
        INode();
        INode(const INode&) = delete;
        INode& operator=(const INode&) = delete;
        virtual ~INode();

        void addChild(INode*);
        int getNumberOfChilds() const;
        virtual void parseRecord(int iRecordSize, char* iRecord) = 0;

    protected:
        std::vector<INode*> mChilds;
    };
}