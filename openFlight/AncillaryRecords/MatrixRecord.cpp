#include <cassert>
#include "MatrixRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
MatrixRecord::MatrixRecord(PrimaryRecord* ipParent) : AncillaryRecord(ipParent)
{}

//-------------------------------------------------------------------------
const Matrix4f& MatrixRecord::getMatrix() const
{ return mMatrix; }

//-------------------------------------------------------------------------
bool MatrixRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);

    bool ok = true;
    ok &= readMatrix4f(iRawRecord, mMatrix);
    
    return ok;
}