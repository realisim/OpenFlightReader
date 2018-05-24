
#include "AncillaryRecords/IndexedStringRecord.h"
#include <cassert>
#include "SwitchRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//------------------------------------------------------------------------------
SwitchRecord::SwitchRecord(PrimaryRecord* ipParent) :
PrimaryRecord(ipParent),
mAsciiId("n/a"),
mCurrentMask(0),
mNumberOfMasks(0),
mNumberOfWordsPerMask(0),
mMasks(),
mMaskNames()
{}

//------------------------------------------------------------------------------
SwitchRecord::~SwitchRecord()
{}

//------------------------------------------------------------------------------
string SwitchRecord::getAsciiId() const
{ return mAsciiId; }

//------------------------------------------------------------------------------
int32_t SwitchRecord::getCurrentMaskIndex() const
{ return mCurrentMask; }

//------------------------------------------------------------------------------
string SwitchRecord::getMaskName(int iMaskIndex) const
{
    string r ("unnamed");

    auto it = mMaskNames.find(iMaskIndex);
    if (it != mMaskNames.end())
    {
        r = it->second;
    }
    return r;
}

//------------------------------------------------------------------------------
uint32_t SwitchRecord::getMask(int iIndex, int iWordIndex) const
{ 
    uint32_t r = 0;
    if (iIndex >= 0 && iIndex < getNumberOfMasks())
    {
        r = mMasks[iIndex * mNumberOfWordsPerMask + iWordIndex];
    }
    return r;
}

//------------------------------------------------------------------------------
int32_t SwitchRecord::getNumberOfMasks() const
{ return mNumberOfMasks; }

//------------------------------------------------------------------------------
int32_t SwitchRecord::getNumberOfWordsPerMask() const
{ return mNumberOfWordsPerMask; }

//------------------------------------------------------------------------------
vector<int> SwitchRecord::getSelectedChildFromMask(int iMaskIndex) const
{
    vector<int> r;

    const int numChilds = getNumberOfChilds(); 
    for (int i = 0; i < numChilds; ++i)
    {
        uint32_t childMask = 1 << (i % 32);
        uint32_t wordMask = mMasks[iMaskIndex * getNumberOfWordsPerMask() + i/32];

        if (wordMask & childMask)
        {
            r.push_back(i);
        }
    }

    return r;
}

//------------------------------------------------------------------------------
void SwitchRecord::handleAddedAncillaryRecord(AncillaryRecord* ipA)
{
    switch (ipA->getOpCode())
    {
        case ocIndexedString:
        {
            IndexedStringRecord *ir = (IndexedStringRecord *)ipA;
            mMaskNames[ir->getIndex()] = ir->getString();
        } break;

        default: break;
    }
}

//------------------------------------------------------------------------------
bool SwitchRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    std::streamoff startPos = iRawRecord.tellg();
    Record::parseRecord(iRawRecord, iVersion);
    
    bool ok = true;
    ok &= readChar(iRawRecord, 8, mAsciiId);
    
    iRawRecord.seekg(startPos + 16);
    ok &= readInt32(iRawRecord, mCurrentMask);        
    ok &= readInt32(iRawRecord, mNumberOfMasks);
    ok &= readInt32(iRawRecord, mNumberOfWordsPerMask);

    const int numberOfMaskWords = mNumberOfWordsPerMask * mNumberOfMasks;
    mMasks.clear();
    mMasks.resize(numberOfMaskWords);
    mMasks.shrink_to_fit();
    uint32_t maskWord;
    for (int i = 0; i < numberOfMaskWords; ++i)
    {
        ok &= readUint32(iRawRecord, maskWord);
        mMasks[i] = maskWord;
    }

    return ok;
}
