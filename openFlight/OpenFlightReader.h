
#pragma once

#include <string>

namespace OpenFlight
{
    class INode;

    /**/
    class OpenFlightReader
    {
    public:
        OpenFlightReader();
        OpenFlightReader(const OpenFlightReader&) = delete;
        OpenFlightReader& operator=(const OpenFlightReader&) = delete;
        ~OpenFlightReader();
        
        std::string getAndClearLastErrors() const;
        void enableDebug(bool);
        bool hasDebugEnabled() const;
        bool hasErrors() const;
        INode* open(const std::string& iFileNamePath); //Should return a clas Document.

    protected:
        void addError(const std::string&) const;
        void parseHeaderRecord(int iRecordSize, char* iRawRecord);
        void parseRawRecord(uint16_t iOpCode, int iRecordSize, char* iRawRecord);
        void readRecord(std::ifstream& iFileStream);
        std::string rawRecordToString(int iRecordSize, char* iRawRecord) const;

        mutable std::string mErrors;
        bool mHasDebugEnabled;

        INode* mpRootNode; //Should be the Document.
    };

}