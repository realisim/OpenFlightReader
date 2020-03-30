
#include "DegreeOfFreedomRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
DegreeOfFreedomRecord::DegreeOfFreedomRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("n/a")
{}

//------------------------------------------------------------------------------
DegreeOfFreedomRecord::~DegreeOfFreedomRecord()
{}

//------------------------------------------------------------------------------
std::string DegreeOfFreedomRecord::getAsciiId() const
{ return mAsciiId;}

DOFParameter DegreeOfFreedomRecord::getTranslationXParameter()const
{
    return mTranslationX;
}
DOFParameter DegreeOfFreedomRecord::getTranslationYParameter()const
{
    return mTranslationY;
}
DOFParameter DegreeOfFreedomRecord::getTranslationZParameter()const
{
    return mTranslationZ;
}

DOFParameter DegreeOfFreedomRecord::getScaleXParameter()const
{
    return mScaleX;
}
DOFParameter DegreeOfFreedomRecord::getScaleYParameter()const
{
    return mScaleY;
}
DOFParameter DegreeOfFreedomRecord::getScaleZParameter()const
{
    return mScaleZ;
}

DOFParameter DegreeOfFreedomRecord::getPitchParameter()const
{
    return mPitch;
}
DOFParameter DegreeOfFreedomRecord::getRollParameter()const
{
    return mRoll;
}
DOFParameter DegreeOfFreedomRecord::getYawParameter()const
{
    return mYaw;
}

DegreeOfFreedomRecord::dofFlag DegreeOfFreedomRecord::getFlags() const
{
    return mFlags;
}

Vector3d DegreeOfFreedomRecord::getOrigin()const
{
    return mOrigin;
}

Vector3d DegreeOfFreedomRecord::getPointOnX_axis()const
{
    return mPointOnXaxis;
}

Vector3d DegreeOfFreedomRecord::getPointOnXY_plane()const
{
    return mPointOnXYplane;
}

void DegreeOfFreedomRecord::handleAddedAncillaryRecord(AncillaryRecord* ipAncillary)
{
    PrimaryRecord::handleAddedAncillaryRecord(ipAncillary);
}

//------------------------------------------------------------------------------
bool DegreeOfFreedomRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);    
    
    bool ok = true;
    ok &= readChar(iRawRecord, 8, mAsciiId);
    
    int reserved = 0;
    ok &= readInt32(iRawRecord, reserved);
    
    iRawRecord.seekg(startPos + 16);
    
    ok &= readVector3d(iRawRecord, mOrigin);
    ok &= readVector3d(iRawRecord, mPointOnXaxis);
    ok &= readVector3d(iRawRecord, mPointOnXYplane);

    ok &= readDOFParameter(iRawRecord, mTranslationZ);
    ok &= readDOFParameter(iRawRecord, mTranslationY);
    ok &= readDOFParameter(iRawRecord, mTranslationX);

    ok &= readDOFParameter(iRawRecord, mPitch);
    ok &= readDOFParameter(iRawRecord, mRoll);
    ok &= readDOFParameter(iRawRecord, mYaw);

    ok &= readDOFParameter(iRawRecord, mScaleZ);
    ok &= readDOFParameter(iRawRecord, mScaleY);
    ok &= readDOFParameter(iRawRecord, mScaleX);

    int flag = 0;
    ok &= readInt32(iRawRecord, flag);
    mFlags = (dofFlag)flag;

    int reservedEnd = 0;
    ok &= readInt32(iRawRecord, reservedEnd);

    return ok;
}
