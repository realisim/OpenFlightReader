
#include "AncillaryRecords/AncillaryRecord.h"
#include "AncillaryRecords/LongIdRecord.h"
#include "PrimaryRecord.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace OpenFlight;
using namespace std;

//-------------------------------------------------------------------------
//--- PrimaryRecord
//-------------------------------------------------------------------------
PrimaryRecord::PrimaryRecord(PrimaryRecord* ipParent) : Record(),
mpParent(ipParent),
mpLongId(nullptr),
mUseCount(1)
{}

//-------------------------------------------------------------------------
PrimaryRecord::~PrimaryRecord()
{
    // delete all ancillary
    for(size_t i = 0; i < mAncillaryRecords.size(); ++i)
    { delete mAncillaryRecords[i]; }
    
    mAncillaryRecords.clear();
    
    // delete all childs
    PrimaryRecord *c = nullptr;
    for(size_t i = 0; i < mChilds.size(); ++i)
    {
        c = mChilds[i];
        if(c->decrementUseCount() == 1)
        { delete c; }
    }

    mChilds.clear();
}

//-------------------------------------------------------------------------
void PrimaryRecord::addAncillaryRecord(AncillaryRecord* ipAncillary)
{
    mAncillaryRecords.push_back(ipAncillary);
    
    handleAddedAncillaryRecord(ipAncillary);
}

//-------------------------------------------------------------------------
void PrimaryRecord::addChild(PrimaryRecord* iChild)
{ 
    if (iChild != nullptr)
    { mChilds.push_back(iChild); }
}

//-------------------------------------------------------------------------
// Arg! this should be recursive
//
int PrimaryRecord::decrementUseCount()
{
    int r = mUseCount;
    incrementUseCount(this, -1);
    return r;
}

//-------------------------------------------------------------------------
AncillaryRecord* PrimaryRecord::getAncillaryRecord(int iIndex) const
{ return mAncillaryRecords.at(iIndex); }

//-------------------------------------------------------------------------
PrimaryRecord* PrimaryRecord::getChild(int iIndex) const
{ return mChilds.at(iIndex); }

//-------------------------------------------------------------------------
LongIdRecord* PrimaryRecord::getLongIdRecord() const
{ return mpLongId; }

//-------------------------------------------------------------------------
int PrimaryRecord::getNumberOfAncillaryRecords() const
{ return (int)mAncillaryRecords.size(); }

//-------------------------------------------------------------------------
int PrimaryRecord::getNumberOfChilds() const
{ return (int)mChilds.size(); }

//-------------------------------------------------------------------------
PrimaryRecord* PrimaryRecord::getParent() const
{ return mpParent; }

//-------------------------------------------------------------------------
int PrimaryRecord::getUseCount() const
{return mUseCount; }

//-------------------------------------------------------------------------
void PrimaryRecord::handleAddedAncillaryRecord(AncillaryRecord* ipAncillary)
{
    switch (ipAncillary->getOpCode())
    {
        case ocLongId: mpLongId = (LongIdRecord*)ipAncillary; break;
        default: break;
    }
}

//-------------------------------------------------------------------------
bool PrimaryRecord::hasLongIdRecord() const
{ return mpLongId != nullptr; }

//-------------------------------------------------------------------------
bool PrimaryRecord::isExternalReference() const
{
    return getParent() != nullptr && getParent()->getOpCode() == ocExternalReference;
}

//-------------------------------------------------------------------------
void PrimaryRecord::incrementUseCount()
{ incrementUseCount(this, 1); }

//-------------------------------------------------------------------------
void PrimaryRecord::incrementUseCount(PrimaryRecord* ipR, int iInc)
{ 
    ipR->mUseCount += iInc;
    
    for (int i = 0; i < ipR->getNumberOfChilds(); ++i)
    {
        incrementUseCount( ipR->mChilds[i], iInc );
    }
}
