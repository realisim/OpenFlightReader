
#pragma once

#include <istream>
#include <stdint.h>
#include <string>

namespace OpenFlight
{
    bool readChar(std::istream& iStream, int iNumberOfCharToRead, std::string& oV);
    bool readInt16(std::istream& iStream, int16_t& oV);
    bool readInt32(std::istream& iStream, int32_t& oV);
    bool readUint8(std::istream& iStream, uint8_t& oV);
    bool readUint16(std::istream& iStream, uint16_t& oV);
    bool readDouble(std::istream& iStream, double& oV);

    void swapBytes(int16_t& iV);
    void swapBytes(uint16_t& iV);
    void swapBytes(int32_t& iV);
    void swapBytes(double& iV);
}