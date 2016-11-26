#include <cassert>
#include "MatrixRecord.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
MatrixRecord::MatrixRecord(Record* ipParent) : Record(ipParent)
{}

//-------------------------------------------------------------------------
const Matrix4f& MatrixRecord::getMatrix() const
{ return mMatrix; }

//-------------------------------------------------------------------------
bool MatrixRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    //skip header...
    iss.seekg(4);

    bool ok = true;
    ok &= readMatrix4f(iss, mMatrix);
    
    return ok;
}