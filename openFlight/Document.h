#pragma once

#include <string>

namespace OpenFlight
{
    class HeaderRecord;
    
    class Document
    {
    public:
        Document(const Document&) = delete;
        Document& operator=(const Document&) = delete;
        virtual ~Document();
        
        void clear();
        const HeaderRecord* getRoot() const;
        bool isValid() const;

    protected:
        // OpenFlightReader is responsible for creating the document
        // and assigning the root node.
        //
        friend class OpenFlightReader;
        
        Document();
        void setRootNode(HeaderRecord*);

        HeaderRecord* mpRootNode;
    };
}