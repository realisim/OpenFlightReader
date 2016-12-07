
#include "AncillaryRecords/AncillaryRecord.h"
#include "PrimaryRecord.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace OpenFlight;
using namespace std;

//-------------------------------------------------------------------------
//--- PrimaryRecord
//-------------------------------------------------------------------------
PrimaryRecord::PrimaryRecord(PrimaryRecord* ipParent) : Record(),
mpParent(ipParent)
{}

//-------------------------------------------------------------------------
PrimaryRecord::~PrimaryRecord()
{
    // delete all ancillary
    for(size_t i = 0; i < mAncillaryRecords.size(); ++i)
    { delete mAncillaryRecords[i]; }
    
    mAncillaryRecords.clear();
    
    // delete all childs
    for(size_t i = 0; i < mChilds.size(); ++i)
    { delete mChilds[i]; }

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
AncillaryRecord* PrimaryRecord::getAncillaryRecord(int iIndex) const
{ return mAncillaryRecords.at(iIndex); }

//-------------------------------------------------------------------------
PrimaryRecord* PrimaryRecord::getChild(int iIndex) const
{ return mChilds.at(iIndex); }

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
void PrimaryRecord::handleAddedAncillaryRecord(Record* ipAncillary)
{
    switch (ipAncillary->getOpCode())
    {
        //case ocLongId: mpLongId = ipAncillary; break;
        default: break;
    }
}
