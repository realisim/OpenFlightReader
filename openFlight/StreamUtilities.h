
#pragma once

#include <istream>
#include <stdint.h>
#include <string>
#include "Types.h"

namespace OpenFlight
{
    bool needsSwapping();
    // it would be a lot clearer if all parameters where passed by pointer
    // instead of reference
    //
    bool readChar(std::istream& iStream, int iNumberOfCharToRead, std::string& oV);
    bool readBytes(std::istream& iStream, int iNumberOfCharToRead, std::string& oV);
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

    bool writeBytes(std::ostream& oss, const std::string& iV);
    bool writeBytes(std::ostream& oss, int iNumberOfBytesToWrite, const char* iV);
    bool writeDouble(std::ostream& oss, double iV);
    //bool writeColor3f(std::ostream& oss, const Color3f& iV);
    //bool writeColor4f(std::ostream& oss, const Color4f& iV);
    bool writeFloat32(std::ostream& oss, float iV);
    bool writeInt8(std::ostream& oss, int8_t iV);
    bool writeInt16(std::ostream& oss, int16_t iV);
    bool writeInt32(std::ostream& oss, int32_t iV);
    //bool writeMatrix4f(std::ostream& oss, const Matrix4f& iV);
    bool writeUint8(std::ostream& oss, uint8_t iV);
    bool writeUint16(std::ostream& oss, uint16_t iV);
    bool writeUint32(std::ostream& oss, uint32_t iV);
    //bool writeVector2f(std::ostream& oss, const Vector2f& iV);
    //bool writeVector2i(std::ostream& oss, const Vector2i& iV);
    //bool writeVector3d(std::ostream& oss, const Vector3d& iV);
    //bool writeVector3f(std::ostream& oss, const Vector3f& iV);
}