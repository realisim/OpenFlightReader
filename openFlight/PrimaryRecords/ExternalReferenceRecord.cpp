
#include "ExternalReferenceRecord.h"
#include <sstream>
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
bool ExternalReferenceRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    // Lets move by 4 to skip the opCode and recordLenght... we already know
    // we have a valid record at this point.
    //
    iss.seekg(4);
    bool ok = true;
    
    ok &= readChar(iss, 200, mFilenameAndNodeName);
    
    iss.seekg(208);
    ok &= readInt32(iss, mFlags);
    ok &= readInt16(iss, mViewAsBoundingBox);
    
    return ok;
}
