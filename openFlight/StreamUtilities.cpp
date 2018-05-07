
#include "StreamUtilities.h"
#include <iostream>


using namespace std;

namespace OpenFlight
{
    const bool __BIGENDIAN = false; //Windows machine are little endian...

    //-------------------------------------------------------------------------
    bool needsSwapping()
    {
        return (!__BIGENDIAN);
    }

    //-------------------------------------------------------------------------
    // This function will read iNumberOfCharToRead and will create a string with
    // the content. The returned string oV will end at the first \0 encountered.
    //
    // To read chars and keep \0, see readBytes.
    // 
    bool readChar(std::istream& iStream, int iNumberOfCharToRead, std::string& oV)
    {
        char *c = new char[iNumberOfCharToRead];
        iStream.read(c, iNumberOfCharToRead);

        //no swap involved in reading chars...
        oV = string(c);
        
        delete[] c;

        return iStream.good();
    }

    //-------------------------------------------------------------------------
    bool readBytes(std::istream& iStream, int iNumberOfBytesToRead, std::string& oV)
    {
        oV.resize(iNumberOfBytesToRead);
        iStream.read(&oV[0], iNumberOfBytesToRead);

        return iStream.good();
    }

    //-------------------------------------------------------------------------
    bool readColor3f(istream& iss, Color3f& oC)
    {
        bool ok = true;
        ok &= readFloat32(iss, oC.mRed);
        ok &= readFloat32(iss, oC.mGreen);
        ok &= readFloat32(iss, oC.mBlue);
        return ok;
    }
    
    //-------------------------------------------------------------------------
    bool readColor4f(istream& iss, Color4f& oC)
    {
        bool ok = true;
        ok &= readFloat32(iss, oC.mRed);
        ok &= readFloat32(iss, oC.mGreen);
        ok &= readFloat32(iss, oC.mBlue);
        ok &= readFloat32(iss, oC.mAlpha);
        return ok;
    }

    //-------------------------------------------------------------------------
    bool readDouble(std::istream& iStream, double& oV)
    {
        iStream.read( (char*)&oV, sizeof(double) );

        if(!__BIGENDIAN){ swapBytes8((void*)&oV); }

        return iStream.good();
    }

    //-------------------------------------------------------------------------
    bool readFloat32(std::istream& iStream, float& oV)
    {
        iStream.read( (char*)&oV, sizeof(float) );
        
        if(!__BIGENDIAN){ swapBytes4((void*)&oV); }
        
        return iStream.good();
    }
    
    //-------------------------------------------------------------------------
    bool readInt8(istream& iStream, int8_t& oV)
    {
        iStream.read( (char*)&oV, sizeof(int8_t) );
        return iStream.good();
    }
    
    //-------------------------------------------------------------------------
    bool readInt16(istream& iStream, int16_t& oV)
    {
        iStream.read( (char*)&oV, sizeof(int16_t) );

        if(!__BIGENDIAN){ swapBytes2((void*)&oV); }

        return iStream.good();
    }

    //-------------------------------------------------------------------------
    bool readInt32(std::istream& iStream, int32_t& oV)
    {
        iStream.read( (char*)&oV, sizeof(int32_t) );

        if(!__BIGENDIAN){ swapBytes4((void*)&oV); }

        return iStream.good();
    }

    //-------------------------------------------------------------------------
    bool readUint8(std::istream& iStream, uint8_t& oV)
    {
        iStream.read( (char*)&oV, sizeof(uint8_t) );
        return iStream.good();
    }

    //-------------------------------------------------------------------------
    bool readUint16(istream& iStream, uint16_t& oV)
    {
        iStream.read( (char*)&oV, sizeof(uint16_t) );

        if(!__BIGENDIAN){ swapBytes2((void*)&oV); }

        return iStream.good();
    }
    
    //-------------------------------------------------------------------------
    bool readUint32(istream& iStream, uint32_t& oV)
    {
        iStream.read( (char*)&oV, sizeof(uint32_t) );
        
        if(!__BIGENDIAN){ swapBytes4((void*)&oV); }
        
        return iStream.good();
    }
    
    //-------------------------------------------------------------------------
    // Read a matrix with Row major internal format
    //
    // According to Presagis specification, Matrix record have a Row major
    // internal format. They also add the following details:
    //      Again, each record that follows the matrix record represents a
    //      discrete transformation that has been concatenated to form the
    //      composite matrix. Concatenation is done in the order that the
    //      records are encountered, using premultiplication.
    //
    // Pre multiplication means the following:
    //      When transformation a vector (v) by a Matrix (M), it is done in the
    //      following manner: vM
    // The vector is a 'row vector'. This leads to a slight confusion with
    // classical mathematics regarding matrix multiplication...
    //
    // A very good explanation of that confusion can be found here
    // https://fgiesen.wordpress.com/2012/02/12/row-major-vs-column-major-row-vectors-vs-column-vectors/
    //
    // It seems like presagis, using the row vector also have their matrix
    // transposed... It would make sense since for premultiplication to
    // to work, the translation needs to be on the last row.
    //
    //
    //
    // Here we will store the matrix in Row major. The matrix stored will be
    // as follow (as we find in math books)
    //
    //      S0 R0 R1 Tx
    //      R2 S1 R3 Ty
    //      R4 R5 S2 Tz
    //      0  0  0  1
    //
    // Where S: Scaling-Rotation
    //       R: Rotation
    //      T: Translation
    
