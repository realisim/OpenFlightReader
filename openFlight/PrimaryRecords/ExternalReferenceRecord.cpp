
#include "ExternalReferenceRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
ExternalReferenceRecord::ExternalReferenceRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mFilenameAndNodeName("n/a"),
mFlags(0),
mViewAsBoundingBox(0)
{}

//------------------------------------------------------------------------------
ExternalReferenceRecord::~ExternalReferenceRecord()
{}

//------------------------------------------------------------------------------
// The Filename is encoded in the following format
//    filename<node name>
//      if <node name> absent, references entire file
std::string ExternalReferenceRecord::getFilenamePath() const
{
    size_t p = mFilenameAndNodeName.find('<');
    string filename = mFilenameAndNodeName.substr(0, p);
    return filename;
}

//------------------------------------------------------------------------------
std::string ExternalReferenceRecord::getNodeName() const
{
    string nodeName;
    size_t p = mFilenameAndNodeName.find('<');
    if(p != string::npos)
    { nodeName = mFilenameAndNodeName.substr(p+1, mFilenameAndNodeName.size() - 2); }
    return nodeName;
}

//------------------------------------------------------------------------------
bool ExternalReferenceRecord::hasFlag(flag iFlag) const
{
    return mFlags & iFlag;
}

//------------------------------------------------------------------------------
bool ExternalReferenceRecord::hasViewAsBoundingBox() const
{
    return mViewAsBoundingBox != 0;
}

//------------------------------------------------------------------------------
bool ExternalReferenceRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    
    ok &= readChar(iRawRecord, 200, mFilenameAndNodeName);
    
    iRawRecord.seekg(startPos + 208);
    ok &= readInt32(iRawRecord, mFlags);
    ok &= readInt16(iRawRecord, mViewAsBoundingBox);
    
    return ok;
}
