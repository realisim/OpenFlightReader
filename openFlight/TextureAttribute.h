#include <stdint.h>
#include <string>

namespace OpenFlight
{
    // This class is meant to reat the .attr file produce by Creator.
    // We are not reading everythin as this file format is quite extensive
    // and we don't really need everything in there.
    //
    class TextureAttribute
    {
    public:
        TextureAttribute();
        TextureAttribute(const TextureAttribute&) = default;
        TextureAttribute& operator=(const TextureAttribute&) = default;
        ~TextureAttribute() = default;

        enum FileFormatType{ AttImage8Pattern = 0, AttImage8Template, SgiIntensityModulation, 
            SgiIntensityWithAlpah, SgiRgb, SgiRgba};
        enum MinificationMagnificationFilterType{mmftPoint = 0, mmftBilinear, mmftNone, mmftBicubic, mmftSharpen,
            mmftAddDetail, mmftModulateDetail, mmftBilinearGE, mmftBilinearLE, mmftBicubicGE, mmftBicubucLE };
        enum WrapMethod{wmRepeat = 0, wmClamp=1, wmNone=3, wmMirroredRepeat=4 };
        enum EnvironmentType{etModulate = 0, etBlend, etDecal, etReplace, etAdd};
        enum InternalFormatType{iftTX_I_12A_4 = 0, iftTX_IA_8, iftTX_RGB_5, iftTX_RGBA_4, iftTX_IA_12,
            iftTX_RGBA_8, iftTX_RGBA_12, iftTX_I_16, iftTX_RGB_12};
        enum ExternalFormatType{eftDefault=0, eftTX_PACK_8, eftTX_PACK_16};

        //Getters
        EnvironmentType getEnvironmentType() const;
        FileFormatType getFileFormatType() const;
        MinificationMagnificationFilterType getMagnificationFilterType() const;
        MinificationMagnificationFilterType getMinificationFilterType() const;
        double getRealWorldSizeX() const;
        double getRealWorldSizeY() const;
        int32_t getSizeInTexelsX() const;
        int32_t getSizeInTexelsY() const;
        WrapMethod getWrapMethodU() const;
        WrapMethod getWrapMethodUV() const;
        WrapMethod getWrapMethodV() const;
        bool isValid() const;
        bool readFromFile(const std::string& iFilenamePath);

    protected:
        bool mIsValid;

        int32_t mSizeInTexelsX;
        int32_t mSizeInTexelsY;
        //int32_t obsolete
        //int32_t obsolete
        //int32_t mXComponentOfUpVector;
        //int32_t mYComponentOfUpVector;
        int32_t mFileFormatType;
        int32_t mMinificationFilterType;
        int32_t mMagnificationFilterType;
        int32_t mWrapMethodUV;
        int32_t mWrapMethodU;
        int32_t mWrapMethodV;
        //int32_t modified flag
        //int32_t mXPivotPointForRotatingTextures;
        //int32_t mYPivotPointForRotatingTextures;
        int32_t mEnvironmentType;
        //int32_t mIsAlphaLoadedWithWhiteInColor;
        //int32_t reserved;
        //int32_t reserved;
        double mRealWorldSizeX;
        double mRealWorldSizeY;
        //int32_t mCodeForOriginOfImportedTexture;
        //int32_t mKernelVersionNumber;
        //int32_t mInternalFormatType;
        //int32_t mExternalFormatType;
        // mipmap kernel... not reading that stuff... i dont get it... must be old school :)
        // mag for alpha...
        // mag for color...
        // not reading the rest of the file...
    };
}