
#include <fstream>
#include "StreamUtilities.h"
#include "TextureAttribute.h"

using namespace OpenFlight;
using namespace std;

//---------------------------------------------------------------------------------------------------------------------
TextureAttribute::TextureAttribute() :
    mIsValid(false),
    mSizeInTexelsX(0),
    mSizeInTexelsY(0),
    mFileFormatType(AttImage8Pattern),
    mMinificationFilterType(mmftPoint),
    mMagnificationFilterType(mmftPoint),
    mWrapMethodUV(wmNone),
    mWrapMethodU(wmNone),
    mWrapMethodV(wmNone),
    mEnvironmentType(etModulate),
    mRealWorldSizeX(0.0),
    mRealWorldSizeY(0.0)
{}


//---------------------------------------------------------------------------------------------------------------------
TextureAttribute::EnvironmentType TextureAttribute::getEnvironmentType() const
{ 
    return (EnvironmentType)mEnvironmentType;
}

//---------------------------------------------------------------------------------------------------------------------
TextureAttribute::FileFormatType TextureAttribute::getFileFormatType() const
{
    return (FileFormatType)mFileFormatType;
}

//---------------------------------------------------------------------------------------------------------------------
TextureAttribute::MinificationMagnificationFilterType TextureAttribute::getMagnificationFilterType() const
{
    return (MinificationMagnificationFilterType)mMagnificationFilterType;
}

//---------------------------------------------------------------------------------------------------------------------
TextureAttribute::MinificationMagnificationFilterType TextureAttribute::getMinificationFilterType() const
{
    return (MinificationMagnificationFilterType)mMinificationFilterType;
}

//---------------------------------------------------------------------------------------------------------------------
double TextureAttribute::getRealWorldSizeX() const
{
    return mRealWorldSizeX;
}

//---------------------------------------------------------------------------------------------------------------------
double TextureAttribute::getRealWorldSizeY() const
{
    return mRealWorldSizeY;
}

//---------------------------------------------------------------------------------------------------------------------
int32_t TextureAttribute::getSizeInTexelsX() const
{
    return mSizeInTexelsX;
}

//---------------------------------------------------------------------------------------------------------------------
int32_t TextureAttribute::getSizeInTexelsY() const
{
    return mSizeInTexelsY;
}

//---------------------------------------------------------------------------------------------------------------------
TextureAttribute::WrapMethod TextureAttribute::getWrapMethodU() const
{
    return (WrapMethod)mWrapMethodU;
}

//---------------------------------------------------------------------------------------------------------------------
TextureAttribute::WrapMethod TextureAttribute::getWrapMethodUV() const
{
    return (WrapMethod)mWrapMethodUV;
}

//---------------------------------------------------------------------------------------------------------------------
TextureAttribute::WrapMethod TextureAttribute::getWrapMethodV() const
{
    return (WrapMethod)mWrapMethodV;
}

//---------------------------------------------------------------------------------------------------------------------
bool TextureAttribute::isValid() const
{
    return mIsValid;
}

//---------------------------------------------------------------------------------------------------------------------
bool TextureAttribute::readFromFile(const std::string& iFilenamePath)
{
    mIsValid = false;

    ifstream ifs;
    ifs.open(iFilenamePath, ifstream::in | ios_base::binary);

    if (!ifs.fail())
    {
        std::streamoff startPos = ifs.tellg();

        bool mIsValid = true;
        mIsValid |= readInt32(ifs, mSizeInTexelsX);
        mIsValid |= readInt32(ifs, mSizeInTexelsY);
        
        ifs.seekg(startPos + 24);
        mIsValid |= readInt32(ifs, mFileFormatType);
        mIsValid |= readInt32(ifs, mMinificationFilterType);
        mIsValid |= readInt32(ifs, mMagnificationFilterType);
        mIsValid |= readInt32(ifs, mWrapMethodUV);
        mIsValid |= readInt32(ifs, mWrapMethodU);
        mIsValid |= readInt32(ifs, mWrapMethodV);

        ifs.seekg(startPos + 60);
        mIsValid |= readInt32(ifs, mEnvironmentType);

        ifs.seekg(startPos + 104);
        mIsValid |= readDouble(ifs, mRealWorldSizeX);
        mIsValid |= readDouble(ifs, mRealWorldSizeY);
    }

    return mIsValid;
}
