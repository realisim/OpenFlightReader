
#pragma once

//Records.h is here so clients only have to include
//OpenflightReader.h
#include "Records.h"
#include <set>
#include <string>
#include <stack>

//TextureAttribute.h is here so clients only have to include
#include "TextureAttribute.h"

namespace OpenFlight
{
    class Document;

    /**/
    class OFR_API OpenFlightReader
    {
    public:
        OpenFlightReader();
        OpenFlightReader(const OpenFlightReader&) = delete;
        OpenFlightReader& operator=(const OpenFlightReader&) = delete;
        ~OpenFlightReader();
        
        struct Options
        {
            Options();
            bool mDebugEnabled;
            bool mExternalReferenceLoadingEnabled;
            bool mVertexDataSkipped;
            bool mShowCurrentFilenamePathBeingParsed;
        };
        
        std::string getAndClearLastErrors() const;
        std::string getAndClearLastWarnings() const;
        std::string getFilePath() const;
        std::string getFilename() const;
        std::string getFilenamePath() const;
        const Options& getOptions() const;
        bool hasErrors() const;
        bool hasWarnings() const;
        HeaderRecord* open(const std::string& iFileNamePath); //Should return a clas Document.
        void setOptions(Options);

    protected:
        // The ReadState holds information relative to the current
        // file being read. Namely the file name, and the path.
        //
        // It also holds information on the current node (see
        // pushLevel and popLevel). New nodes are added (as childs)
        // to the current node.
        //
        // The ReadState can be pushed/popped (see push/popReadState).
        // It is useful for external reference. When an external reference
        // is encountered, method open() is called recursively, and to keep
        // track of where we were when we get out of the recursion, we pop back
        // the ReadState.
        //
        struct ReadState
        {
            ReadState() :
                mpCurrentHeaderNode(nullptr),
                mpCurrentParentNode(nullptr),
                mpLastPrimaryNodeAdded(nullptr) {}
            ReadState& operator=(const ReadState&) = default;
            HeaderRecord* mpCurrentHeaderNode;
            PrimaryRecord* mpCurrentParentNode;
            PrimaryRecord* mpLastPrimaryNodeAdded;
            std::string mFilenamePath;
            std::string mFilename;
            std::string mFilePath;
        };
        
        void addError(const std::string&) const;
        void addPrimaryRecord(PrimaryRecord*);
        void addWarning(const std::string&) const;
        void clear();
        HeaderRecord* getCurrentHeaderNode();
        PrimaryRecord* getLastPrimaryNodeAdded();
        PrimaryRecord* getCurrentParentNode();
        void open(const std::string& iFileNamePath, bool iIsExternalReference);
        template<typename T> void parseAncillaryRecord(std::ifstream& iRawRecord);
        template<typename T> void parsePrimaryRecord(std::ifstream& iRawRecord);
        void parseExternalReferenceRecord(std::ifstream& iRawRecord);
        void parseHeaderRecord(std::ifstream& iRawRecord);
        void parseUnsupportedRecord(std::ifstream& iRawRecord);
        void parseRawRecord(uint16_t iOpCode, std::ifstream& iRawRecord);
        void parseVertexPaletteEntry(std::ifstream& iRawRecord);
        void popLevel();
        void popReadState();
        void pushLevel();
        void pushReadState();
        void readRecord(std::ifstream& iFileStream);
        std::string rawRecordToString(std::ifstream& iRawRecord, int iRecordLength) const;
        void setCurrentHeaderNode(HeaderRecord*);
        void setCurrentPrimaryNode(PrimaryRecord*);
        void setLastPrimaryNodeAdded(PrimaryRecord*);

        mutable std::string mErrors;
        mutable std::set<std::string> mWarnings;
        Options mOptions;

        HeaderRecord* mpRootNode; //not owned, will be pass to caller of open()
        ReadState mReadState;
        std::stack<ReadState> mReadStateStack;
        std::map<std::string, ExternalReferenceRecord*> mExternalReferences;
    };
    
    //-----------------------------------------------------------------------------
    // Ancillary records always follow the primary node they affect and allways
    // precede a control command.
    // So we add the ancillary to the lastly added primary node.
    //
    template<class T>
    void OpenFlightReader::parseAncillaryRecord(std::ifstream& iRawRecord)
    {
        T *r = new T(getCurrentParentNode());
        ((Record*)r)->parseRecord(iRawRecord, getCurrentHeaderNode()->getFormatRevision());
        
        getLastPrimaryNodeAdded()->addAncillaryRecord(r);
    }
    
    //-----------------------------------------------------------------------------
    template<class T>
    void OpenFlightReader::parsePrimaryRecord(std::ifstream& iRawRecord)
    {
        T *r = new T(getCurrentParentNode());
        ((Record*)r)->parseRecord(iRawRecord, getCurrentHeaderNode()->getFormatRevision());
        
        //Goup is a primary node, so we add it to the currentPrimaryNode
        addPrimaryRecord(r);
    }

}