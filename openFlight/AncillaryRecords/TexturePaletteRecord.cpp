#include <cassert>
#include "TexturePaletteRecord.h"
#include <sstream>
#include "StreamUtilities.h"

using namespace std;
using namespace OpenFlight;

//-------------------------------------------------------------------------
TexturePaletteRecord::TexturePaletteRecord(Record* ipParent) : Record(ipParent)
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
bool TexturePaletteRecord::parseRecord(const std::string& iRawRecord, int iVersion)
{
    Record::parseRecord(iRawRecord, iVersion);
    
    stringstream iss(stringstream::in | stringstream::binary);
    iss.str( iRawRecord );

    //skip header...
    iss.seekg(4);

    bool ok = true;
    ok &= readChar(iss, 200, mFilenamePath);
    ok &= readInt32(iss, mTexturePatternIndex);
    ok &= readVector2i(iss, mLocation);

    return ok;
}