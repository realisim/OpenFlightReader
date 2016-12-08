#pragma once

#include <cstdint>

namespace OpenFlight
{
    //------------------------------------------------------------------------------
    struct Color3f
    {
        Color3f() : mRed(0.0), mGreen(0.0), mBlue(0.0) {}
        Color3f(float iR, float iG, float iB) : mRed(iR), mGreen(iG), mBlue(iB) {}
        float mRed;
        float mGreen;
        float mBlue;
    };
    
    //------------------------------------------------------------------------------
    struct Color4f
    {
        Color4f() : mRed(0.0), mGreen(0.0), mBlue(0.0), mAlpha(0.0) {}
        Color4f(float iR, float iG, float iB, float iA) : mRed(iR), mGreen(iG), mBlue(iB), mAlpha(iA) {}
        float mRed;
        float mGreen;
        float mBlue;
        float mAlpha;
    };
    
    //------------------------------------------------------------------------------
    //unsigned byte
    struct Color4ub
    {
        Color4ub() : mRed(0), mGreen(0), mBlue(0), mAlpha(0) {}
        Color4ub(int iC) : mRed( (iC >> 24) & 0x000000ff), mGreen( (iC >> 16) & 0x000000ff), mBlue( (iC >> 8) & 0x000000ff), mAlpha(iC & 0x000000ff) {}
        unsigned char mRed;
        unsigned char mGreen;
        unsigned char mBlue;
        unsigned  char mAlpha;
    };
    
    //------------------------------------------------------------------------------
    struct Matrix4f
    {
        Matrix4f(); //identity matrix

        enum internalStorage{isRowMajor = 0, isColumnMajor};
        
        float mData[4][4];
        internalStorage mInternalStorage;
    };

    //------------------------------------------------------------------------------
    struct Vector2f
    {
        Vector2f() : mX(0.0f), mY(0.0f){}
        ~Vector2f(){}
        float mX;
        float mY;
    };

    //------------------------------------------------------------------------------
    struct Vector2i
    {
        Vector2i() : mX(0), mY(0){}
        ~Vector2i(){}
        int mX;
        int mY;
    };
    
    //------------------------------------------------------------------------------
    struct Vector3f
    {
        Vector3f() : mX(0.0f), mY(0.0f), mZ(0.0f) {}
        ~Vector3f(){}
        float mX;
        float mY;
        float mZ;
    };
    
    //------------------------------------------------------------------------------
    struct Vector3d
    {
        Vector3d() : mX(0.0), mY(0.0), mZ(0.0) {}
        ~Vector3d(){}
        double mX;
        double mY;
        double mZ;
    };
    
    //------------------------------------------------------------------------------
    // maps the data for records:
    //   ocVertexWithColor            =   68 ,  //“Vertex with Color Record”
    //   ocVertexWithColorAndNormal   =   69 ,  //“Vertex with Color and Normal Record”
    //   ocVertexWithColorNormalAndUv =   70 ,  //“Vertex with Color, Normal and UV Record”
    //   ocVertexWithColorAndUv       =   71 ,  //“Vertex with Color and UV Record”
    //
    // Notes:
    //  The mFlags is somehow tricky over here. As stated in the documentation
    //      Flags (bits, from left to right)
    //      0 = Start hard edge
    //      1 = Normal frozen
    //      2 = No color
    //      3 = Packed color
    //      4-15 = Spare
    //
    //      By left to right, they mean most significant to least significant
    //      (This sould be validated and corrected if innacurate)
    //
    struct Vertex
    {
        Vertex() : mColorNameIndex(0), mFlags(0), mCoordinate(), mNormal(),
        mTextureCoordinate(), mPackedColor(), mColorIndex(0) {}
        ~Vertex() {}
        
        enum flag{ fStartHardEdge = 1 << 15, fNormalFrozen = 1 << 14,
            fNoColor = 1 << 13, fPackedColor = 1 << 12};
        
        bool hasFlag(flag iFlag) const;
        
        uint16_t mColorNameIndex;
        uint16_t mFlags;
        Vector3d mCoordinate;
        Vector3f mNormal;
        Vector2f mTextureCoordinate;
        Color4ub mPackedColor;
        uint32_t mColorIndex;
    };

}