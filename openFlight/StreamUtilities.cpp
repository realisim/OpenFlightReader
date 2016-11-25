
#include "StreamUtilities.h"


using namespace std;

namespace OpenFlight
{
    const bool __BIGENDIAN = false; //Windows machine are little endian...

    //-------------------------------------------------------------------------
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
    bool readInt16(istream& iStream, int16_t& oV)
    {
        iStream.read( (char*)&oV, sizeof(int16_t) );

        if(!__BIGENDIAN){ swapBytes(oV); }

        return iStream.good();
    }

    //-------------------------------------------------------------------------
    bool readInt32(std::istream& iStream, int32_t& oV)
    {
        iStream.read( (char*)&oV, sizeof(int32_t) );

        if(!__BIGENDIAN){ swapBytes(oV); }

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

        if(!__BIGENDIAN){ swapBytes(oV); }

        return iStream.good();
    }

    //-------------------------------------------------------------------------
    bool readDouble(std::istream& iStream, double& oV)
    {
        iStream.read( (char*)&oV, sizeof(double) );

        //if(!__BIGENDIAN){ swapBytes8((char*)&oV); }

        return iStream.good();
    }

    //-------------------------------------------------------------------------
    void swapBytes(int16_t& iV)
    {
        iV = (( iV >> 8 ) & 0x00ff) | //move byte 1 to 0
             (( iV << 8 ) & 0xff00 ); //move byte 0 to 1
    }

    //-------------------------------------------------------------------------
    void swapBytes(uint16_t& iV)
    { 
        int16_t t = iV;
        swapBytes( t );
        iV = (uint16_t)t;
    }

    //-------------------------------------------------------------------------
    void swapBytes(int32_t& iV)
    { 
        iV = (( iV >> 24 ) & 0x000000ff) | //move byte 3 to 0
             (( iV >> 8 ) & 0x0000ff00) | //move byte 2 to 1
             (( iV << 8 ) & 0x00ff0000) | //move byte 1 to 2
             (( iV << 24 ) & 0xff000000 ); //move byte 0 to 3
    }

    //-------------------------------------------------------------------------
    void swapBytes(double& iV)
    { 
        iV = 0.0;
    }
}