    bool readMatrix4f(istream& iss, Matrix4f& oV)
    {
        bool ok = true;
        oV.mInternalStorage = Matrix4f::isRowMajor;
        
        for(int row = 0; row < 4 && ok; ++row)
            for(int column = 0; column < 4 && ok; ++column)
            {
                ok &= readFloat32(iss, oV.mData[column][row]);
            }        
        return ok;
    }
    
    //-------------------------------------------------------------------------
    bool readVector2f(istream& iss, Vector2f& oV)
    {
        bool ok = true;
        ok &= readFloat32(iss, oV.mX);
        ok &= readFloat32(iss, oV.mY);
        return ok;
    }
    
    //-------------------------------------------------------------------------
    bool readVector2i(istream& iss, Vector2i& oV)
    {
        bool ok = true;
        ok &= readInt32(iss, oV.mX);
        ok &= readInt32(iss, oV.mY);
        return ok;
    }
    
    //-------------------------------------------------------------------------
    bool readVector3d(istream& iss, Vector3d& oV)
    {
        bool ok = true;
        ok &= readDouble(iss, oV.mX);
        ok &= readDouble(iss, oV.mY);
        ok &= readDouble(iss, oV.mZ);
        return ok;
    }
    
    //-------------------------------------------------------------------------
    bool readVector3f(istream& iss, Vector3f& oV)
    {
        bool ok = true;
        ok &= readFloat32(iss, oV.mX);
        ok &= readFloat32(iss, oV.mY);
        ok &= readFloat32(iss, oV.mZ);
        return ok;
    }

    //-------------------------------------------------------------------------
    void swapBytes2(void* iV)
    { 
        char in[2], out[2];
        memcpy(in, iV, 2);
        out[0]  = in[1];
        out[1]  = in[0];
        memcpy(iV, out, 2);
    }

    //-------------------------------------------------------------------------
    void swapBytes4(void* iV)
    { 
        char in[4], out[4];
        memcpy(in, iV, 4);
        out[0]  = in[3];
        out[1]  = in[2];
        out[2]  = in[1];
        out[3]  = in[0];
        memcpy(iV, out, 4);
    }

    //-------------------------------------------------------------------------
    void swapBytes8(void* iV)
    {
        char in[8], out[8];
        memcpy(in, iV, 8);
        out[0]  = in[7];
        out[1]  = in[6];
        out[2]  = in[5];
        out[3]  = in[4];
        out[4]  = in[3];
        out[5]  = in[2];
        out[6]  = in[1];
        out[7]  = in[0];
        memcpy(iV, out, 8);
    }

    //-------------------------------------------------------------------------
    bool writeBytes(ostream& oss, const string& iV)
    {
        return writeBytes( oss, iV.size(), iV.c_str() );
    }

    //-------------------------------------------------------------------------
    bool writeBytes(ostream& oss, int iNumberOfBytesToWrite, const char* iV)
    {
        oss.write( (char*)iV, iNumberOfBytesToWrite );
        return oss.good();
    }

    //-------------------------------------------------------------------------
    bool writeDouble(std::ostream& oss, double iV)
    {
        if(!__BIGENDIAN){ swapBytes8((void*)&iV); }
        oss.write( (char*)&iV, sizeof(double) );
        return oss.good();
    }

    //-------------------------------------------------------------------------
    bool writeFloat32(std::ostream& oss, float iV)
    {
        if(!__BIGENDIAN){ swapBytes4((void*)&iV); }
        oss.write( (char*)&iV, sizeof(float) );
        return oss.good();
    }

    //-------------------------------------------------------------------------
    bool writeInt8(std::ostream& oss, int8_t iV)
    {
        oss.write( (char*)&iV, sizeof(int8_t) );
        return oss.good();
    }

    //-------------------------------------------------------------------------
    bool writeInt16(std::ostream& oss, int16_t iV)
    {
        if(!__BIGENDIAN){ swapBytes2((void*)&iV); }
        oss.write( (char*)&iV, sizeof(int16_t) );
        return oss.good();
    }

    //-------------------------------------------------------------------------
    bool writeInt32(std::ostream& oss, int32_t iV)
    {
        if(!__BIGENDIAN){ swapBytes4((void*)&iV); }
        oss.write( (char*)&iV, sizeof(int32_t) );
        return oss.good();
    }

    //-------------------------------------------------------------------------
    bool writeUint8(std::ostream& oss, uint8_t iV)
    {
        oss.write( (char*)&iV, sizeof(uint8_t) );
        return oss.good();
    }

    //-------------------------------------------------------------------------
    bool writeUint16(ostream& oss, uint16_t iV)
    {
        if(!__BIGENDIAN){ swapBytes2((void*)&iV); }
        oss.write( (char*)&iV, sizeof(uint16_t) );
        return oss.good();
    }

    //-------------------------------------------------------------------------
    bool writeUint32(ostream& oss, uint32_t iV)
    {
        if(!__BIGENDIAN){ swapBytes4((void*)&iV); }
        oss.write( (char*)&iV, sizeof(uint32_t) );
        return oss.good();
    }
}