#include <cassert>
#include "CommentRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
CommentRecord::CommentRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{}

//-------------------------------------------------------------------------
const std::string& CommentRecord::getComment() const
{ return mComment; }

//-------------------------------------------------------------------------
bool CommentRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    iRawRecord.seekg(startPos + 4);

    bool ok = true;
    ok &= readBytes(iRawRecord, getRecordLength() - 4, mComment);
    
    return ok;
}