#include <cassert>
#include "TexturePaletteRecord.h"
#include <fstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
TexturePaletteRecord::TexturePaletteRecord(PrimaryRecord* ipParent) :
AncillaryRecord(ipParent)
{}

//-------------------------------------------------------------------------
const std::string& TexturePaletteRecord::getFilenamePath() const
{ return mFilenamePath; }

//-------------------------------------------------------------------------
const Vector2i& TexturePaletteRecord::getLocation() const
{ return mLocation; }

//-------------------------------------------------------------------------
int32_t TexturePaletteRecord::getTexturePatternIndex() const
{ return mTexturePatternIndex; }

//-------------------------------------------------------------------------
bool TexturePaletteRecord::parseRecord(std::ifstream& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);

    bool ok = true;
    ok &= readChar(iRawRecord, 200, mFilenamePath);
    ok &= readInt32(iRawRecord, mTexturePatternIndex);
    ok &= readVector2i(iRawRecord, mLocation);

    return ok;
}