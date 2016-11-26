
#pragma once

#include <istream>
#include <stdint.h>
#include <string>
#include "Types.h"

namespace OpenFlight
{
    bool readChar(std::istream& iStream, int iNumberOfCharToRead, std::string& oV);
    bool readDouble(std::istream& iStream, double& oV);
    bool readColor3f(std::istream& iss, Color3f& oC);
    bool readColor4f(std::istream& iss, Color4f& oC);
    bool readFloat32(std::istream& iStream, float& oV);
    bool readInt8(std::istream& iStream, int8_t& oV);
    bool readInt16(std::istream& iStream, int16_t& oV);
    bool readInt32(std::istream& iStream, int32_t& oV);
    bool readMatrix4f(std::istream& iStream, Matrix4f& oV);
    bool readUint8(std::istream& iStream, uint8_t& oV);
    bool readUint16(std::istream& iStream, uint16_t& oV);
    bool readUint32(std::istream& iStream, uint32_t& oV);
    bool readVector2f(std::istream& iss, Vector2f& oV);
    bool readVector2i(std::istream& iss, Vector2i& oV);
    bool readVector3d(std::istream& iss, Vector3d& oV);
    bool readVector3f(std::istream& iss, Vector3f& oV);

    void swapBytes2(void* iV);
    void swapBytes4(void* iV);
    void swapBytes8(void* iV);
}